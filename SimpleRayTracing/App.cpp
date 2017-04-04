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

#include <mutex>

#include "resource.h"

#include "FrameBuffer.h"
#include "MathType.h"

namespace {
struct BitmapInfo
{
	BitmapInfo(long width, long height)
	{
		ZeroMemory(&info, sizeof(BITMAPINFO));

		info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biHeight = -height;
		info.bmiHeader.biWidth = width;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biSizeImage = 0;
	}

	BITMAPINFO info;
};
	
std::mutex  cMutex;
}

App::App(const std::wstring& name, const DWORD style, const RECT& rect, const HWND parent, const UINT id)
	: active_(false)
	, instance_(nullptr)
	, hwnd_(nullptr)
	, memory_dc_(nullptr)
	, bitmap_(nullptr)
{
	auto instance = ::GetModuleHandle(nullptr);

	WNDCLASSEXW wndcls = { 0 };
	wndcls.cbSize = sizeof(WNDCLASSEX);

	wndcls.style		 = CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc   = WndProc;
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

	hwnd_ = ::CreateWindow(name.c_str(), name.c_str(), style,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, this);

	if (hwnd_ == nullptr)
	{
		auto error = ::GetLastError();

		printf("Error Code : %d", error);
	}
	else
	{
		::SetWindowLongPtr(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));		
	}

	HDC dc = ::GetDC(hwnd_);

	background_ = LoadBitmap(instance, MAKEINTRESOURCE(IDB_BK));

	memory_dc_ = CreateCompatibleDC(dc);

	ReleaseDC(hwnd_, dc);

	::ShowWindow(hwnd_, SW_SHOW);
	::UpdateWindow(hwnd_);

	rollback.Dismiss();

	MSG msg = { nullptr };

	while (WM_QUIT != msg.message)
	{
		auto got_msg = active_ ?
		(::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0) :
		(::GetMessage(&msg, nullptr, 0, 0) != 0);

		if (got_msg)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		OnIdle();
	}
}

App::~App()
{
	if (hwnd_)
	{
		::DestroyWindow(hwnd_);
		hwnd_ = nullptr;
	}
}

void App::OnIdle()
{
	if (hwnd_)
	{
		RECT client_rect;
		::GetClientRect(hwnd_, &client_rect);

		auto width = client_rect.right - client_rect.left;
		auto height = client_rect.bottom - client_rect.top;

		static BitmapInfo bitmap_info(width, height);

		HDC dc = ::GetDC(hwnd_);

		if (buffer_)
		{
			std::unique_lock<std::mutex> lock(cMutex);
			SetDIBits(dc, bitmap_, 0, buffer_->GetHeight(), buffer_->Data(), (BITMAPINFO*)&bitmap_info.info, DIB_RGB_COLORS);
			lock.unlock();

			BitBlt(dc, 0, 0, width, height, memory_dc_, 0, 0, SRCCOPY);
		}
		else
		{
			auto backgroud_dc_ = CreateCompatibleDC(dc);

			SelectObject(backgroud_dc_, background_);

			for (auto x = 0; x < width; x += 20)
			{
				for (auto y = 0; y < height; y += 20)
				{
					BitBlt(dc, x, y, 20, 20, backgroud_dc_, 0, 0, SRCCOPY);
				}
			}

			DeleteDC(backgroud_dc_);
		}
		
		ReleaseDC(hwnd_, dc);
	}
}

LRESULT App::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	auto *app_ptr = reinterpret_cast<App*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (app_ptr)
	{
		return app_ptr->Proc(hwnd, msg, wparam, lparam);
	}

	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

void App::Render( void *ctx )
{
	auto* context = static_cast<App*>(ctx);

	if (context)
	{
		RECT client_rect;
		::GetClientRect(context->hwnd_, &client_rect);

		auto width  = client_rect.right  - client_rect.left;
		auto height = client_rect.bottom - client_rect.top;

		if (context->buffer_)
		{
			context->buffer_->Clear();
			context->buffer_->Resize(width, height);
		}
		else
		{
			context->buffer_ = std::make_unique<FrameBuffer>(width, height);
		}

		if (context->buffer_)
		{
			math3D::double3 lower_left_corner(-2.0, -1.0, -1.0);
			math3D::double3 horizontal(2.0, 0.0, 0.0);
			math3D::double3 vertical(0.0, 2.0, 0.0);
			math3D::double3 origin(0.0, 0.0, 0.0);

			for (auto x = 0L; x < context->buffer_->GetWidth(); ++x)
			{
				for (auto y = 0L; y < context->buffer_->GetHeight(); ++y)
				{
					float u = float(x) / float(context->buffer_->GetWidth());
					float v = float(y) / float(context->buffer_->GetHeight());

					math3D::RayD ray(origin, lower_left_corner + u * horizontal + v * vertical);

					math3D::double3 unit_direction = normalize(ray.direction);

					double t = 0.5 * (unit_direction.y() + 1.0);

					math3D::double3 c = (1. - t) * math3D::double3(1., 1., 1.) + t * math3D::double3(0.5, 0.7, 1.);

					std::lock_guard<std::mutex> lock(cMutex);

					context->buffer_->SetColor(math3D::Color(float(c.x()), float(c.y()), float(c.z()), 1.0f), x, y);
				}
			}
		}
	}
}

void App::TerminateRenderThread()
{
	if (render_thread_)
	{
		render_thread_.reset();
	}
}

LRESULT App::Proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_COMMAND:
		{
			switch (LOWORD(wparam))
			{
			case ID_BEGIN_RENDER:	//Begin Render
				TerminateRenderThread();

				if (!render_thread_)
				{
					render_thread_ = std::make_unique<std::thread>(Render, this);
	
					render_thread_->detach();
				}
				break;

			default:
				break;
			}
		}
		break;

	case WM_SIZE:
		{
			auto cx = LOWORD(lparam);
			auto cy = HIWORD(lparam);

			//创建一个窗口大小的位图
			if (!bitmap_)
			{
				DeleteObject(bitmap_);
				bitmap_ = nullptr;
			}

			HDC dc = ::GetDC(hwnd);

			bitmap_ = ::CreateCompatibleBitmap(dc, cx, cy); 

			::ReleaseDC(hwnd, dc);

			::SelectObject(memory_dc_, bitmap_);
		}
		break;

	case WM_ACTIVATE:
		active_ = (WA_INACTIVE != LOWORD(wparam));
		break;

	case WM_DESTROY:
		TerminateRenderThread();

		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}
