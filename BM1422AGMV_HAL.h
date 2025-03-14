/*
 * BM1422AGMV_HAL.h
 *
 *  Created on: Dec 16, 2024
 *      Author: Sezakiaoi
 */

#ifndef INC_BM1422AGMV_HAL_H_
#define INC_BM1422AGMV_HAL_H_

#include "i2c.h"
#include "BM1422AGMV.h"

class BM1422AGMV_HAL: public BM1422AGMV{

	public:

		BM1422AGMV_HAL(I2C_HandleTypeDef* I2cPin);

		void Write(BM1422AGMV::REGISTER REGADDR, uint8_t *TxBuffer, uint8_t Len);
		void Read(BM1422AGMV::REGISTER REGADDR, uint8_t *RxBuffer, uint8_t Len);

	private:

		uint8_t I2CADDR = 0b0001110 << 1;
		I2C_HandleTypeDef* I2cPin;
};

#endif /* INC_BM1422AGMV_HAL_H_ */
