# STM32_BM1422AGMV

クラス設計を修正

あんまりきれいなコードじゃないけどご自由に使ってください！

i2c通信のみ対応しています

## サンプルコード

初回に1度実行される部分と、ループする部分に分けて書いてあります

それぞれの環境に合わせて使ってください

```cpp
#include "BM1422AGMV_HAL.h"

//使用するi2cのピンを設定
BM1422AGMV bm(&hi2c2);

int16_t mag_data[3] = {};

//1回のみ実行される部分
void init(){

	bm.verify_connection();
	bm.setting(bm.mode::scale_14bit, bm.output_rate::rate_1000hz);
}

//whileでループする部分
void loop(){

	bm.get_data(mag_data);
}
```

## setting()について

センサーの基本的な設定をしています

#### 第1引数 出力のスケール
```cpp
scale_12bit
scale_14bit
```

#### 第2引数 出力レート(ODR)
```cpp
rate_10hz 
rate_20hz
rate_100hz
rate_1000hz
```

## get_data()について

int16でx,y,zの順番に値を出力します

int16型の3要素を持つ配列のポインタを渡してください

## ファイルとクラスについて

### BM1422AGMV_HAL 

STM32を使った通信を定義しています

### BM1422AGMG

センターに対する操作が書かれています

レジスタアドレスや設定項目はこのクラスに書かれています

## 修正や改善をしたい場合

データシートがとても読みやすい（日本語&説明丁寧）ので、こちらを読むことを推奨します

https://akizukidenshi.com/goodsaffix/BM1422AGMV.pdf

setting()の中身は、p16の説明をコードにしたものになります

（いっぱい書いてあるけど、データシートに沿って書くだけです！）

## その他

BM1422AGMV::Connection()が成功していないと設定やデータ取得ができないため

実際のプロジェクトで使用する場合は、この関数の戻り値を確認してください

