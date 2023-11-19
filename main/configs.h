#ifndef CONFIGS_H
#define CONFIGS_H

// lvgl
#define REFRESH_RATE 10 // tickrate

// lcd (Make changes according to your LCD)
#define LCD_WIDTH 320
#define LCD_HEIGHT 240
#define LCD_MOSI 16
#define LCD_CLK 17
#define LCD_CS 13
#define LCD_DC 15
#define LCD_RST 14
#define LCD_BCKL 18
#define LCD_MISO 33

#define TOUCH_ENABLED // uncomment if you have touch screen
#ifdef TOUCH_ENABLED
#define TOUCH_IRQ 35
#define TOUCH_CS 34
#endif

// LOG tags
#define INFO "INFO"
#define ERR "ERR"
#define DEBUG "DEBUG"
#define WIFI "WIFI"
#define REQ "REQUEST"
#define HTTPS "HTTP"

// WIFI Settings
#define SSID "BEEPBOOP"                      // wifi ssid here
#define PSWD "WHYHAVENTYOUCHANGEDTHISMISTER" // wifi password here

// http req target
// either endpoint or socket

// uncomment this if you want to use endpoint
// #define REQ_ENDPOINT "your_endpoint_here" // endpoint here

#ifndef REQ_ENDPOINT
#define REQ_IP "127.0.0.1"    // target ip here
#define REQ_PORT 5000         // target port here
#define REQ_PATH "/ask_llama" // http path
#endif

// delay
#define DELAY(x) vTaskDelay(x / portTICK_PERIOD_MS); // ms

#endif