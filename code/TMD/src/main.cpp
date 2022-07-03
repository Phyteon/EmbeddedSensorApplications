
/*!
* C++ libs BEGIN
*/
#include <iostream>
#include "mcu_abstraction_layer.hpp"
#include "application.hpp"
#include "sensor_specific_drivers/sensirion_sht4x/sensirion_sht4x.hpp"
/*!
* C++ libs END
*/


/*!
* All the C libraries needed included C style
*/
extern "C" {
    #include "sdkconfig.h"
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_chip_info.h"
    #include "esp_spi_flash.h"
    #include <stdio.h>
}

extern "C"{
    void app_main() {
        printf("Test sensirion driver\n");
        application_main_wrapper();
    }
}
