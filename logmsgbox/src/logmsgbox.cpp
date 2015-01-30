//
// ログ表示用ダイアログサンプル
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

LogMsgBoxMain theApp;

#ifdef _MANAGED
#pragma managed(push, off)
#endif


LogMsgBoxMain::LogMsgBoxMain()
{
}

LogMsgBoxMain::~LogMsgBoxMain()
{}

// DLLが初期化される場合に呼ばれる
bool LogMsgBoxMain::Init(HMODULE hmodule)
{
	if(! m_LogDlg.Create(hmodule)){
		MessageBox(NULL,L"作成失敗",L"LogMsgBox",MB_OK);
		return false;
	}
	return true;
}

// DLLが消される場合に呼ばれる
bool LogMsgBoxMain::Exit()
{
	m_LogDlg.Exit();
	return true;
}


void LogMsgBoxMain::LogPut(const wchar_t * mes)
{
	m_LogDlg.LogPut(mes);
}

// -----------------------------------------------------

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if(! theApp.Init(hModule)) return FALSE;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		theApp.Exit();
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

const void MQLCALL LogPuts(const wchar_t * mes)
{
	return theApp.LogPut(mes);
}
