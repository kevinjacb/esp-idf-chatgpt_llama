#include <stdio.h>
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "driver/gptimer.h"
#include "gui.h"
#include "configs.h"
#include "ui/ui.h"
#include "wifi.h"

void app_main(void)
{
    // setup lcd stuff
    setup_lcd();
    // turn on backlight
    backlight_control(1);
    DELAY(100);

    // draw basic gui
    // modify this function to display graphics
    // draw_ui();
    setup_station_mode();
    ui_init();

    // update screen if required
    while (1)
    {
        uint32_t delay = lv_timer_handler();
        DELAY(delay);
    }
}
