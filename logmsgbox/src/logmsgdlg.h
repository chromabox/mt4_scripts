//
// ���O�\���p�_�C�A���O�N���X
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

#include "resource.h"		// ���C�� �V���{��
#include "mt4define.h"
#include <string>

class LogMsgDlg
{
protected:
	CRITICAL_SECTION	m_Cs;			// �\���N���e�B�J���Z�N�V����
	HWND				m_hDlg;			// �_�C�A���O����

	std::wstring		m_logstr;		// ���O�\���p

	LRESULT  MsgProc(HWND hDlg,UINT msg,WPARAM wp,LPARAM lp);
	static LRESULT CALLBACK defDlgProc(HWND hDlg,UINT msg,WPARAM wp,LPARAM lp);

public:
	LogMsgDlg();
	~LogMsgDlg();

// �I�[�o�[���C�h
public:
	virtual bool Create(HMODULE hmodule);
	virtual bool Exit();
	void LogPut(const wchar_t * mes);
};

#define WM_LOGPUTMES (WM_USER+3)
