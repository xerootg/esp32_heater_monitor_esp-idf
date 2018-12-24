#include "pin_definitions.h"
#include "driver/gpio.h"

void powerStatus(void * queuePtr){
    int pin1 = 0;
    int pin2 = 0;

    bool currentPower = false;
    bool previousPower = false;
    while(1){

        pin1 = gpio_get_level( (gpio_num_t) POWER_LED_1 );
        pin2 = gpio_get_level( (gpio_num_t) POWER_LED_2 );
        if (pin1 == 1 && pin2 == 0){
            currentPower = true;
        }
        if (pin2 == 1 && pin1 == 0){
            currentPower = false;
        }

        if (currentPower != previousPower){
            printf("Power: %s\n", currentPower ? "true": "false");
            previousPower = currentPower;
        }

    }
}