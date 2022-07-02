
#include "mcu_abstraction_layer.hpp"

bool mcu_ab_layer::I2C::compare_config_to_default_config(const i2c_config_t& config) {
    /*!
    * To make sure there is no alignment issues, structures are compared
    * manually, field by field, instead of i.e. converting them to arrays.
    */
    if ((I2C::default_i2c_conf.clk_flags == config.clk_flags) &&
        (I2C::default_i2c_conf.mode == config.mode) &&
        (I2C::default_i2c_conf.scl_io_num == config.scl_io_num) &&
        (I2C::default_i2c_conf.sda_io_num == config.sda_io_num) &&
        (I2C::default_i2c_conf.scl_pullup_en == config.scl_pullup_en) &&
        (I2C::default_i2c_conf.sda_pullup_en == config.sda_pullup_en) &&
        (I2C::default_i2c_conf.master.clk_speed == config.master.clk_speed) &&
        (I2C::default_i2c_conf.slave.slave_addr == config.slave.slave_addr) &&
        (I2C::default_i2c_conf.slave.addr_10bit_en == config.slave.addr_10bit_en)
    ){
        return true;
    }
    else return false;
}

mcu_ab_layer::I2C::I2C(i2c_port_t i2c_port_num,
                        int intr_alloc_flags,
                        const i2c_config_t& config){
    esp_err_t init_error;

    this->config = config;
    this->i2c_port_num = i2c_port_num;
    this->intr_alloc_flags = intr_alloc_flags;

    init_error = i2c_param_config(i2c_port_num, &config);
    if (ESP_OK != init_error)
        throw diagnostic::I2C_NotInitializedException(init_error, this->get_port_data_as_str());

    /*!
    * Since master mode only is enabled, no slave rx and tx buffers are needed, hence
    * their sizes are 0, 0.
    */
    init_error = i2c_driver_install(i2c_port_num,
                                    I2C_MODE_MASTER,
                                    0,
                                    0,
                                    intr_alloc_flags);
    if (ESP_OK != init_error)
        throw diagnostic::I2C_NotInitializedException(init_error, this->get_port_data_as_str());

    mcu_ab_layer::I2CGlobalDataContainer::initialized_ports.insert(this);
                 
}

mcu_ab_layer::I2C::I2C(){
    throw diagnostic::NotImplementedException("I2C default automatic constructor");
}

mcu_ab_layer::I2C::~I2C(){
    i2c_driver_delete(this->i2c_port_num);
    mcu_ab_layer::I2CGlobalDataContainer::initialized_ports.erase(this);
}

std::string mcu_ab_layer::I2C::get_port_data_as_str() {
    std::string data {"I2C driver info:\n"};
    data += "--- Port number: ";
    data += std::to_string(this->i2c_port_num);
    data += "\n--- Initial allocation flags: ";
    data += std::to_string(this->intr_alloc_flags);
    data += "\n--- Configuration:\n";
    data += "---+--- Mode: ";
    if (I2C_MODE_MASTER == this->config.mode) {
        data += "MASTER\n";
        data += "---+--- Master config:\n";
        data += "---+---+--- Clock speed: ";
        data += std::to_string(this->config.master.clk_speed);
    }
    else if (I2C_MODE_SLAVE == this->config.mode) {
        data += "SLAVE\n";
        data += "---+--- Slave config:\n";
        data += "---+---+--- Max clock speed: ";
        data += std::to_string(this->config.slave.maximum_speed);
        data += "\n---+---+--- 10 bit address enable: ";
        if (0 == this->config.slave.addr_10bit_en)
            data += "False\n";
        else
            data += "True\n";
        data += "---+---+--- Slave address: ";
        data += std::to_string(this->config.slave.slave_addr);
    }
    else
        data += "UNINITIALIZED!";
    data += "\n";
    data += "---+--- SDA IO number: ";
    data += std::to_string(this->config.sda_io_num);
    data += "\n---+--- SDA pullup enable: ";
    if (0 == this->config.sda_pullup_en)
        data += "False\n";
    else
        data += "True\n";
    data += "---+--- SCL IO number: ";
    data += std::to_string(this->config.scl_io_num);
    data += "\n---+--- SCL pullup enable: ";
    if (0 == this->config.scl_pullup_en)
        data += "False\n";
    else
        data += "True\n";
    data += "---+--- Clock flags: ";
    data += std::to_string(this->config.clk_flags);

    return data;
}

esp_err_t mcu_ab_layer::I2C::write_to_slave(const std::vector<uint8_t>& data_buffer,
                                            uint8_t device_addr, TickType_t timeout) {
    esp_err_t write_error;
    write_error = i2c_master_write_to_device(this->i2c_port_num,
                                            device_addr,
                                            &data_buffer[0],
                                            data_buffer.size(),
                                            timeout);
    if (ESP_OK != write_error)
        throw diagnostic::I2C_MasterSlaveWriteFailedException(write_error,
                                                            this->get_port_data_as_str());
    return write_error;
}

esp_err_t mcu_ab_layer::I2C::read_from_slave(std::vector<uint8_t>& data_buffer, uint8_t device_addr,
                                            TickType_t timeout) {
    esp_err_t read_error;
    data_buffer.resize(0xFF); /*!< No more than 255 bytes are expected */
    read_error = i2c_master_read_from_device(this->i2c_port_num,
                                            device_addr,
                                            &data_buffer[0],
                                            data_buffer.size(),
                                            timeout);
    if (ESP_OK != read_error)
        throw diagnostic::I2C_MasterSlaveReadFailedException(read_error,
                                                            this->get_port_data_as_str());
    
    return read_error;

}