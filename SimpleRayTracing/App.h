////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 BoXiang.Pei
//
// Permission is hereby granted, free of charge,
// to any person obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//　　
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.	
//
// 文件名称:		App.h
// 创建时间:		2016-10-19
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     Application
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

#include <Windows.h>
#include <atlimage.h>

#include <vector>
#include <thread>

#include "RAII.hpp"

class FrameBuffer;

class App
{
public:
	App(const std::wstring& name, const DWORD style, const RECT& rect, const HWND parent = nullptr, const UINT id = 0);
	~App();

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static void Render(void* ctx);

	void TerminateRenderThread();

	LRESULT Proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void OnIdle();

private:
	bool		active_;
	HINSTANCE	instance_;
	HWND		hwnd_;	

	HDC			memory_dc_;
	HBITMAP		bitmap_;
	HBITMAP		background_;

	UPtr<std::thread> render_thread_;

	UPtr<FrameBuffer> buffer_;
};

