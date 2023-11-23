/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// =============================================

void vTask1(void *pvParameter)
{
    int count = 0;
    while (1)
    {
        count++;
        printf("-------> Task 1 count: %d - Core %d\n", count, xPortGetCoreID());
        if(count == 1500)    
        {
            printf("===============Task 1 finish===============\n");
            vTaskDelete(NULL);
        }
    }
}

void vTask2(void *pvParameter)
{
    int count = 0;
    while (1)
    {
        count++;
        printf("-------> Task 2 count: %d - Core %d\n", count, xPortGetCoreID());
        if(count == 1500)    
        {
            printf("===============Task 2 finish===============\n");
            vTaskDelete(NULL);
        }
    }
}

void vTask3(void *pvParameter)
{
    for (int i = 0; i < 6; i++) {
        printf("Task 3 - Before VTaskDelay 500ms - Core %d\n", xPortGetCoreID());
        vTaskDelay(500 / portTICK_PERIOD_MS);
        printf("Task 3 - After VTaskDelay 500ms - Core %d\n", xPortGetCoreID());
        if (i == 0) {
            xTaskCreate(&vTask2, "task2", 4096, NULL, 4, NULL);
        } else if (i == 3) {
            xTaskCreate(&vTask1, "task1", 4096, NULL, 3, NULL);
        }
    }
    vTaskDelete(NULL);
}

void app_main()
{

    xTaskCreate(&vTask3, "task3", 4096, NULL, 2, NULL);

}