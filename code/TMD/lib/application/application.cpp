
#include "application.hpp"

void application_main_wrapper(){
    try
    {
        mcu_ab_layer::I2C i2c_driver(I2C_NUM_0, 0, mcu_ab_layer::I2C::default_i2c_conf);
        std::cout << "Constructed a I2C driver" << std::endl;
        std::pair<float, float> humidity_and_temp;
        sht4x::Sensirion_SHT4X sensor(i2c_driver);
        std::cout << "Constructed sensor driver" << std::endl;
        std::cout << "Serial number is: " + std::to_string(sensor.get_serial_number()) << std::endl;
        while (true) {
            humidity_and_temp = sensor.measure_humidity_temperature_blocking();
            std::cout << "Humidity: " + std::to_string(std::get<0>(humidity_and_temp)) << std::endl;
            std::cout << "Temperature: " + std::to_string(std::get<1>(humidity_and_temp)) << std::endl;
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}