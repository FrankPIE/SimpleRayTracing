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
// 文件名称:		RAII.hpp
// 创建时间:		2016-06-15
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     用于支持RAII设计模式，支持make_unique
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <memory>

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T>
using UPtr = std::unique_ptr<T>;

template <typename T>
using WPtr = std::weak_ptr<T>;

class ScopeGuard
{
	using FunType = std::function<void()>;

public:
	explicit ScopeGuard(FunType on_exit_scope)
		: dismissed_(false)
		, on_exit_scope_(on_exit_scope)
	{

	}

	~ScopeGuard()
	{
		if (!dismissed_)
		{
			on_exit_scope_();
		}
	}

	void Dismiss()
	{
		dismissed_ = true;
	}

private:
	ScopeGuard(const ScopeGuard&) = delete;
	ScopeGuard& operator=(const ScopeGuard&) = delete;

private:
	bool	 dismissed_;
	FunType  on_exit_scope_;
};

#define LINENAME_CAT(name, line) name##line
#define LINENAME(name, line)	 LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback)						\
ScopeGuard LINENAME(EXIT, __LINE__)(callback)

