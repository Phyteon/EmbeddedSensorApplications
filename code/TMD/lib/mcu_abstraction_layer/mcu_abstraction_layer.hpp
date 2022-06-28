
#ifndef __MCU_ABSTRACTION_LAYER__
#define __MCU_ABSTRACTION_LAYER__

#include <map>
#include <string>
#include <vector>
#include "esp_err.h"
#include "diagnostic.hpp"
#include "driver/i2c.h"

namespace mcu_ab_layer {

    /*!
    * Class holding the init and status data of all the I2C ports.
    */
    class I2CGlobalDataContainer
    {
        private:
            friend class I2C; /*!< So that I2C constructors can add pointers to created instances */

            /*!
            * Private constructor.
            *
            * Object construction is not intended, its purpose is to only hold pointers to all
            * I2C port instances for ease of management.
            */
            I2CGlobalDataContainer() = default;
        protected:
            static std::vector<I2C*> initialized_ports;

    };
    
    /*!
    * Class providing simple handlers and another level of abstraction for ESP i2c drivers.
    */
    class I2C
    {
        private:
            friend class I2CGlobalDataContainer;
        protected:
            /*!
            * 
            */
            i2c_config_t config;
            i2c_port_t i2c_port_num;
            int intr_alloc_flags;
        public:
            /*!
            * Default port config.
            *
            * It is made available to the user so that it can be used to instantiate the port
            * without the user needing to specify their own config in the scope where the driver
            * is initialised.
            *
            */
            static constexpr i2c_config_t default_i2c_conf = {
                .mode = I2C_MODE_MASTER,
                .sda_io_num = 21,
                .scl_io_num = 22,
                .master.clk_speed = 400000
            };
            
            /*!
            * Parametric constructor.
            *
            * Initializes the i2c port with the specified parameters.
            * 
            * @param i2c_port_num Number of the port to be initialized. Only I2C_PORT_NUM_0 and
            *                     I2C_PORT_NUM_1 supported.
            * @param intr_alloc_flags Additional init flags for the i2c driver. For details, please
            *                         visit official API reference page for the i2c driver and also
            *                         check the esp_intr_alloc.h file which can be found on the
            *                         official github page of the ESP IDF framework.
            * @param config Configuration structure for the i2c driver. If the default config is
            *               passed to the constructor, the data won't be copied to protected
            *               attribute 'config'.
            *
            */
            I2C(i2c_port_t i2c_port_num,
                int intr_alloc_flags,
                const i2c_config_t& config);
            
            /*!
            * Default constructor.
            *
            * Default constructor checks the list of initialised and active I2C object instances
            * and their configuration, and if there is a possibility to allocate and initialize
            * new i2c master driver, it will do it automatically by trying different available
            * pins and scanning for slave. Default constructor will fail to init if no space
            * is available or if on all the possible pins no slave device is detected. If slave
            * device is expected to be unresponsive for some time (eg. it is powered off)
            * explicit constructor should be used to initialize the i2c port.
            */
            I2C();

            esp_err_t write_to_slave(std::vector<uint8_t>& data_buffer, uint8_t device_addr,
                                    TickType_t timeout);

            esp_err_t read_from_slave(std::vector<uint8_t>& data_buffer, uint8_t device_addr,
                                    TickType_t timeout);

    };
    
}

#endif /* __MCU_ABSTRACTION_LAYER__ */