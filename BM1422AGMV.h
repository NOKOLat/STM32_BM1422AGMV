/*
 * BM1422AGMV.h
 *
 *  Created on: Dec 16, 2024
 *      Author: aoi25
 */

#ifndef INC_BM1422AGMV_H_
#define INC_BM1422AGMV_H_

#include "BM1422AGMV_HAL.h"

class BM1422AGMV : private BM1422AGMV_HAL{

	public:

		enum class mode: uint8_t{

			scale_12bit = 0x00,
			scale_14bit
		};

		enum class output_rate: uint8_t{

			rate_10hz = 0x00,
			rate_20hz,
			rate_100hz,
			rate_1000hz
		};

		BM1422AGMV(I2C_HandleTypeDef* i2c_pin);

		uint8_t verify_connection();
		uint8_t setting(BM1422AGMV::mode, BM1422AGMV::output_rate);
		uint8_t get_data(int16_t mag_buffer[3]);

	private:

		I2C_HandleTypeDef* i2c_pin;
};

#endif /* INC_BM1422AGMV_H_ */
