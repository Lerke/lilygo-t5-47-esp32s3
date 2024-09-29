#include <ed047tc1.h>
#include <epd_driver.h>
#include <esp_log.h>
#include <stdio.h>
#include <string.h>

#include "pictures/pic1.h"
#include "pictures/pic2.h"
#include "pictures/pic3.h"

#include "freertos/FreeRTOS.h"

uint8_t *framebuffer = NULL;

void app_main(void) {
    printf("LilyGO T5 4.7\" EPD Test\n");
    framebuffer = (uint8_t *) heap_caps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2, MALLOC_CAP_SPIRAM);
    if (!framebuffer) {
        ESP_LOGE("APP", "Framebuffer allocation failed");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        return;
    }

    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

    epd_init();
    epd_poweron();
    epd_clear();

    Rect_t draw1 = {
        .x = 0,
        .y = 0,
        .width = pic1_width,
        .height = pic1_height
    };
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);

    vTaskDelay(2000 / portTICK_PERIOD_MS);
    epd_draw_grayscale_image(draw1, pic1_data);

    vTaskDelay(5000 / portTICK_PERIOD_MS);

    Rect_t draw2 = {
        .x = 0,
        .y = 0,
        .width = pic2_width,
        .height = pic2_height
    };
    epd_clear();
    epd_draw_grayscale_image(draw2, pic2_data);
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    Rect_t draw3 = {
        .x = 0,
        .y = 0,
        .width = pic3_width,
        .height = pic3_height
    };
    epd_clear();
    epd_draw_grayscale_image(draw3, pic3_data);

    vTaskDelay(5000 / portTICK_PERIOD_MS);

    epd_clear();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    epd_poweroff();
    printf("OK - Done!");
}
