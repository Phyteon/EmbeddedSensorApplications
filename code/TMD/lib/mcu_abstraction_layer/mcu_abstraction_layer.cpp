#include "diagnostic.hpp"
#include "mcu_abstraction_layer.hpp"

mcu_ab_layer::I2C::I2C(int i2c_port_num,
                        int intr_alloc_flags,
                        const i2c_config_t& config){

    esp_err_t init_error;
    init_error = i2c_param_config(i2c_port_num, &config);
    if (ESP_OK != init_error)
        throw diagnostic::I2C_NotInitializedException(init_error);

    init_error = i2c_driver_install(i2c_port_num,
                                    I2C_MODE_MASTER,
                                    slv_rx_buf_len,
                                    slv_tx_buf_len,
                                    intr_alloc_flags)
    if (ESP_OK != init_error)
        throw diagnostic::I2C_NotInitializedException(init_error);
    
    this->config = config;
    this->i2c_port_num = i2c_port_num;
    this->slv_rx_buf_len = slv_rx_buf_len;
    this->slv_tx_buf_len = slv_tx_buf_len;
    this->intr_alloc_flags = intr_alloc_flags;
                 
}

mcu_ab_layer::I2C::read_from_slave(std::vector<uint8_t>& data_buffer, uint8_t device_addr,
                                    TickType_t timeout) {
    esp_err_t read_error;
    read_error = i2c_master_read_from_device()

}