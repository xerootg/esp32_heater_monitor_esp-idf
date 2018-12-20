/* SPI Slave example, receiver (uses SPI Slave driver to communicate with sender)

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "lwip/igmp.h"

#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "soc/rtc_cntl_reg.h"
#include "rom/cache.h"
#include "esp_log.h"
#include "esp_spi_flash.h"

#include "spi_read.h"
#include "process_spi_data.h"

#include "spi_message.h"
#include "queue.hpp"
using namespace cpp_freertos;


extern "C" {
	void app_main(void);
}

void app_main(void){

        Queue * queue = new Queue( 10, sizeof( SPIMessage));

        xTaskCreate(&spi_read, "SPI Read", 2048, queue, 5, NULL);
        xTaskCreate(&processSpiMessageTask, "SPI Parse", 2048, queue, 5, NULL);
        // xTaskCreate(&processSerialMessagesTask, "Serial Reader", 2048, NULL, 5, NULL);
}