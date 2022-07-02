
#ifndef __MCU_ABSTRACTION_LAYER__
#define __MCU_ABSTRACTION_LAYER__

#include <map>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "diagnostic.hpp"
extern "C"{
    #include "esp_err.h"
    #include "driver/i2c.h"
    }
#include "diagnostic.hpp"


namespace mcu_ab_layer {

    /*!
    * Forward declaration so that I2CGlobalDataContainer can reference later the I2C class.
    */
    class I2C;

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
            inline static std::set<I2C*> initialized_ports;
        public:
            /*!
            * Returns the information about currently initialized ports.
            *
            * Info is returned as a std::map, where the key is port number and value is
            * std::pair, where the first element is copied configuration and the second is
            * copied init flags.
            */
            std::map<i2c_port_t, std::pair<i2c_config_t, int>> get_init_ports_info();

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
            inline static constexpr i2c_config_t default_i2c_conf = {
                .mode = I2C_MODE_MASTER,
                .sda_io_num = 21,
                .scl_io_num = 22,
                .sda_pullup_en = false,
                .scl_pullup_en = false,
                .master{.clk_speed = 400000},
                .clk_flags = I2C_SCLK_DEFAULT
            };

            /*!
            * Simple method for comparing i2c_config_t struct to the static constant one.
            *
            * This is a simple workaround for providing comparison for two structures of the
            * same type, instead of building a wrapper for the struct itself.
            * 
            * @param config Reference to a c struct containing configuration to be compared to
            *               default config.
            * @return True if struct is the same as default config. False otherwise.
            */
            static bool compare_config_to_default_config(const i2c_config_t& config);
            
            /*!
            * Parametric constructor.
            *
            * Initializes the i2c port with the specified parameters and adds the pointer to itself
            * to the global set holding all the initialized i2c ports.
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
            I2C(i2c_port_t i2c_port_num, int intr_alloc_flags, const i2c_config_t& config);
            
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

            /*!
            * Class destructor.
            *
            * During object deallocation, the installed driver must also be uninitialized and
            * removed from global set.
            */
            ~I2C();

            /*!
            * Returns information about port in string format.
            *
            * @return Constructed string containing port info.
            */
            std::string get_port_data_as_str();

            /*!
            * Wrapper for functions used to write data to slave, blocking mode.
            *
            * This methods wraps around original C functions used to communicate with slave,
            * while providing some C++ high level features.
            * 
            * @param data_buffer Vector holding data to be sent to slave.
            * @param device_addr Address of the device on the bus.
            * @param timeout Time after which if the slave won't acknowledge the transmission, it
            *                is considered a failed transmission.
            * @return Return value of the original function (if no exception was thrown along the
            *         way).
            */
            esp_err_t write_to_slave(const std::vector<uint8_t>& data_buffer, uint8_t device_addr,
                                    TickType_t timeout);

            /*!
            * Wrapper for functions used to read data from slave, blocking mode.
            *
            * This methods wraps around original C functions used to communicate with slave,
            * while providing some C++ high level features.
            * 
            * @param data_buffer Vector to which the data will be written to.
            * @param device_addr Address of the device on the bus.
            * @param timeout Time after which if the slave won't acknowledge the transmission, it
            *                is considered a failed transmission.
            * @return Return value of the original function (if no exception was thrown along the
            *         way).
            */
            esp_err_t read_from_slave(std::vector<uint8_t>& data_buffer, uint8_t device_addr,
                                    TickType_t timeout);

    };
    
}

#endif /* __MCU_ABSTRACTION_LAYER__ */