//
// Spread�����C���`���[�g�ɕ\������
// �w��l�ȏ�ɑ傫���Ȃ�ƐF��ς���
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

#property indicator_chart_window

// �ݒ�ϐ�����
// �����ݒ�ł́A1Pips������100Point�A�����ʒu�̓`���[�g�E��[�ASpread�x����1.0�ȏ�
// Spread�x����Pips�P�ʂŎw�肷�邱��
extern int Pips_To_Point = 100; 
extern color Label_Normal_Color = Aqua;
extern color Label_High_Color = Yellow;
extern int Label_Corners = 1;
extern int Label_XDistance = 1;
extern int Label_YDistance = 1;
extern double HighSpread = 1.0;

// ������
int init()
{
	ObjectCreate("CBX_SPREAD_LABEL",OBJ_LABEL,0,0,0);
	ObjectSet("CBX_SPREAD_LABEL",OBJPROP_CORNER,Label_Corners);
	ObjectSet("CBX_SPREAD_LABEL",OBJPROP_XDISTANCE,Label_XDistance);
	ObjectSet("CBX_SPREAD_LABEL",OBJPROP_YDISTANCE,Label_YDistance);
	
	return (0);
}

// �I��
int deinit()
{
	DeleteMyObject();
	return (0);
}

int start()
{
	double spread;
	color lcolor;
	string outtext;
	spread = (Ask - Bid) * Pips_To_Point;
	outtext = StringConcatenate("Spread : ",spread);
//	Comment(outtext);
	
	if(HighSpread > spread){
		lcolor = Label_Normal_Color;
	}else{
		lcolor = Label_High_Color;
	}
	ObjectSetText("CBX_SPREAD_LABEL",outtext,12,NULL,lcolor);
	
	return (0);
}

// ���̃X�N���v�g�ō쐬�����I�u�W�F�N�g������
void DeleteMyObject()
{
	int i;
	for(i=ObjectsTotal();i>=0;i--){
		string ObjName=ObjectName(i);
		if(StringFind(ObjName,"CBX_SPREAD_",0) != 0){
			ObjectDelete(ObjName);
		}
	}
}


