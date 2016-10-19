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
// 文件名称:		App.cpp
// 创建时间:		2016-10-19
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     Application
// 
//////////////////////////////////////////////////////////////////////////

#include "App.h"

#include "resource.h"
#include "RAII.hpp"

App::App(const std::wstring& name, const DWORD style, const RECT& rect, const HWND parent, const UINT id)
	: m_active_(false)
	, m_instance_(nullptr)
	, m_hwnd_(nullptr)
{
	auto instance = ::GetModuleHandle(nullptr);

	WNDCLASSEXW wndcls = { 0 };
	wndcls.cbSize = sizeof(WNDCLASSEX);

	wndcls.style		 = CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc   = wnd_proc;
	wndcls.cbWndExtra	 = sizeof(this);
	wndcls.hInstance	 = instance;
	wndcls.hIcon		 = LoadIcon(instance, MAKEINTRESOURCE(IDC_ICON));
	wndcls.hCursor		 = LoadCursor(nullptr, IDC_ARROW);
	wndcls.hbrBackground = static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
	wndcls.lpszMenuName  = MAKEINTRESOURCE(IDR_APP_MENU);
	wndcls.lpszClassName = name.c_str();
	wndcls.hIconSm		 = LoadIcon(wndcls.hInstance, MAKEINTRESOURCE(IDC_ICON));

	if (RegisterClassEx(&wndcls) == 0)
	{
		auto error = ::GetLastError();

		printf("Error Code : %d", error);		
	}

	ScopeGuard rollback([&]{ ::UnregisterClass(name.c_str(), instance); });

	m_hwnd_ = ::CreateWindow(name.c_str(), name.c_str(), style,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, this);

	if (m_hwnd_ == nullptr)
	{
		auto error = ::GetLastError();

		printf("Error Code : %d", error);
	}
	else
	{
		::SetWindowLongPtr(m_hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));		
	}

	::ShowWindow(m_hwnd_, SW_SHOW);
	::UpdateWindow(m_hwnd_);

	rollback.Dismiss();

	MSG msg = { nullptr };

	while (WM_QUIT != msg.message)
	{
		auto got_msg = m_active_ ?
		(::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0) :
		(::GetMessage(&msg, nullptr, 0, 0) != 0);

		if (got_msg)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

App::~App()
{
	if (m_hwnd_)
	{
		::DestroyWindow(m_hwnd_);
		m_hwnd_ = nullptr;
	}
}

LRESULT App::wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	App *app_ptr = reinterpret_cast<App*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (app_ptr)
	{
		return app_ptr->proc(hwnd, msg, wparam, lparam);
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

LRESULT App::proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		m_active_ = (WA_INACTIVE != LOWORD(wparam));
		break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}
