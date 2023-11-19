#ifndef WIFI_H
#define WIFI_H
#include <freertos/FreeRTOS.h>
#include <esp_wifi.h>

#define MAX_BUFFER_LEN 256

void setup_station_mode();
void send_http_request(char *post_data);
void get_response(char *response, int response_len);

#endif