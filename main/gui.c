#include "gui.h"
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "driver/gptimer.h"
// #include "lvgl/lvgl.h"
#include "lvgl.h"
#include "configs.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "driver/gpio.h"
#include "hal/spi_types.h"
#include "driver/spi_master.h"
#include "esp_lcd_ili9341.h"
#include "esp_log.h"

#ifdef TOUCH_ENABLED
#include "esp_lcd_touch_xpt2046.h"
#endif

#define BUFFER_SIZE_ROWS 20
#define LCD_SPI_HOST SPI2_HOST
#define CLK_SPEED (uint32_t)2e7

#define CHAT_WIDTH (LCD_WIDTH - 20)
#define CHAT_HEIGHT 80
#define PADDING 10

// lcd settings and params
esp_lcd_panel_handle_t lcd_panel_handle = NULL;
esp_lcd_panel_io_handle_t lcd_panel_io_handle = NULL;
lv_disp_draw_buf_t display_buffer;
lv_color_t buffer1[LCD_WIDTH * BUFFER_SIZE_ROWS * sizeof(lv_color_t)];
lv_disp_drv_t display_driver;
lv_disp_t *display = NULL;

// touch settings and params
#ifdef TOUCH_ENABLED
esp_lcd_panel_io_handle_t touch_io_handle = NULL;
esp_lcd_touch_handle_t lcd_panel_touch_handle = NULL;
lv_indev_drv_t input_driver; // input driver
#endif

void update_ticks(TimerHandle_t xTimer)
{
    lv_tick_inc(REFRESH_RATE);
}

void flush_display(lv_disp_drv_t *display, const lv_area_t *area, lv_color_t *color_p)
{
    // // check if the start x < end x and start y < endy
    // if (area->x1 > area->x2 || area->y1 > area->y2)
    //     return; // error TODO

    // flush the display with the esp lcd
    esp_lcd_panel_draw_bitmap(lcd_panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_p);
}

void backlight_control(uint8_t on)
{
    gpio_set_level(LCD_BCKL, on);
}

bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

#ifdef TOUCH_ENABLED

void setup_touch()
{
    esp_lcd_panel_io_spi_config_t io_config_touch = ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(TOUCH_CS);
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_SPI_HOST, &io_config_touch, &touch_io_handle));
    esp_lcd_touch_config_t lcd_panel_touch_config = {
        .x_max = LCD_HEIGHT,
        .y_max = LCD_WIDTH,
        .rst_gpio_num = -1,
        .int_gpio_num = -1,
        .flags = {
            .swap_xy = 1,
            .mirror_x = 1,
            .mirror_y = 0,
        }};

    ESP_LOGI(INFO, "Intializing touch controller...");
    ESP_ERROR_CHECK(esp_lcd_touch_new_spi_xpt2046(touch_io_handle, &lcd_panel_touch_config, &lcd_panel_touch_handle));
}

void touch_driver_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    uint16_t x[1];
    uint16_t y[1];
    uint16_t strength[1];
    uint8_t count = 0;

    // Update touch point data.
    ESP_ERROR_CHECK(esp_lcd_touch_read_data(lcd_panel_touch_handle));

    data->state = LV_INDEV_STATE_REL;
    if (esp_lcd_touch_get_coordinates(lcd_panel_touch_handle, x, y, strength, &count, 1))
    {
        // check
        if (strength[0] > 1000)
        {
            ESP_LOGI(INFO, "X: %u Y: %u, strength: %u, count: %u", (unsigned)x[0], (unsigned)y[0], (unsigned)strength[0], (unsigned)count);
        }

        data->point.x = x[0];
        data->point.y = y[0];
        data->state = LV_INDEV_STATE_PR;
    }

    data->continue_reading = false;
}

#endif

void setup_lcd()
{
    // setup backlight
    gpio_reset_pin(LCD_BCKL);
    gpio_set_direction(LCD_BCKL, GPIO_MODE_OUTPUT);

    // turn on the backlight
    backlight_control(1);

    TickType_t ticks = pdMS_TO_TICKS(REFRESH_RATE);
    TimerHandle_t refresh_timer_handle = xTimerCreate("refresh", ticks, pdTRUE, (void *)1, update_ticks);

    // init lvgl
    lv_init();
    // start tick refresh
    xTimerStart(refresh_timer_handle, 0);

    ESP_LOGI(INFO, "Refresh timer started.");
    spi_bus_config_t spi_bus_config = {
        .mosi_io_num = LCD_MOSI,
        .miso_io_num = LCD_MISO,
        .sclk_io_num = LCD_CLK,
        .max_transfer_sz = LCD_WIDTH * BUFFER_SIZE_ROWS * sizeof(uint16_t),
        .quadhd_io_num = -1,
        .quadwp_io_num = -1};

    ESP_ERROR_CHECK(spi_bus_initialize(LCD_SPI_HOST, &spi_bus_config, SPI_DMA_CH_AUTO));

    ESP_LOGI(INFO, " SPI configured");

    // lcd panel io config
    esp_lcd_panel_io_spi_config_t lcd_io_config = {
        .cs_gpio_num = LCD_CS,
        .dc_gpio_num = LCD_DC,
        .pclk_hz = CLK_SPEED,
        .on_color_trans_done = notify_lvgl_flush_ready,
        .spi_mode = 0,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .trans_queue_depth = 10,
        .user_ctx = &display_driver,
    };

    // create a new panel with io config
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_SPI_HOST, &lcd_io_config, &lcd_panel_io_handle));

    // config for the panel
    esp_lcd_panel_dev_config_t lcd_panel_dev_config = {
        .reset_gpio_num = LCD_RST,
        .bits_per_pixel = 16,
    }; // create a new panel with the appropriate driver
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(lcd_panel_io_handle, &lcd_panel_dev_config, &lcd_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(lcd_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(lcd_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(lcd_panel_handle, true));

    // initialize display buffer
    lv_disp_draw_buf_init(&display_buffer, &buffer1, NULL, LCD_WIDTH * BUFFER_SIZE_ROWS);

    // init display_driver
    lv_disp_drv_init(&display_driver);
    display_driver.hor_res = LCD_WIDTH;
    display_driver.ver_res = LCD_HEIGHT;
    display_driver.flush_cb = flush_display;
    display_driver.antialiasing = false;
    display_driver.user_data = lcd_panel_handle;
    display_driver.draw_buf = &display_buffer;

    display = lv_disp_drv_register(&display_driver);
    if (display == NULL)
    {
        ESP_LOGI(ERR, "Display was not initialized!");
        esp_restart();
    }
#ifdef TOUCH_ENABLED
    // initialize touch
    setup_touch();

    // touch input driver setup
    lv_indev_drv_init(&input_driver);
    input_driver.type = LV_INDEV_TYPE_POINTER;
    input_driver.disp = display;
    input_driver.read_cb = touch_driver_read;
    input_driver.user_data = lcd_panel_touch_handle;

    // register the driver
    if (lv_indev_drv_register(&input_driver) == NULL)
    {
        ESP_LOGI(ERR, "Touch failed to register.");
        DELAY(1000);
        esp_restart();
    }
    ESP_LOGI(ERR, "Touch initialized.");
#endif

    esp_lcd_panel_mirror(lcd_panel_handle, 1, 1);
    esp_lcd_panel_swap_xy(lcd_panel_handle, 1);
    ESP_LOGI(INFO, "Display ready.");
}

//////////// GUI SECTION /////////////

lv_obj_t *slider, *label;
