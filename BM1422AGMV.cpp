/*
 * BM1422AGMV.cpp
 *
 *  Created on: Dec 16, 2024
 *      Author: aoi25
 *
 *      基本的にデータシートに書いてある手順をそのまま書いています
 *
 */

#include <BM1422AGMV.h>

BM1422AGMV::BM1422AGMV(I2C_HandleTypeDef* i2c_pin):BM1422AGMV_HAL(i2c_pin){

}

uint8_t BM1422AGMV::verify_connection(){

	uint8_t who_am_i = 0x00;
	uint8_t error_count = 0;

	while(who_am_i != 0x41){

		BM1422AGMV_HAL::read(REGISTER::WIA, &who_am_i, 1);
		error_count ++;

	}

	return 0;
}

uint8_t BM1422AGMV::setting(BM1422AGMV::mode mode, BM1422AGMV::output_rate rate){

	//12bitmodeでのoutput_rate(odr)設定
	if(uint8_t(mode) == 0){

		uint8_t CTNL1_command = 0x80 + ((uint8_t)rate << 3);
		BM1422AGMV_HAL::write(REGISTER::CNTL1, &CTNL1_command, 1);
	}

	//14bitmodeでのoutput_rate(odr)設定
	if(uint8_t(mode) == 1){

		uint8_t CTNL1_command = 0xC0 + ((uint8_t)rate << 3);
		BM1422AGMV_HAL::write(REGISTER::CNTL1, &CTNL1_command, 1);
	}

	//CTNL4
	uint8_t CTNL4_command[2] = {};
	BM1422AGMV_HAL::write(REGISTER::CNTL4, CTNL4_command, 2);

	//CTNL2
	uint8_t CTNL2_command = 0x0C;
	BM1422AGMV_HAL::write(REGISTER::CNTL2, &CTNL2_command, 1);

	//CTNL3
	uint8_t CTNL3_command = 0x40;
	BM1422AGMV_HAL::write(REGISTER::CNTL3, &CTNL3_command, 1);

	return 0;
}

uint8_t BM1422AGMV::get_data(int16_t mag_data[3]){

	uint8_t raw_magdata[6] = {};
	BM1422AGMV_HAL::read(BM1422AGMV::REGISTER::DATA_X, raw_magdata, 6);

	if(raw_magdata[0] == 0 && raw_magdata[2] == 0 && raw_magdata[4] == 0){

		return 1; //データの受信失敗
	}

	mag_data[0]  = (int16_t)(raw_magdata[0] | raw_magdata[1] << 8);
	mag_data[1]  = (int16_t)(raw_magdata[2] | raw_magdata[3] << 8);
	mag_data[2]  = (int16_t)(raw_magdata[4] | raw_magdata[5] << 8);

	return 0;
}
