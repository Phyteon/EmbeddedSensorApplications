
#ifndef __SENSIRION_SHT4X__
#define __SENSIRION_SHT4X__

#include "mcu_abstraction_layer.hpp"
#include "diagnostic.hpp"
#include <memory>
#include <utility>
#include <map>
#include <string>
#include <vector>
extern "C" {
    #include "freertos/task.h"
    #include "esp_err.h"
}

namespace sht4x {
    /*!
    * Class providing abstraction for the Sensirion SHT4X temperature and humidity sensor.
    */
    class Sensirion_SHT4X {
        protected:
            /*!
            * A shared pointer to bus that may be used by many entities (controllers).
            */
            std::shared_ptr<mcu_ab_layer::I2C> i2c_driver_handle;

            /*!
            * All available commands for the sensor.
            */
            inline static const std::map<std::string, uint8_t> command_palette {
                {"MEASURE_HIGH_PRECISION_MODE", 0xFD},
                {"MEASURE_MEDIUM_PRECISION_MODE", 0xF6},
                {"MEASURE_LOW_PRECISION_MODE", 0xE0},
                {"READ_SERIAL_NUMBER", 0x89},
                {"SOFT_RESET", 0x94},
                {"HEATER_EN_HIGH_POWER_1_SEC", 0x39},
                {"HEATER_EN_HIGH_POWER_0_1_SEC", 0x32},
                {"HEATER_EN_MEDIUM_POWER_1_SEC", 0x2F},
                {"HEATER_EN_MEDIUM_POWER_0_1_SEC", 0x24},
                {"HEATER_EN_LOW_POWER_1_SEC", 0x1E},
                {"HEATER_EN_LOW_POWER_0_1_SEC", 0x15}
            };
            /*!
            * Bus address of the sensor.
            */
            inline static const uint8_t address = 0x44;
            /*!
            * Time in miliseconds that is required for the sensor to perform measurement in
            * high precision mode.
            */
            inline static const uint16_t milisec_measure_delay = 100;
            uint32_t serial_number;
            std::vector<uint8_t> output_data_buffer;
            std::vector<uint8_t> input_data_buffer;

            /*!
            * Method for simple CRC8 calculation.
            *
            * @param data Vector (sized!) containing data from which the CRC8 will be calculated.
            * @return CRC8 value.
            */
            uint8_t calculate_crc8(const std::vector<uint8_t>& data);

            /*!
            * Checks if CRC8 is valid and extracts 4 bytes of transmission.
            *
            * @param data Vector (sized!) containing transmission from sensor that will be checked
            *             for correctnes and data extracted.
            * @return Pair of extracted data. If there was any error along the way, exception will
            *         be thrown.
            */
            std::pair<uint16_t, uint16_t> validate_and_extract_data(
                                                            const std::vector<uint8_t>& data);

        public:
            /*!
            * Parametric constructor.
            *
            * @param i2c_driver A valid I2C driver object, which handles the bus to which the
            *                   sensor is connected to.
            */
            Sensirion_SHT4X(mcu_ab_layer::I2C& i2c_driver);

            /*!
            * Method for getting humidity and temperature measurement.
            *
            * This method sends appropriate commands over the i2c to the sensor for it to
            * measure desired parameters. It performs it in blocking mode, as performing the
            * measurement takes some time. For now, measurement is performed in high precision
            * mode.
            * 
            * @return Pair of float values, the first being the humidity (in % RH) and
            *         the second being temperature (in deg C).
            */
            std::pair<float, float> measure_humidity_temperature_blocking();

            inline uint32_t get_serial_number() {return this->serial_number;}
    };
}

#endif /* __SENSIRION_SHT4X__ */