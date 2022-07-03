
#include "sensirion_sht4x.hpp"

sht4x::Sensirion_SHT4X::Sensirion_SHT4X(mcu_ab_layer::I2C& i2c_driver) {
    /* Claim shared ownership of the driver */
    this->i2c_driver_handle.reset(&i2c_driver);
    /* Using find instead of [] operator, as dereference operator can cause exceptions */
    this->output_data_buffer.push_back(this->command_palette.find("READ_SERIAL_NUMBER")->second);
    /* Check if sensor is connected and alive on the bus by asking for serial number */
    this->i2c_driver_handle->write_to_slave(this->output_data_buffer,
                                            sht4x::Sensirion_SHT4X::address,
                                            sht4x::Sensirion_SHT4X::milisec_measure_delay);
    vTaskDelay(sht4x::Sensirion_SHT4X::milisec_measure_delay / portTICK_PERIOD_MS);
    this->i2c_driver_handle->read_from_slave(this->input_data_buffer,
                                            sht4x::Sensirion_SHT4X::address,
                                            sht4x::Sensirion_SHT4X::milisec_measure_delay);
    std::pair<uint16_t, uint16_t> serial_num = this->validate_and_extract_data(
                                                                        this->input_data_buffer);
    this->serial_number = (uint32_t)std::get<0>(serial_num) << 16 | (uint32_t)std::get<1>(serial_num);
}

uint8_t sht4x::Sensirion_SHT4X::calculate_crc8(const std::vector<uint8_t>& data) {
    uint8_t crc = 0xFF;
    uint8_t loop_cnt;
    for (uint8_t byte: data) {
        crc ^= byte;
        for (loop_cnt = 0; loop_cnt < 8; loop_cnt++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)(uint8_t(crc << 1) ^ (uint8_t)0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

std::pair<uint16_t, uint16_t> sht4x::Sensirion_SHT4X::validate_and_extract_data(
                                                    const std::vector<uint8_t>& data) {
    std::vector<uint8_t> data_msb(data.begin(), data.begin() + 2);
    std::vector<uint8_t> data_lsb(data.begin() + 3, data.begin() + 5);
    uint8_t data_msb_crc = data[2];
    uint8_t data_lsb_crc = data[5];
    uint16_t msb, lsb;
    if (this->calculate_crc8(data_msb) != data_msb_crc)
        throw diagnostic::Sensirion_SHT4X_CRC8ChecksumMismatchException("MSB mismatch");
    if (this->calculate_crc8(data_lsb) != data_lsb_crc)
        throw diagnostic::Sensirion_SHT4X_CRC8ChecksumMismatchException("LSB mismatch");
    msb = (uint16_t)((uint16_t)data_msb[0] << 8) | (uint16_t)data_msb[1];
    lsb = (uint16_t)((uint16_t)data_lsb[0] << 8) | (uint16_t)data_lsb[1];
    return std::pair<uint16_t, uint16_t>(msb, lsb);
}

std::pair<float, float> sht4x::Sensirion_SHT4X::measure_humidity_temperature_blocking() {
    this->output_data_buffer.clear();
    this->output_data_buffer.push_back(
        this->command_palette.find("MEASURE_HIGH_PRECISION_MODE")->second);
    this->i2c_driver_handle->write_to_slave(this->output_data_buffer,
                                            sht4x::Sensirion_SHT4X::address,
                                            sht4x::Sensirion_SHT4X::milisec_measure_delay);
    vTaskDelay(sht4x::Sensirion_SHT4X::milisec_measure_delay / portTICK_PERIOD_MS);
    this->input_data_buffer.clear();
    this->i2c_driver_handle->read_from_slave(this->input_data_buffer,
                                            sht4x::Sensirion_SHT4X::address,
                                            sht4x::Sensirion_SHT4X::milisec_measure_delay);
    std::pair<uint16_t, uint16_t> temp_and_humidity = this->validate_and_extract_data(
                                                                        this->input_data_buffer);
    
    float humidity = (float)(std::get<1>(temp_and_humidity));
    /* First casting to signed integer, so there is no problem with sign when converting to float */
    float temperature = (float)((int16_t)std::get<0>(temp_and_humidity));
    /* According to manufacturer specification */
    humidity = -6.0f + 125.0f * (humidity / 65535.0f);
    temperature = -45.0f + 175.0f * (temperature / 65535.0f);

    return std::pair<float, float>(humidity, temperature);
}