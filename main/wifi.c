#include "wifi.h"
#include "esp_wifi.h"
#include "esp_https_ota.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "configs.h"
#include <stdio.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int wifi_ready = 0, buffer_len = 0, retry_num = 0;
char buffer[MAX_BUFFER_LEN];

static void
wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(WIFI, "WIFI CONNECTING....\n");
    }
    else if (event_id == WIFI_EVENT_STA_CONNECTED)
    {
        ESP_LOGI(WIFI, "WiFi CONNECTED\n");
    }
    else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        ESP_LOGI(WIFI, "WiFi lost connection\n");
        if (retry_num < 5)
        {
            esp_wifi_connect();
            retry_num++;
            ESP_LOGI(WIFI, "Retrying to Connect...\n");
        }
    }
    else if (event_id == IP_EVENT_STA_GOT_IP)
    {
        esp_netif_t *netif_inst = (esp_netif_t *)event_handler_arg;
        esp_netif_ip_info_t ipinfo;
        // ESP_ERROR_CHECK(esp_netif_get_ip_info(netif_inst, &ipinfo));
        ESP_LOGI(WIFI, "Wifi got IP...\n\n");
        wifi_ready = 1;
    }
}

void setup_station_mode(void)
{ // initialize nvs
    nvs_flash_init();

    // initialize the tcp/ip stack
    ESP_ERROR_CHECK(esp_netif_init());

    // create event loop or sum
    esp_event_loop_handle_t event_loop_handle;
    esp_event_loop_args_t event_loop_conf = {
        .queue_size = 10,
        .task_name = NULL,
    };
    // ESP_ERROR_CHECK(esp_event_loop_create(&event_loop_conf, &event_loop_handle));
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // create station or ap
    esp_netif_t *netif_inst = esp_netif_create_default_wifi_sta();

    // initialize wifi
    const wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, &netif_inst));

    // set wifi configs
    wifi_config_t wifi_ap_config = {
        .sta.ssid = SSID,
        .sta.password = PSWD,
    };

    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_ap_config));
    // set to station mode
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    // start the wifi
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_wifi_connect());
    ESP_LOGI(WIFI, "Configurations complete!");
}

esp_err_t http_event_handler(esp_http_client_event_t *event)
{
    if (event->event_id == HTTP_EVENT_ERROR)
    {
        ESP_LOGI(HTTPS, "HTTP error.");
        DELAY(1000);
        return ESP_ERR_HTTP_CONNECTING;
    }
    if (event->event_id == HTTP_EVENT_ON_CONNECTED)
    {
        ESP_LOGI(HTTPS, "Connected to the server.");
    }
    if (event->event_id == HTTP_EVENT_ON_FINISH)
    {
        ESP_LOGI(HTTPS, "HTTP request sent!");
    }
    if (event->event_id == HTTP_EVENT_ON_DATA)
    {
        // clear the buffer
        int data_len = event->data_len;
        memset(buffer, 0, MAX_BUFFER_LEN);
        memcpy(buffer, event->data, MIN(data_len, (int)MAX_BUFFER_LEN));
        // add null char to the end of the data
        if (data_len < MAX_BUFFER_LEN)
            buffer[data_len] = '\0';
        buffer_len = data_len;
    }
    return ESP_OK;
}

void send_http_request(char *post_data)
{
// ESP_LOGI("DEBUG", "http_request_func entered");
#ifdef REQ_ENDPOINT
    esp_http_client_config_t http_config = {
        .url = REQ_ENDPOINT,
        .auth_type = HTTP_AUTH_TYPE_NONE,
        .method = HTTP_METHOD_POST,
        .event_handler = http_event_handler,
        .disable_auto_redirect = true,
        .user_data = buffer,
        .timeout_ms = 10000000,
    };
#else
    esp_http_client_config_t http_config = {
        .host = REQ_IP,
        .port = REQ_PORT,
        .auth_type = HTTP_AUTH_TYPE_NONE,
        .path = REQ_PATH,
        .method = HTTP_METHOD_POST,
        .event_handler = http_event_handler,
        .disable_auto_redirect = true,
        .user_data = buffer,
        .timeout_ms = 10000000,
    };
#endif
    ESP_LOGI("DEBUG", "%s %d", post_data, strlen(post_data));

    esp_http_client_handle_t client = esp_http_client_init(&http_config);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    if (client == NULL)
    {
        ESP_LOGI(HTTPS, "Error connecting to the client.");
    }
    if (wifi_ready)
    {
        esp_err_t err = esp_http_client_perform(client);
        if (err == ESP_OK)
        {
            ESP_LOGI(HTTPS, "HTTP POST Status = %d, content_length = %" PRId64,
                     esp_http_client_get_status_code(client),
                     esp_http_client_get_content_length(client));
            ESP_LOGI(HTTPS, "Response received: %s", buffer);
        }
        else
        {
            ESP_LOGE(HTTPS, "HTTP POST request failed: %s", esp_err_to_name(err));
        }
    }
}

void get_response(char *response, int response_len)
{
    memset(response, 0, response_len);
    strcpy(response, buffer);
}