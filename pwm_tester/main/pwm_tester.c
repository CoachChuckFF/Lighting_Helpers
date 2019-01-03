/* LEDC (LED Controller) fade example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

/*
 * About this example
 *
 * 1. Start with initializing LEDC module:
 *    a. Set the timer of LEDC first, this determines the frequency
 *       and resolution of PWM.
 *    b. Then set the LEDC channel you want to use,
 *       and bind with one of the timers.
 *
 * 2. You need first to install a default fade function,
 *    then you can use fade APIs.
 *
 * 3. You can also set a target duty directly without fading.
 *
 * 4. This example uses GPIO18/19/4/5 as LEDC output,
 *    and it will change the duty repeatedly.
 *
 * 5. GPIO18/19 are from high speed channel group.
 *    GPIO4/5 are from low speed channel group.
 *
 */
#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO       (18)
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_HS_CH1_GPIO       (19)
#define LEDC_HS_CH1_CHANNEL    LEDC_CHANNEL_1

#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_LS_CH2_GPIO       (4)
#define LEDC_LS_CH2_CHANNEL    LEDC_CHANNEL_2
#define LEDC_LS_CH3_GPIO       (5)
#define LEDC_LS_CH3_CHANNEL    LEDC_CHANNEL_3

#define LEDC_TEST_CH_NUM       (4)
#define LEDC_TEST_DUTY         (4000)
#define LEDC_TEST_FADE_TIME    (3000)

//exit chars
#define CHAR_ESC 0x1B
#define CHAR_DEL 0x7F
#define CHAR_BS 0x08

//enter char
#define CHAR_ENTER '\n'

//other acceptable chars
#define CHAR_SPACE 0x20
#define CHAR_PERIOD 0x2E
#define CHAR_COMMA 0x2C
#define CHAR_SEMICOLON ':'

//getcahr null return
#define CHAR_NULL 0xFF

//delay defines
#define INPUT_DELAY 33 / portTICK_PERIOD_MS
#define DMX_DELAY 3

//size defines
#define INPUT_BUFFER_SIZE 64

void app_main()
{
    char in;
    uint32_t freq = 500;
    uint32_t duty = 0;

    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = freq,                      // frequency of PWM signal
        .speed_mode = LEDC_HS_MODE,           // timer mode
        .timer_num = LEDC_HS_TIMER            // timer index
    };

    ledc_timer_config(&ledc_timer);


    ledc_channel_config_t ledc_channel = 
    {
        .channel    = LEDC_HS_CH0_CHANNEL,
        .duty       = 0,
        .gpio_num   = LEDC_HS_CH0_GPIO,
        .speed_mode = LEDC_HS_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_HS_TIMER
    };

    ledc_channel_config(&ledc_channel);

    while(1){
        in = getchar();
        
        if(in == CHAR_DEL || in == CHAR_BS){
            putchar('\n');
            continue;
        }

        switch(in){
            case 'U':
                if(freq + 100 <= 5000){
                    freq += 100;
                    ledc_set_freq(ledc_channel.speed_mode, ledc_channel.timer_sel, freq);
                }
                printf("freq up %d\n", freq);
            break;
            case 'D':
                if(freq - 100 > 100){
                    freq -= 100;
                    ledc_set_freq(ledc_channel.speed_mode, ledc_channel.timer_sel, freq);
                }
                printf("freq down %d\n", freq);
            break;
            case 'u':
                if(duty + 1 <= 8191){
                    duty += 1;
                    ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
                    ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
                }
                printf("duty up %d\n", duty);
            break;
            case 'd':
                if((duty - 1) < 8191){
                    duty -= 1;
                    ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
                    ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
                } else {
                    duty = 0;
                    ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
                    ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
                }
                printf("duty down %d\n", duty);
                break;
            case 'Z':
            case 'z':
                duty = 0;
                ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
                ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
                printf("duty zero %d\n", duty);
                break;
            case 'F':
                duty = 8191;
                ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
                ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
                printf("duty full %d\n", duty);
                break;
            break;
        }

        vTaskDelay(1);
    }
}

