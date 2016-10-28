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
// 文件名称:		Assert.hpp
// 创建时间:		2015-09-16
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     调试器头文件
// 
//////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER

#if defined(DEBUG) || defined(_DEBUG) 
#define ASSERT_DEBUG
#endif

#pragma warning(disable:4355)

#endif

#include <string>
#include <sstream>

class Assert
{
public:
	Assert() 
		: ASSERT_A(*this)
		, ASSERT_B(*this)
	{
		
	}

	explicit Assert(const std::string& expression) 
		: ASSERT_A(*this)
		, ASSERT_B(*this)
	{
		dump_ 
			<< "Expression : " << expression.c_str() 
			<< std::endl;	
	}


	Assert& do_nothing() { return *this; }

	Assert& print_context(const std::string& file, const int line);

	template<typename T>
	Assert& print_current_val(const T& val, const std::string& str);

	//level 1, just print warn message
	void warn(const std::string& warn_msg);		

	//level 2, assert;
	void debug(const std::string& debug_msg );

	//level 3, throw exception
	template<typename _E>
	void error(const std::string& error_msg, const _E& exception);	 

	//level 4, break off program;
	void fatal(const std::string& fatal_msg);		

public:
	Assert&	ASSERT_A;
	Assert&	ASSERT_B;

private:
	std::stringstream	dump_;
};

template<typename T>
Assert& Assert::print_current_val(const T& val, const std::string& str)
{
	dump_ << str.c_str() << " = " << val << std::endl;

	return *this;
}

template<typename _E>
void Assert::error(const std::string& error_msg, const _E& e)
{
	dump_ << "Debug : " << error_msg << e.what() << std::endl;

	throw e;
}

#define ASSERT_A(x) ASSERT_OP(x, B)
#define ASSERT_B(x) ASSERT_OP(x, A)

#define MAKE_STR(x) #x
#define MAKE_TSTR(x) MAKE_STR(x)

#ifdef ASSERT_DEBUG
	#define ASSERT_OP(x, next) ASSERT_A.print_current_val((x), MAKE_TSTR(x)).ASSERT_##next		
	#define MAKE_ASSERT(e)	   Assert(e) 

	#define ENSURE(e)	\
	if ((e));				\
	else MAKE_ASSERT(MAKE_TSTR(e)).print_context(__FILE__, __LINE__).ASSERT_A

	#define VERIFY(e)	ENSURE(e)

	#define ENSURE_WARNING(e, m)  e.warn((m)) 
	#define ENSURE_ASSERT(e, m)   e.debug((m))
	#define ENSURE_ERROR(e, m)	  e.error((m), std::runtime_error((m));   
	#define ENSURE_FATAL(e, m)	  e.fatal((m))

	#define VERIFY_WARNING(e, m) ENSURE_WARNING(e, m)
	#define VERIFY_ASSERT(e, m)  ENSURE_ASSERT(e, m)
	#define VERIFY_ERROR(e, m)	 ENSURE_ERROR(e, m)
	#define VERIFY_FATAL(e, m)	 ENSURE_FATAL(e, m)
#else
	#define ASSERT_OP(x, next) ASSERT_A.do_nothing().ASSERT_##next

	#define MAKE_ASSERT() Assert()

	#define ENSURE(e)

	#define VERIFY(e) \
	if ((e)); else MAKE_ASSERT().ASSERT_A

	#define ENSURE_WARNING(e, m)   
	#define ENSURE_ASSERT(e, m) 
	#define ENSURE_FATAL(e, m)  
	#define ENSURE_ERROR(e, m) 

	#define VERIFY_WARNING(e, m)	e
	#define VERIFY_ASSERT(e, m)		e
	#define VERIFY_ERROR(e, m)		e
	#define VERIFY_FATAL(e, m)		e
#endif


