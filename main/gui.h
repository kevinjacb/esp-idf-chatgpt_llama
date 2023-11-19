#ifndef GUI_H
#define GUI_H

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
// #include "lvgl/lvgl.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"

extern esp_lcd_panel_handle_t lcd_panel;
extern esp_lcd_panel_io_handle_t lcd_panel_io;

// flush the display
void flush_display();

// update the display
void update_ticks(TimerHandle_t xTimer);

// setup display
void setup_lcd();

// backlight control
void backlight_control(uint8_t on);

void draw_ui();

#endif