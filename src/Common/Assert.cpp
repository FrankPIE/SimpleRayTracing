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
// 文件名称:		Assert.cpp
// 创建时间:		2015-09-16
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     调试器实现文件
// 
//////////////////////////////////////////////////////////////////////////

#include "Assert.hpp"

#ifdef WIN32
#include <Windows.h>
#endif

void Assert::warn(const std::string& warn_msg) 
{
	dump_ 
		<< "Warning : " << warn_msg.c_str()  
		<< std::endl;
}

void Assert::debug(const std::string& debug_msg)
{
	dump_ 
		<< "Debug : " << debug_msg.c_str() 
		<< std::endl;

#ifdef WIN32
	auto IDD = 
		::MessageBoxA(nullptr, dump_.str().c_str(), "Assert Box", MB_ABORTRETRYIGNORE | MB_ICONERROR);

	switch (IDD)
	{
	case IDABORT:
		::ExitProcess(-1);

	case IDRETRY:
		::DebugBreak();
		break;

	case IDIGNORE:
		break;

	default:
		break;
	}
#endif
}

void Assert::fatal(const std::string& fatal_msg)
{
	dump_ 
		<< "Fatal : " << fatal_msg.c_str() 
		<< std::endl;

#ifdef WIN32
	MessageBoxA(nullptr, dump_.str().c_str(), "Error", MB_OK | MB_ICONERROR);
#endif

	ExitProcess(-1);
}

Assert& Assert::print_context(const std::string& file, const int line)
{
	dump_ 
		<< "File location : " << file.c_str() 
		<< "\n"
		<< "Line location : " << line 
		<< std::endl;

	return *this;
}
