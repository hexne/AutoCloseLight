#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"


#define SLEEP10 (vTaskDelay(10))

/**
 * @brief 监听按键是否被按下，此处引脚20连接按键输出信号端
 * @return true  : 表示按键被按下
 *         flase : 表示按键未被按下
*/
bool CheckKeyEvent() {
    return gpio_get_level(gpio_num_t::GPIO_NUM_20);
}


/**
 * @brief 查看当前按键是否是长按，并捕获整个长按事件
 * @return true  : 表示该事件是长按
 *         flase : 表示该事件是短按
*/
bool CheckIsLongTimeKey() {
    bool ret = (SLEEP10, CheckKeyEvent()) && (SLEEP10, CheckKeyEvent());

    while (ret && CheckKeyEvent())
        ;
    
    return ret;
}

/**
 * @brief 控制点灯的开关状态
 * @param status : true为开，false为关
*/
void SetLight(bool status) {
    
}

/**
 * @brief 为按钮供电，此处为21引脚
*/
void init_button() {
    gpio_set_level(gpio_num_t::GPIO_NUM_21,1);
}
extern "C" {
void app_main() {

    init_button();
    bool status = false;

    while (1) {
        // 如果按键被触发
        if (CheckKeyEvent()) {
            if (CheckIsLongTimeKey()) {
                printf("长按\n");
            }
            else {
                printf("短按\n");
            }
            SetLight(status);
            status = !status;
        }
        else {
            // printf("未按下\n");
        }
        vTaskDelay(10);

        fflush(stdout);
    }
    
    return;
}
}