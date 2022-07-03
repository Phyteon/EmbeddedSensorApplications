
#ifndef __APPLICATION__
#define __APPLICATION__

#include "mcu_abstraction_layer.hpp"
#include <iostream>
#include "diagnostic.hpp"
#include <memory>
#include "sensor_specific_drivers/sensirion_sht4x/sensirion_sht4x.hpp"
#include <utility>

extern "C" {
    #include "freertos/task.h"
}

/*!
* A wrapper function for all the underlying C++ code.
*
* To be called from app_main. Created to prevent linking issues.
*/
extern "C" void application_main_wrapper();

#endif /* __APPLICATION__ */