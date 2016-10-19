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

#ifndef CPP0X_CORE_VARIADIC_TEMPLATES
#	define MOVE_I0 
#	define MOVE_I1 ,
#	define MOVE_I2 ,
#	define MOVE_I3 ,
#	define MOVE_I4 ,
#	define MOVE_I5 , 
#	define MOVE_I6 ,
#	define MOVE_I7 ,
#	define MOVE_I8 ,
#	define MOVE_I9 ,

#	define MOVE_CLASS0
#	define MOVE_CLASS1 class Arg0
#	define MOVE_CLASS2 MOVE_CLASS1, class Arg1
#	define MOVE_CLASS3 MOVE_CLASS2, class Arg2
#	define MOVE_CLASS4 MOVE_CLASS3, class Arg3
#	define MOVE_CLASS5 MOVE_CLASS4, class Arg4
#	define MOVE_CLASS6 MOVE_CLASS5, class Arg5
#	define MOVE_CLASS7 MOVE_CLASS6, class Arg6
#	define MOVE_CLASS8 MOVE_CLASS7, class Arg7
#	define MOVE_CLASS9 MOVE_CLASS8, class Arg8

#	define MOVE_FWD0
#	define MOVE_FWD1 ::std::forward<Arg0>(arg0)
#	define MOVE_FWD2 MOVE_FWD1, ::std::forward<Arg1>(arg1)
#	define MOVE_FWD3 MOVE_FWD2, ::std::forward<Arg2>(arg2)
#	define MOVE_FWD4 MOVE_FWD3, ::std::forward<Arg3>(arg3)
#	define MOVE_FWD5 MOVE_FWD4, ::std::forward<Arg4>(arg4)
#	define MOVE_FWD6 MOVE_FWD5, ::std::forward<Arg5>(arg5)
#	define MOVE_FWD7 MOVE_FWD6, ::std::forward<Arg6>(arg6)
#	define MOVE_FWD8 MOVE_FWD7, ::std::forward<Arg7>(arg7)
#	define MOVE_FWD9 MOVE_FWD8, ::std::forward<Arg8>(arg8)

#	define FWD_REF(T) T&&

#	define MOVE_UREF0
#	define MOVE_UREF1 FWD_REF(Arg0) arg0
#	define MOVE_UREF2 MOVE_UREF1, FWD_REF(Arg1) arg1
#	define MOVE_UREF3 MOVE_UREF2, FWD_REF(Arg2) arg2
#	define MOVE_UREF4 MOVE_UREF3, FWD_REF(Arg3) arg3
#	define MOVE_UREF5 MOVE_UREF4, FWD_REF(Arg4) arg4
#	define MOVE_UREF6 MOVE_UREF5, FWD_REF(Arg5) arg5
#	define MOVE_UREF7 MOVE_UREF6, FWD_REF(Arg6) arg6
#	define MOVE_UREF8 MOVE_UREF7, FWD_REF(Arg7) arg7
#	define MOVE_UREF9 MOVE_UREF8, FWD_REF(Arg8) arg8

#	define MOVE_ITERATE_0TO0(MACROFUNC)   MACROFUNC(0)
#	define MOVE_ITERATE_0TO1(MACROFUNC)   MOVE_ITERATE_0TO0(MACROFUNC)  MACROFUNC(1)
#	define MOVE_ITERATE_0TO2(MACROFUNC)   MOVE_ITERATE_0TO1(MACROFUNC)  MACROFUNC(2)
#	define MOVE_ITERATE_0TO3(MACROFUNC)   MOVE_ITERATE_0TO2(MACROFUNC)  MACROFUNC(3)
#	define MOVE_ITERATE_0TO4(MACROFUNC)   MOVE_ITERATE_0TO3(MACROFUNC)  MACROFUNC(4)
#	define MOVE_ITERATE_0TO5(MACROFUNC)   MOVE_ITERATE_0TO4(MACROFUNC)  MACROFUNC(5)
#	define MOVE_ITERATE_0TO6(MACROFUNC)   MOVE_ITERATE_0TO5(MACROFUNC)  MACROFUNC(6)
#	define MOVE_ITERATE_0TO7(MACROFUNC)   MOVE_ITERATE_0TO6(MACROFUNC)  MACROFUNC(7)
#	define MOVE_ITERATE_0TO8(MACROFUNC)   MOVE_ITERATE_0TO7(MACROFUNC)  MACROFUNC(8)
#	define MOVE_ITERATE_0TO9(MACROFUNC)   MOVE_ITERATE_0TO8(MACROFUNC)  MACROFUNC(9)

#endif

template <typename T>
struct SPtr
{
	typedef std::shared_ptr<T> type;
};

template <typename T>
struct UPtr
{
	typedef std::unique_ptr<T> type;
};

#ifndef CPP0X_CORE_VARIADIC_TEMPLATES
#	define MOVE_MAKE_UNIQUE_CODE(N)							\
	template<typename T MOVE_I##N MOVE_CLASS##N>				\
	typename UPtr<T>::type make_unique( MOVE_UREF##N)			\
	{  return std::unique_ptr<T>( new T( MOVE_FWD##N ) );  }		\
	
	MOVE_ITERATE_0TO9(MOVE_MAKE_UNIQUE_CODE)

#	undef MOVE_MAKE_UNIQUE_CODE
#endif

template <typename T>
struct WPtr
{
	typedef std::weak_ptr<T> type;
};

class ScopeGuard
{
	typedef std::function<void()> FunType;

public:
	explicit ScopeGuard(FunType on_exit_scope)
		: dismissed_(false), on_exit_scope_(on_exit_scope)
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
	ScopeGuard(const ScopeGuard&);
	void operator=(const ScopeGuard&);

private:
	bool	 dismissed_;
	FunType  on_exit_scope_;
};

#define LINENAME_CAT(name, line) name##line
#define LINENAME(name, line)	 LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback)						\
ScopeGuard LINENAME(EXIT, __LINE__)(callback)

