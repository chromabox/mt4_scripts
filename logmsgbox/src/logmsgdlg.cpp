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

#include "stdafx.h"
#include "logmsgbox.h"
#include "mt4define.h"

#include <time.h>

#ifdef _MANAGED
#pragma managed(push, off)
#endif

LRESULT CALLBACK LogMsgDlg::defDlgProc(HWND hDlg,UINT msg,WPARAM wp,LPARAM lp)
{
	LogMsgDlg *pdlg;
	if(msg == WM_INITDIALOG){
		// Dialog���N���G�C�g�����Ƃ��ɂ�����Ă�ŃN���X�̃|�C���^���Z�b�g����
		SetWindowLongPtr(hDlg,DWLP_USER,lp);
	}
	pdlg = (LogMsgDlg *)GetWindowLongPtr(hDlg,DWLP_USER);
	if(pdlg == NULL) return FALSE;

	return pdlg->MsgProc(hDlg,msg,wp,lp);
}


LRESULT  LogMsgDlg::MsgProc(HWND hDlg,UINT msg,WPARAM wp,LPARAM lp)
{
	if(msg == WM_INITDIALOG){
		return TRUE;
	}
	if(msg == WM_LOGPUTMES){
		HWND editbox = GetDlgItem(hDlg,IDC_LOGMSG_EDIT);
		SetWindowText(editbox,m_logstr.c_str());
		return TRUE;
	}

	if(msg == WM_COMMAND){
		switch(LOWORD(wp)){
			case IDCANCEL:
			case IDOK:
				ShowWindow(hDlg,SW_HIDE);
				return TRUE;
				break;
			case IDC_LOGCLEAR_BUTTON:
				m_logstr.clear();
				HWND cntr = GetDlgItem(hDlg,IDC_LOGMSG_EDIT);
				SetWindowText(cntr,m_logstr.c_str());
				return TRUE;
				break;
		}
	}
	return FALSE;
}



LogMsgDlg::LogMsgDlg()
{
	m_hDlg = NULL;
}

LogMsgDlg::~LogMsgDlg()
{
	Exit();
}

// �_�C�A���O�̍쐬���s��
bool LogMsgDlg::Create(HMODULE hmodule)
{
	InitializeCriticalSection(&m_Cs);

	m_hDlg = CreateDialogParam(hmodule,MAKEINTRESOURCE(IDD_LOGMSG_DLG),NULL,(DLGPROC)defDlgProc,(LPARAM)this);
	if(m_hDlg == NULL)	return false;

	ShowWindow(m_hDlg,SW_SHOW);
	return true;
}

// �������ꍇ�̃_�C�A���O�̔j��
bool LogMsgDlg::Exit()
{
	if(m_hDlg != NULL){
		DestroyWindow(m_hDlg);
		DeleteCriticalSection(&m_Cs);
		m_hDlg = NULL;
	}
	return true;
}

// �_�C�A���O�փ��O�̕\�����s���B
// �_�C�A���O��ł͈�ԏオ�V�������b�Z�[�W�ƂȂ�
void LogMsgDlg::LogPut(const wchar_t * mes)
{
	time_t ntime;
	struct tm tm_ntime;
	wchar_t wst_time[64];

	EnterCriticalSection(&m_Cs);

	time(&ntime);
	localtime_s(&tm_ntime,&ntime);
	_wcsftime_l(wst_time,64,L"[%Y/%m/%d %H:%M:%S] ",&tm_ntime,_get_current_locale());

	std::wstring omes;
	omes += wst_time;
	omes += mes;
	omes += L"\r\n";
	m_logstr = omes + m_logstr;
	if(m_hDlg != NULL){
		PostMessage(m_hDlg,WM_LOGPUTMES,0,0);
	}

	LeaveCriticalSection(&m_Cs);
}

