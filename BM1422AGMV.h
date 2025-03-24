/*
 * BM1422AGMV.h
 *
 *  Created on: Dec 16, 2024
 *      Author: aoi25
 */

#ifndef INC_BM1422AGMV_H_
#define INC_BM1422AGMV_H_

#include <cstdint>

class BM1422AGMV{

	public:

		enum class REGISTER: uint8_t{

			WIA 	= 0x0F,
			DATA_X  = 0x10,
			STA1    = 0x18,
			CNTL1   = 0x1B,
			CNTL2   = 0x1C,
			CNTL3   = 0x1D,
			CNTL4   = 0x5C,
		};

		enum class Mode: uint8_t{

			Scale12Bit = 0x00,
			Scale14Bit,
		};

		enum class ODR: uint8_t{

			Rate10Hz = 0x00,
			Rate20Hz,
			Rate100Hz,
			Rate1000Hz
		};

		uint8_t Connection();
		uint8_t Setting(BM1422AGMV::Mode, BM1422AGMV::ODR);
		uint8_t GetData(int16_t MagData[3]);

	private:

		virtual void Write(BM1422AGMV::REGISTER, uint8_t* TxBuffer, uint8_t Len){}
		virtual void Read(BM1422AGMV::REGISTER, uint8_t* RxBuffer, uint8_t Len){}
};

#endif /* INC_BM1422AGMV_H_ */
