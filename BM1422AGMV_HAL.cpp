/*
 * BM1422AGMV_HAL.cpp
 *
 *  Created on: Dec 16, 2024
 *      Author: Sezakiaoi
 */

#include <BM1422AGMV_HAL.h>
#include <i2c.h>

BM1422AGMV_HAL::BM1422AGMV_HAL(I2C_HandleTypeDef *use_i2cPin){

	//使用するピンの情報を受け取る
	i2c_pin = use_i2cPin;

}

void BM1422AGMV_HAL::write(BM1422AGMV_HAL::REGISTER REGISTER_ADDR, uint8_t* command, uint8_t len){

	HAL_I2C_Mem_Write(i2c_pin, I2C_ADDR, uint8_t(REGISTER_ADDR), 1, command, len, 10);
}

void BM1422AGMV_HAL::read(BM1422AGMV_HAL::REGISTER REGISTER_ADDR, uint8_t* receive_buffer, uint8_t len){

	HAL_I2C_Mem_Read(i2c_pin, I2C_ADDR, uint8_t(REGISTER_ADDR), 1, receive_buffer, len, 10);
}
