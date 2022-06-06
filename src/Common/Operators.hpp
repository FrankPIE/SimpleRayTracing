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
// 文件名称:		Operators.hpp
// 创建时间:		2016-10-27
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     模板操作符重载
// 
//////////////////////////////////////////////////////////////////////////


#ifndef _OPERTAOR_HPP_
#define _OPERTAOR_HPP_

namespace detail {
struct null_type { };
}

template <class T, class B = detail::null_type>
struct EqualityComparable1 : B
{
	friend bool operator!=(const T& x, const T& y) { return !static_cast<bool>(x == y); }
};

template < class T, class U, class B = detail::null_type >
struct EqualityComparable2 : B
{
	friend bool operator==(const U& y, const T& x) { return x == y; }
	friend bool operator!=(const U& y, const T& x) { return !static_cast<bool>(x == y); }
	friend bool operator!=(const T& y, const U& x) { return !static_cast<bool>(y == x); }
};

template < class T, class B = detail::null_type >
struct LessThanComparable1 : B
{
	friend bool operator>(const T& x, const T& y)  { return y < x; }
	friend bool operator<=(const T& x, const T& y) { return !static_cast<bool>(y < x); }
	friend bool operator>=(const T& x, const T& y) { return !static_cast<bool>(x < y); }
};

template < class T, class U, class B = detail::null_type >
struct LessThanComparable2 : B
{
	friend bool operator<=(const T& x, const U& y) { return !static_cast<bool>(x > y); }
	friend bool operator>=(const T& x, const U& y) { return !static_cast<bool>(x < y); }
	friend bool operator>(const U& x, const T& y)  { return y < x; }
	friend bool operator<(const U& x, const T& y)  { return y > x; }
	friend bool operator<=(const U& x, const T& y) { return !static_cast<bool>(y < x); }
	friend bool operator>=(const U& x, const T& y) { return !static_cast<bool>(y > x); }
};

#define OPERATOR2_LEFT(name) name##2##Left

#define BINARY_OPERATOR_COMMUTATIVE( NAME, OP )								  \
template <class T, class U, class B = detail::null_type >					  \
struct NAME##2 : B															  \
{																			  \
  friend T operator OP( const T& lhs, const U& rhs )                          \
	{ T nrv( lhs ); nrv OP##= rhs; return nrv; }                              \
  friend T operator OP( const U& lhs, const T& rhs )                          \
	{ T nrv( rhs ); nrv OP##= lhs; return nrv; }                              \
};                                                                            \
                                                                              \
template <class T, class B = detail::null_type >							  \
struct NAME##1 : B                                                            \
{                                                                             \
  friend T operator OP( const T& lhs, const T& rhs )                          \
	{ T nrv( lhs ); nrv OP##= rhs; return nrv; }                              \
};

#define BINARY_OPERATOR_NON_COMMUTATIVE( NAME, OP )							  \
template <class T, class U, class B = detail::null_type >					  \
struct NAME##2 : B															  \
{																			  \
  friend T operator OP( const T& lhs, const U& rhs )						  \
	{ T nrv( lhs ); nrv OP##= rhs; return nrv; }							  \
};																			  \
																			  \
template <class T, class U, class B = detail::null_type >					  \
struct OPERATOR2_LEFT(NAME) : B												  \
{																			  \
  friend T operator OP( const U& lhs, const T& rhs )						  \
	{ T nrv( lhs ); nrv OP##= rhs; return nrv; }							  \
};																			  \
																			  \
template <class T, class B = detail::null_type >							  \
struct NAME##1 : B															  \
{																			  \
  friend T operator OP( const T& lhs, const T& rhs )						  \
	{ T nrv( lhs ); nrv OP##= rhs; return nrv; }							  \
};

BINARY_OPERATOR_COMMUTATIVE(Multipliable, *)
BINARY_OPERATOR_COMMUTATIVE(Addable, +)
BINARY_OPERATOR_NON_COMMUTATIVE(Subtractable, -)
BINARY_OPERATOR_NON_COMMUTATIVE(Dividable, / )
BINARY_OPERATOR_NON_COMMUTATIVE(Modable, %)
BINARY_OPERATOR_COMMUTATIVE(Xorable, ^)
BINARY_OPERATOR_COMMUTATIVE(Andable, &)
BINARY_OPERATOR_COMMUTATIVE(Orable, |)

#undef BINARY_OPERATOR_COMMUTATIVE
#undef BINARY_OPERATOR_NON_COMMUTATIVE
#undef OPERATOR2_LEFT

#define BINARY_OPERATOR( NAME, OP )											\
template <class T, class U, class B = detail::null_type >					\
struct NAME##2 : B                                                          \
{                                                                           \
  friend T operator OP( const T& lhs, const U& rhs )                        \
	{ T nrv( lhs ); nrv OP##= rhs; return nrv; }                            \
};                                                                          \
                                                                            \
template <class T, class B = detail::null_type >							\
struct NAME##1 : B                                                          \
{                                                                           \
  friend T operator OP( const T& lhs, const T& rhs )                        \
	{ T nrv( lhs ); nrv OP##= rhs; return nrv; }                            \
};

BINARY_OPERATOR(LeftShiftable, <<)
BINARY_OPERATOR(RightShiftable, >>)

#undef BINARY_OPERATOR

template <class T, class B = detail::null_type >
struct Equivalent1 : B
{
	friend bool operator==(const T&x, const T&y)
	{
		return !static_cast<bool>(x < y) && !static_cast<bool>(y < x);
	}
};

template <class T, class U, class B = detail::null_type >
struct Equivalent2 : B
{
	friend bool operator==(const T& x, const U& y)
	{
		return !static_cast<bool>(x < y) && !static_cast<bool>(x > y);
	}
};

template <class T, class B = detail::null_type >
struct PartiallyOrdered1 : B
{
	friend bool operator>(const T& x, const T& y)
	{
		return y < x;
	}
	friend bool operator<=(const T& x, const T& y)
	{
		return static_cast<bool>(x < y) || static_cast<bool>(x == y);
	}
	friend bool operator>=(const T& x, const T& y)
	{
		return static_cast<bool>(y < x) || static_cast<bool>(x == y);
	}
};

template <class T, class U, class B = detail::null_type >
struct PartiallyOrdered2 : B
{
	friend bool operator<=(const T& x, const U& y)
	{
		return static_cast<bool>(x < y) || static_cast<bool>(x == y);
	}
	friend bool operator>=(const T& x, const U& y)
	{
		return static_cast<bool>(x > y) || static_cast<bool>(x == y);
	}
	friend bool operator>(const U& x, const T& y)
	{
		return y < x;
	}
	friend bool operator<(const U& x, const T& y)
	{
		return y > x;
	}
	friend bool operator<=(const U& x, const T& y)
	{
		return static_cast<bool>(y > x) || static_cast<bool>(y == x);
	}
	friend bool operator>=(const U& x, const T& y)
	{
		return static_cast<bool>(y < x) || static_cast<bool>(y == x);
	}
};

//< > == != <= >=
template <class T, class B = detail::null_type >
struct TotallyOrdered1
	: LessThanComparable1 < T, EqualityComparable1<T, B> > { };

template <class T, class U, class B = detail::null_type >
struct TotallyOrdered2
	: LessThanComparable2 < T, U, EqualityComparable2<T, U, B> > { };

//+ -
template <class T, class B = detail::null_type >
struct Additive1
	: Addable1 < T, Subtractable1<T, B> > { };

template <class T, class U, class B = detail::null_type >
struct Additive2
	: Addable2 < T, U, Subtractable2<T, U, B> > { };

//* /
template <class T, class B = detail::null_type >
struct Multiplicative1
	: Multipliable1 < T, Dividable1 < T, B > > { };

template <class T, class U, class B = detail::null_type >
struct Multiplicative2
	: Multipliable2 < T, U, Dividable2 < T, U, B> > { };

//* / %
template <class T, class B = detail::null_type >
struct IntegerMultiplicative1
	: Multiplicative1 < T, Modable1 < T, B > > { };

template <class T, class U, class B = detail::null_type >
struct IntegerMultiplicative2
	: Multiplicative2 < T, U, Modable2 < T, U, B > > { };

//+ - * /
template <class T, class B = detail::null_type >
struct Arithmetic1
	: Additive1 < T, Multiplicative1 < T, B > > { };

template <class T, class U, class B = detail::null_type >
struct Arithmetic2
	: Additive2 < T, U, Multiplicative2 < T, U, B > > {};

//+ - * / %
template <class T, class B = detail::null_type >
struct IntegerArithmetic1
	: Additive1 < T, IntegerMultiplicative1 < T, B > > {};

template <class T, class U, class B = detail::null_type >
struct IntegerArithmetic2
	: Additive2 < T, U, IntegerMultiplicative2 < T, U, B > > {};

//| & ^
template <class T, class B = detail::null_type >
struct Bitwise1
	: Xorable1 < T, Andable1<T, Orable1<T, B> > > {};

template <class T, class U, class B = detail::null_type >
struct Bitwise2
	: Xorable2 < T, U, Andable2<T, U, Orable2<T, U, B> > > {};

//<< >>
template <class T, class B = detail::null_type >
struct Shiftable1
	: LeftShiftable1 < T, RightShiftable1 < T, B > > {};

template <class T, class U, class B = detail::null_type >
struct Shiftable2
	: LeftShiftable2 < T, U, RightShiftable2 < T, U, B > > {};

//+ - * /
template <class T, class B = detail::null_type >
struct RingOperators1
	: Additive1 < T, Multipliable1 < T, B > > {};

template <class T, class U, class B = detail::null_type >
struct RingOperators2
	: Additive2 < T, U, Subtractable2Left<T, U, Multipliable2<T, U, B > > > {};

#endif
