/*
 * BM1422AGMV_HAL.cpp
 *
 *  Created on: Dec 16, 2024
 *      Author: Sezakiaoi
 */

#include <BM1422AGMV_HAL.h>

BM1422AGMV_HAL::BM1422AGMV_HAL(I2C_HandleTypeDef* I2cPin){

	//使用するピンの情報を受け取る
	this->I2cPin = I2cPin;

}

void BM1422AGMV_HAL::Write(BM1422AGMV::REGISTER REGADDR, uint8_t *TxBuffer, uint8_t Len){

	HAL_I2C_Mem_Write(I2cPin, I2CADDR, (uint8_t)REGADDR, 1, TxBuffer, Len, 100);
}

void BM1422AGMV_HAL::Read(BM1422AGMV::REGISTER REGADDR, uint8_t *RxBuffer, uint8_t Len){

	HAL_I2C_Mem_Read(I2cPin, I2CADDR, (uint8_t)REGADDR, 1, RxBuffer, Len, 100);
}
