#include <stdio.h> // c language input and output libraries
// freeRTOS Libraries
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ESP32 Libraries
#include "driver/gpio.h"
#include "esp_log.h"

//pins map
#define LED1_PIN 21     //GPIO21
#define LED2_PIN 33     //GPIO33
#define BUTTON_PIN 13    //GPI13

static const char *TAG = "BUTTON TEST: ";   //for Log messages

//main function
void app_main(void)
{
    //local variables
    bool button_state1 = 1;  //variable to store button 1 state
    bool button_state2 = 0;  //variable to store button 2 state
    bool i = 0;             //variable to store LED state

    //configure LED_PIN_1 GPIO as input
    gpio_reset_pin(LED1_PIN);                          //reset pin and set as GPIO
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);   //set LED_PIN_1 as output

    //configure LED_PIN_2 GPIO as input
    gpio_reset_pin(LED2_PIN);                          //reset pin and set as GPIO
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);   //set LED_PIN_1 as output

    //configure button_PIN GPIO as input
    gpio_reset_pin(BUTTON_PIN);                         //reset pin and set as GPIO
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);    //set BUTTON_PIN as input
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);   //set pull-up resistor

    ESP_LOGI(TAG, "init");

    while(true) //infinite loop
    {
        bool new_state = gpio_get_level(BUTTON_PIN);   //read button state and save in new_state variable

        if (new_state != button_state1)              //if button state is different from previous state
        {
            button_state1 = new_state; 
              //update button state
            if (button_state1 == 0)                  //if button is pressed
            {
                gpio_set_level(LED1_PIN, i^=1);      //toggle LED state
                ESP_LOGI(TAG,"Button pressed");   //print message on console
            }
            else                                    //if button is not pressed
            {
                ESP_LOGI(TAG,"Button released");    //print message on console
            }
            button_state2 = new_state;
            if (button_state2 == 0)                  //if button is pressed
            {
                gpio_set_level(LED2_PIN, i^1);      //toggle LED state
                ESP_LOGI(TAG,"Button pressed");   //print message on console
            }
            else                                    //if button is not pressed
            {
                ESP_LOGI(TAG,"Button released");    //print message on console
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);       // delay for 100 ms
    }
}