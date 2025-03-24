/*
 * BM1422AGMV.cpp
 *
 *  Created on: Dec 16, 2024
 *      Author: aoi25
 *
 *      基本的にデータシートに書いてある手順をそのまま書いています
 *		https://www.marutsu.co.jp/contents/shop/marutsu/datasheet/BM1422AGMV-ZE2.pdf?srsltid=AfmBOoqfdOcrsayBjkr4m8f85_AMl4rc7Bt3exxuVXZ_LP84yWsz81PN
 */

#include <BM1422AGMV.h>

/* @brief 通信チェック
 *
 * WIAレジスタを読んで、値をチェックします
 *
 * 最大で100回の再試行をします
 *
 *@return uint8_t 0: 接続成功、1: 通信失敗
 */
uint8_t BM1422AGMV::Connection(){

	uint8_t ProductId = 0x00;
	uint8_t ErrorCount = 0;

	//WHO_AM_I 0x41なら成功
	while(ProductId != 0x41){

		Read(REGISTER::WIA, &ProductId , 1);
		ErrorCount ++;

		if(ErrorCount > 100){

			return 1;
		}
	}

	return 0;
}

/* @brief センサー設定の設定
 *
 * CNTL1~4レジスタに値を書き込みます
 *
 * @param Mode 12Bit、14Bit出力を選べます
 * @param ODR  出力レートを設定できます
 *
 *　@return uint8_t 0: 接続成功
 *
 *　Connectionが成功していれば失敗しないはずです
 */
uint8_t BM1422AGMV::Setting(BM1422AGMV::Mode Mode, BM1422AGMV::ODR ODR){

	//出力モードとODRの設定
	uint8_t CNTL1_Command = 0x00;
	uint8_t CNTL1_Mode = 0x00;
	uint8_t CNTL1_Error = 0;

	if(uint8_t(Mode) == 0){

		//12BitMode
		CNTL1_Command = 0x80 + ((uint8_t)ODR << 3);
	}
	else{

		//14BitMode
		CNTL1_Command = 0xC0 + ((uint8_t)ODR << 3);
	}

	//値が一致するまで書き込み
	while(CNTL1_Mode != CNTL1_Command){

		Write(REGISTER::CNTL1, &CNTL1_Command, 1);
		Read(REGISTER::CNTL1, &CNTL1_Mode, 1);

		CNTL1_Error ++;
		if(CNTL1_Error > 100){

			return 1;
		}
	}

	//CNTL4 リセット解除
	//0x00を連続する2つのレジスタに書き込む（リセット解除）
	uint8_t CNTL4_Command[2] = {};
	uint8_t CNTL4_Mode[2] = {0xff, 0xff};
	uint8_t CNTL4_Error = 0;

	while(CNTL4_Mode[0] != CNTL4_Command[0] || CNTL4_Mode[1] != CNTL4_Command[1]){

		Write(REGISTER::CNTL4, CNTL4_Command, 2);
		Read(REGISTER::CNTL4, CNTL4_Mode, 2);

		CNTL4_Error ++;
		if(CNTL4_Error > 100){

			return 2;
		}
	}

	//CNTL2 DataReadyの有効化
	uint8_t CNTL2_Command = 0x0C;
	uint8_t CNTL2_Mode = 0x00;
	uint8_t CNTL2_Error = 0;

	while(CNTL2_Command != CNTL2_Mode){

		Write(REGISTER::CNTL2, &CNTL2_Command, 1);
		Read(REGISTER::CNTL2, &CNTL2_Mode, 1);

		CNTL2_Error ++;
		if(CNTL2_Error > 100){

			return 3;
		}
	}

	//CNTL3 　測定モードの設定
	uint8_t CNTL3_Command = 0x40;
	uint8_t CNTL3_Mode = 0x00;
	uint8_t CNTL3_Error = 0;

	while(CNTL3_Command != CNTL3_Mode){

		Write(REGISTER::CNTL3, &CNTL3_Command, 1);
		Read(REGISTER::CNTL3, &CNTL3_Mode, 1);

		CNTL3_Error ++;
		if(CNTL3_Error > 100){

			return 4;
		}
	}

	return 0;
}

/* @brief センサーデータの取得
 *
 * DATA_Xレジスタから6Byteを読み値を出力します
 *
 * @param int16_t MagData データを入れる配列
 *
 *@return uint8_t 0: 通信成功, 1: 通信失敗
 */
uint8_t BM1422AGMV::GetData(int16_t MagData[3]){

	uint8_t RawData[6] = {};

	//DATA_Xから6Byteを読む
	Read(BM1422AGMV::REGISTER::DATA_X, RawData, 6);

	//通信失敗
	if(RawData[0] == 0 && RawData[2] == 0 && RawData[4] == 0){

		return 1;
	}

	//通信成功
	MagData[0]  = (int16_t)(RawData[0] | RawData[1] << 8);
	MagData[1]  = (int16_t)(RawData[2] | RawData[3] << 8);
	MagData[2]  = (int16_t)(RawData[4] | RawData[5] << 8);

	return 0;
}
