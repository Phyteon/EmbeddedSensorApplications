
#ifndef __DIAGNOSTIC__
#define __DIAGNOSTIC__

#include <stdexcept>
#include "esp_err.h"

namespace diagnostic {
    class I2C_NotInitializedException : public std::logic_error {
        public:
            I2C_NotInitializedException(esp_err_t error_code) : 
            std::logic_error("ERROR: I2C init failed with code " + error_code){};

    };
    class I2C_MasterSlaveReadFailedException : public std::logic_error {
        public:
            I2C_MasterSlaveReadFailedException(esp_err_t error_code) :
            std::logic_error("ERROR: I2C master read from slave failed with code " + error_code){};
    };
}

#endif