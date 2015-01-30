//
// MT4�Ŏg�p�����\���̂̋��ʒ�`
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

#pragma once

// MT4�Ŏg�p���������f�[�^��`�������Œ�`����

#pragma pack(push,1)
struct RateInfo
{
	__int64				ctm;		// Period start time
	double				open;		// Open price
	double				low;		// The highest price of the period
	double				high;		// The lowest price of the period
	double				close;		// Close price
	unsigned __int64	vol_tick;	// Tick volume
	int					spread;		// Spread
	unsigned __int64	vol_real;	// Trade volume
};
#pragma pack(pop)
//---
struct MqlStr
{
	int				len;			// Length
	wchar_t			*string;		// Strings(Build600����ς����)
	int				padding;		// Padding(Build600����ς����)
};

// �G�N�X�|�[�g����ׂ��֐��͂���𓪂ɂ��邱��
#define MQLCALL __stdcall
