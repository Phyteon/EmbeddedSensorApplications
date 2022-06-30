#include "diagnostic.hpp"
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
    if (I2C::compare_config_to_default_config(config))
        init_error = i2c_param_config(i2c_port_num, &I2C::default_i2c_conf);
    else
        init_error = i2c_param_config(i2c_port_num, &config);
    if (ESP_OK != init_error)
        throw diagnostic::I2C_NotInitializedException(init_error);

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
        throw diagnostic::I2C_NotInitializedException(init_error);
    
    this->config = config;
    this->i2c_port_num = i2c_port_num;
    this->intr_alloc_flags = intr_alloc_flags;
                 
}

esp_err_t mcu_ab_layer::I2C::read_from_slave(std::vector<uint8_t>& data_buffer, uint8_t device_addr,
                                            TickType_t timeout) {
    esp_err_t read_error;
    data_buffer.resize(0xFF); /*!< No more than 256 bytes are expected */
    read_error = i2c_master_read_from_device(this->i2c_port_num,
                                            device_addr,
                                            &data_buffer[0],
                                            data_buffer.size(),
                                            timeout);
    if (ESP_OK != read_error)
        throw diagnostic::I2C_MasterSlaveReadFailedException(read_error);
    
    return read_error;

}