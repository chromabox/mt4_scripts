//
// 線の種類を変更できるボリンジャーバンド
// このインディケータだけで±３αまで指定可能
//
// The MIT License (MIT)
//
// Copyright (c) <2015> chromabox <chromarockjp@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#property copyright "chromabox"
#property version "0.1"
#property link "https://github.com/chromabox/mt4_scripts"
#property description "CBX Bollinger Bands"
#property strict

// 設定変数たち
#property indicator_chart_window
#property indicator_buffers 7
#property indicator_color1 Aqua
#property indicator_color2 LightSeaGreen
#property indicator_color3 LightSeaGreen
#property indicator_color4 MediumSpringGreen
#property indicator_color5 LightSeaGreen
#property indicator_color6 LightSeaGreen
#property indicator_color7 Red

#property indicator_style1 2
#property indicator_style2 2
#property indicator_style3 2
#property indicator_style4 0
#property indicator_style5 2
#property indicator_style6 2
#property indicator_style7 2

input int    InpBandsPeriod=20;      // 期間
input int    InpBandsShift=0;        // シフト
input double InpBandsDeviations_1=1.0; // ±１α
input double InpBandsDeviations_2=2.0; // ±２α
input double InpBandsDeviations_3=3.0; // ±３α
input bool   InpUseDeviations_1=false; // ±１αを使用する
input bool   InpUseDeviations_2=true; // ±２αを使用する
input bool   InpUseDeviations_3=true; // ±３αを使用する
input ENUM_MA_METHOD InpMAMethod=MODE_SMA;	// 移動平均法の種類
input ENUM_APPLIED_PRICE InpMAPrice=PRICE_CLOSE; // 適用価格

double MABuf[];
double UpperBuf1[];
double LowerBuf1[];
double UpperBuf2[];
double LowerBuf2[];
double UpperBuf3[];
double LowerBuf3[];


// 初期化
int OnInit(void)
{
	IndicatorBuffers(7);
	IndicatorDigits(Digits);
	
	// +3aライン
	if(InpUseDeviations_3){
		SetIndexStyle(0,DRAW_LINE);
		SetIndexBuffer(0,UpperBuf3);
		SetIndexShift(0,InpBandsShift);
		SetIndexLabel(0,"CBX_BB_3Upper");
	}
	// +2aライン
	if(InpUseDeviations_2){
		SetIndexStyle(1,DRAW_LINE);
		SetIndexBuffer(1,UpperBuf2);
		SetIndexShift(1,InpBandsShift);
		SetIndexLabel(1,"CBX_BB_2Upper");
	}
	// +1aライン
	if(InpUseDeviations_1){
		SetIndexStyle(2,DRAW_LINE);
		SetIndexBuffer(2,UpperBuf1);
		SetIndexShift(2,InpBandsShift);
		SetIndexLabel(2,"CBX_BB_1Upper");
	}
	// 0ライン
	SetIndexStyle(3,DRAW_LINE);
	SetIndexBuffer(3,MABuf);
	SetIndexShift(3,InpBandsShift);
	SetIndexLabel(3,"CBX_BB_SMA");
	// -1aライン
	if(InpUseDeviations_1){
		SetIndexStyle(4,DRAW_LINE);
		SetIndexBuffer(4,LowerBuf1);
		SetIndexShift(4,InpBandsShift);
		SetIndexLabel(4,"CBX_BB_1Lower");
	}
	// -2aライン	
	if(InpUseDeviations_2){
		SetIndexStyle(5,DRAW_LINE);
		SetIndexBuffer(5,LowerBuf2);
		SetIndexShift(5,InpBandsShift);
		SetIndexLabel(5,"CBX_BB_2Lower");
	}
	// -3aライン	
	if(InpUseDeviations_3){
		SetIndexStyle(6,DRAW_LINE);
		SetIndexBuffer(6,LowerBuf3);
		SetIndexShift(6,InpBandsShift);
		SetIndexLabel(6,"CBX_BB_3Lower");
	}
	
	if(InpBandsPeriod<=0){
		Print("Wrong input parameter Bands Period=",InpBandsPeriod);
		return(INIT_FAILED);
	}
	if(InpUseDeviations_3) SetIndexDrawBegin(0,InpBandsPeriod+InpBandsShift);
	if(InpUseDeviations_2) SetIndexDrawBegin(1,InpBandsPeriod+InpBandsShift);
	if(InpUseDeviations_1) SetIndexDrawBegin(2,InpBandsPeriod+InpBandsShift);
	SetIndexDrawBegin(3,InpBandsPeriod+InpBandsShift);
	if(InpUseDeviations_1) SetIndexDrawBegin(4,InpBandsPeriod+InpBandsShift);
	if(InpUseDeviations_2) SetIndexDrawBegin(5,InpBandsPeriod+InpBandsShift);
	if(InpUseDeviations_3) SetIndexDrawBegin(6,InpBandsPeriod+InpBandsShift);
	return(INIT_SUCCEEDED);
}


int OnCalculate(const int rates_total,
				const int prev_calculated,
				const datetime &time[],
				const double &open[],
				const double &high[],
				const double &low[],
				const double &close[],
				const long &tick_volume[],
				const long &volume[],
				const int &spread[])
{
	int i,pos;
	double sqdev,sqres;
	if(rates_total <= InpBandsPeriod)	return(0);

	// 初めてのときの初期化
	if(prev_calculated<1){
		for(i=0; i<InpBandsPeriod; i++){
			MABuf[i]=EMPTY_VALUE;
			if(InpUseDeviations_1){
				UpperBuf1[i]=EMPTY_VALUE;
				LowerBuf1[i]=EMPTY_VALUE;
			}
			if(InpUseDeviations_2){
				UpperBuf2[i]=EMPTY_VALUE;
				LowerBuf2[i]=EMPTY_VALUE;
			}
			if(InpUseDeviations_3){
				UpperBuf3[i]=EMPTY_VALUE;
				LowerBuf3[i]=EMPTY_VALUE;
			}
		}
	}
	pos = rates_total - prev_calculated - 1;
	// 更新が無いときはしない
	if(pos < 0) return(rates_total);

	for(i=pos ; i >= 0 ;i--){
		// 中央線(移動平均)を計算
		MABuf[i]=iMA(NULL,0,InpBandsPeriod,InpBandsShift,InpMAMethod,InpMAPrice,i);
		// 標準偏差を求める。ちょっと無駄だけど仕方なし
		sqdev = iStdDev(NULL,0,InpBandsPeriod,InpBandsShift,InpMAMethod,InpMAPrice,i);
		if(InpUseDeviations_1){
			sqres = InpBandsDeviations_1 * sqdev;
			UpperBuf1[i] = MABuf[i] + sqres;
			LowerBuf1[i] = MABuf[i] - sqres;
		}
		if(InpUseDeviations_2){
			sqres = InpBandsDeviations_2 * sqdev;
			UpperBuf2[i] = MABuf[i] + sqres;
			LowerBuf2[i] = MABuf[i] - sqres;
		}
		if(InpUseDeviations_3){
			sqres = InpBandsDeviations_3 * sqdev;
			UpperBuf3[i] = MABuf[i] + sqres;
			LowerBuf3[i] = MABuf[i] - sqres;
		}
	}
	return(rates_total);
}

