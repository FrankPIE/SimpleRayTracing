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
// 文件名称:		Vector.hpp
// 创建时间:		2016-10-27
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     矢量数学类
// 
//////////////////////////////////////////////////////////////////////////

#ifndef _MATH3D_VECTOR_HPP_
#define _MATH3D_VECTOR_HPP_

#include <array>
#include <cassert>

#include "Math.hpp"
#include "Operators.hpp"

#ifndef NOEXCEPT
#define NOEXCEPT throw()
#endif

namespace math3D {

namespace detail {

template<typename T, size_t N>
struct VectorHelper
{
	static_assert(N != 0, "N can't be zero");

	template<typename U>
	static void do_copy(T out[N], const U rhs[N])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] = static_cast<T>(rhs[0]);
		VectorHelper<T, N - 1>::do_copy(out + 1, rhs + 1);
	}

	template<typename U>
	static void do_move(T out[N], U rhs[N])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");
		
		out[0] = std::move(static_cast<T>(rhs[0]));

		VectorHelper<T, N - 1>::do_move(out + 1, rhs + 1);
	}

	template <typename U>
	static void do_add(T out[N], const U rhs[N])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] += static_cast<T>(rhs[0]);
		VectorHelper<T, N - 1>::do_add(out + 1, rhs + 1);
	}

	template <typename U>
	static void do_add(T out[N], const U& rhs)
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] += static_cast<T>(rhs);
		VectorHelper<T, N - 1>::do_add(out + 1, rhs);
	}

	template <typename U>
	static void do_sub(T out[N], const U rhs[N])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] -= static_cast<T>(rhs[0]);
		VectorHelper<T, N - 1>::do_sub(out + 1, rhs + 1);
	}

	template <typename U>
	static void do_sub(T out[N], const U& rhs)
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] -= static_cast<T>(rhs);
		VectorHelper<T, N - 1>::do_sub(out + 1, rhs);
	}

	template <typename U>
	static void do_mul(T out[N], const U rhs[N])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] *= static_cast<T>(rhs[0]);
		VectorHelper<T, N - 1>::do_mul(out + 1, rhs + 1);
	}

	template <typename U>
	static void do_mul(T out[N], const U& rhs)
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] *= static_cast<T>(rhs);
		VectorHelper<T, N - 1>::do_mul(out + 1, rhs);
	}

	template <typename U>
	static void do_div(T out[N], const U rhs[N])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		DIV_ZERO_CHECK(rhs[0])

		out[0] /= static_cast<T>(rhs[0]);
		VectorHelper<T, N - 1>::do_div(out + 1, rhs);
	}

	template <typename U>
	static void do_div(T out[N], const U& rhs)
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		DIV_ZERO_CHECK(rhs)

		out[0] /= static_cast<T>(rhs);
		VectorHelper<T, N - 1>::do_div(out + 1, rhs);
	}

	static bool do_equal(const T lhs[1], const T rhs[1])
	{
		return lhs[0] == rhs[0] && VectorHelper<T, N - 1>::do_equal(lhs + 1, rhs + 1);
	}

	static void do_negative(T out[N], const T rhs[N])
	{
		out[0] = -rhs[0];
		VectorHelper<T, N - 1>::do_negative(out + 1, rhs + 1);
	}

	static T dot_product(const T lhs[N], const T rhs[N])
	{
		return lhs[0] * rhs[0] + VectorHelper<T, N - 1>::dot_product(lhs + 1, rhs + 1);
	}

	static T length_square(const T lhs[N])
	{
		return lhs[0] * lhs[0] + VectorHelper<T, N - 1>::length_square(lhs + 1);
	}
};

template<typename T>
struct VectorHelper<T, 1>
{
	template<typename U>
	static void do_copy(T out[1], const U rhs[1])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] = static_cast<T>(rhs[0]);
	}

	template<typename U>
	static void do_move(T out[1], U rhs[1])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");
		
		out[0] = std::move(static_cast<T>(rhs[0]));	
	}

	template <typename U>
	static void do_add(T out[1], const U rhs[1])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] += static_cast<T>(rhs[0]);
	}

	template <typename U>
	static void do_add(T out[1], const U& rhs)
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] += static_cast<T>(rhs);
	}

	template <typename U>
	static void do_sub(T out[1], const U rhs[1])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] -= static_cast<T>(rhs[0]);
	}

	template <typename U>
	static void do_sub(T out[1], const U& rhs)
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] -= static_cast<T>(rhs);
	}

	template <typename U>
	static void do_mul(T out[1], const U rhs[1])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] *= static_cast<T>(rhs[0]);
	}

	template <typename U>
	static void do_mul(T out[1], const U& rhs)
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		out[0] *= static_cast<T>(rhs);
	}

	template <typename U>
	static void do_div(T out[1], const U rhs[1])
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		DIV_ZERO_CHECK(rhs[0])

		out[0] /= static_cast<T>(rhs[0]);
	}

	template <typename U>
	static void do_div(T out[1], const U& rhs)
	{
		static_assert(std::is_convertible<U, T>::value, "can't convert type U to type T");

		DIV_ZERO_CHECK(rhs)

		out[0] /= static_cast<T>(rhs);
	}

	static bool do_equal(const T lhs[1], const T rhs[1])
	{
		return lhs[0] == rhs[0];
	}

	static void do_negative(T out[1], const T rhs[1])
	{
		out[0] = -rhs[0];
	}

	static T dot_product(const T lhs[1], const T rhs[1])
	{
		return lhs[0] * rhs[0];
	}

	static T length_square(const T lhs[1])
	{
		return lhs[0] * lhs[0];
	}
};

}

template<class T, size_t N>
class VectorT
	: Addable1<VectorT<T, N>	 //用+=引出 VectorT + VectorT
	, Addable2<VectorT<T, N>, T  //用+=引出 T + VectorT, VectorT + T
	, Subtractable1<VectorT<T, N>	 //用-=引出 VectorT - VectorT
	, Subtractable2<VectorT<T, N>, T //用-=引出 VectorT - T
	, Multipliable1<VectorT<T, N>	 //用*=引出 VectorT * VectorT
	, Multipliable2<VectorT<T, N>, T //用*=引出 VectorT * T, T * VectorT
	, Dividable1<VectorT<T, N>		 //用/=引出 VectorT / VectorT	
	, Dividable2<VectorT<T, N>, T    //用/=引出 VectorT / T
	, EqualityComparable1<VectorT<T, N>	//用==引出 VectorT != VectorT
	>>>>>>>>>
{
	static_assert(N != 0, "N can't be zero");
 
 	template <typename U, size_t M>
 	friend class VectorT;
 
 	typedef std::array < T, N > VectorType;
 
 	enum { cElemNumber = N };

public:
	typedef typename VectorType::value_type value_type;

	typedef value_type *pointer;
	typedef const value_type *const_pointer;

	typedef typename VectorType::reference reference;
	typedef typename VectorType::const_reference const_reference;

	typedef typename VectorType::size_type		 size_type;
	typedef typename VectorType::difference_type difference_type;

public:
	VectorT() 
	{ }

	explicit VectorT(const T& v)
	{
		vec_.fill(v);
	}

	explicit VectorT(const T* pv)
	{
		detail::VectorHelper<T, N>::do_copy(&vec_[0], pv);
	}

	//兼容其他类型VectorT
	template <typename U, int M>
	VectorT(const VectorT<U, M>& rhs)
	{
		static_assert(M >= N, "M msut bigger or equal than N");

		detail::VectorHelper<T, N>::do_copy(&vec_[0], rhs.Data());
	}

	template <typename U, int M>
	VectorT(VectorT<U, M>&& rhs)
	{
		static_assert(M >= N, "M msut bigger or equal than N");
		
		detail::VectorHelper<T, N>::do_move(&vec_[0], &rhs.vec_[0]);
	}

	VectorT(const T& x, const T& y)
	{
		static_assert(cElemNumber == 2, "invaild construct, out of range");

		this->x() = x;
		this->y() = y;
	}

	VectorT(T&& x, T&& y)
	{
		static_assert(cElemNumber == 2, "invaild construct, out of range");

		this->x() = std::move(x);
		this->y() = std::move(y);
	}

	VectorT(const T& x, const T& y, const T& z)
	{
		static_assert(cElemNumber == 3, "invaild construct, out of range");

		this->x() = x;
		this->y() = y;
		this->z() = z;
	}

	VectorT(T&& x, T&& y, T&& z)
	{
		static_assert(cElemNumber == 3, "invaild construct, out of range");

		this->x() = std::move(x);
		this->y() = std::move(y);
		this->z() = std::move(z);
	}

	VectorT(const T& x, const T& y, const T& z, const T& w)
	{
		static_assert(cElemNumber == 4, "invaild construct, out of range");

		this->x() = x;
		this->y() = y;
		this->z() = z;
		this->w() = w;
	}

	VectorT(T&& x, T&& y, T&& z, T&& w)
	{
		static_assert(cElemNumber == 4, "invaild construct, out of range");

		this->x() = std::move(x);
		this->y() = std::move(y);
		this->z() = std::move(z);
		this->w() = std::move(w);
	}

	VectorT(const VectorT& rhs)
		: vec_(rhs.vec_)
	{ }

	VectorT(VectorT&& rhs)
		: vec_(std::move(rhs.vec_))
	{ }

	VectorT& operator=(const VectorT& rhs)
	{
		if (this == &rhs)
			return (*this);

		vec_ = rhs.vec_;

		return (*this);
	}

	template <typename U, int M>
	VectorT& operator=(const VectorT<U, M>& rhs)
	{
		static_assert(M >= N, "M msut bigger or equal than N");

		if (this == &rhs)
			return (*this);

		detail::VectorHelper<T, N>::do_copy(&vec_[0], rhs.Data());

		return (*this);
	}

	VectorT& operator=(VectorT&& rhs)
	{
		if (this == &rhs)
			return (*this);

		vec_ = std::move(rhs.vec_);

		return (*this);
	}

	template <typename U, int M>
	VectorT& operator=(VectorT<U, M>&& rhs)
	{
		static_assert(M >= N, "M msut bigger or equal than N");

		if (this == &rhs)
			return (*this);

		detail::VectorHelper<T, N>::do_move(&vec_[0], rhs.Data());

		return (*this);
	}

public:
	VectorT& zero()
	{
		memset(&vec_[0], 0, sizeof(T) * cElemNumber);
		return (*this);
	}

	static const VectorT& zero_t()
	{
		static const VectorT<T, N> zero_value(static_cast<T>(0));

		return zero_value;
	}

	VectorT& invalid()
	{
		(*this) = VectorT();	//will move

		return (*this);
	}

	static const VectorT& invalid_t()
	{
		static const VectorT<T, N> invaild_value;

		return invaild_value;		
	}

	void normalize()
	{
		(*this) /= length();
	}

	T length_square() const
	{
		return (detail::VectorHelper<T, N>::length_square(data()));
	}

	T length() const
	{
		return ::sqrt(length_square());
	}

	T norm()
	{
		return length();	
	}

public:
	VectorT operator-() const
	{
		VectorT temp(*this);

		detail::VectorHelper<T, N>::do_negative(&temp.vec_[0], data());

		return std::move(temp);
	}

	VectorT operator+() const
	{
		return (*this);
	}

	VectorT& operator+=(const VectorT& rhs)
	{
		detail::VectorHelper<T, N>::template do_add<T>(&vec_[0], rhs.data());

		return (*this);
	}

	VectorT& operator+=(const T& rhs)
	{
		detail::VectorHelper<T, N>::template do_add<T>(&vec_[0], rhs);

		return (*this);
	}

	VectorT& operator-=(const VectorT& rhs)
	{
		detail::VectorHelper<T, N>::template do_sub<T>(&vec_[0], rhs.data());

		return (*this);
	}

	VectorT& operator-=(const T& rhs)
	{
		detail::VectorHelper<T, N>::template do_sub<T>(&vec_[0], rhs);

		return (*this);
	}

	VectorT& operator*=(const VectorT& rhs)
	{
		detail::VectorHelper<T, N>::template do_mul<T>(&vec_[0], rhs.data());

		return *this;
	}

	VectorT& operator*=(const T& rhs)
	{
		detail::VectorHelper<T, N>::template do_mul<T>(&vec_[0], rhs);

		return (*this);
	}

	VectorT& operator/=(const VectorT& rhs)
	{
		detail::VectorHelper<T, N>::template do_div<T>(&vec_[0], rhs.data());

		return (*this);
	}

	VectorT& operator/=(const T& rhs)
	{
		detail::VectorHelper<T, N>::template do_div<T>(&vec_[0], rhs);

		return (*this);
	}

	reference operator[](size_type index)
	{
		assert(index >= 0 && index < size());

		return vec_[index];
	}

	const_reference operator[](size_type index) const
	{
		assert(index >= 0 && index < size());
		
		return vec_[index];
	}

	bool operator==(const VectorT& rhs)
	{
		return detail::VectorHelper<T, N>::do_equal(data(), rhs.data());
	}

public:
	reference x()
	{
		static_assert(cElemNumber >= 1, "invaild x reference");
		return vec_[0];
	}

	const_reference x() const
	{
		static_assert(cElemNumber >= 1, "invaild x reference");
		return vec_[0];
	}

	reference y()
	{
		static_assert(cElemNumber >= 2, "invaild y reference");
		return vec_[1];
	}

	const_reference y() const
	{
		static_assert(cElemNumber >= 2, "invaild y reference");
		return vec_[1];
	}

	reference z()
	{
		static_assert(cElemNumber >= 3, "invaild z reference");
		return vec_[2];
	}

	const_reference z() const
	{
		static_assert(cElemNumber >= 3, "invaild z reference");
		return vec_[2];
	}

	reference w()
	{
		static_assert(cElemNumber >= 4, "invaild w reference");
		return vec_[3];
	}

	const_reference w() const
	{
		static_assert(cElemNumber >= 4, "invaild w reference");
		return vec_[3];
	}

	const_pointer data() const NOEXCEPT
	{
		return vec_.data();
	}

 	size_type size() const NOEXCEPT
	{
		return cElemNumber;
	}

	void swap(VectorT& rhs) NOEXCEPT
	{
		vec_.swap(rhs.vec_);
	}
	
private:
	VectorType		 vec_;
};

template <typename T, size_t N>
inline void swap(VectorT<T, N>& lhs, VectorT<T, N>& rhs) NOEXCEPT
{
	lhs.swap(rhs);
}

template <class T, size_t N>
inline T dot_product(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return detail::VectorHelper<T, N>::dot_product(lhs.data(), rhs.data());
}

template <typename T>
inline VectorT<T, 3> cross_product(const VectorT<T, 3>& lhs, const VectorT<T, 3>& rhs)
{
	return VectorT<T, 3>(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
		lhs.z() * rhs.x() - lhs.x() * rhs.z(),
		lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

template <typename T, size_t N>
inline VectorT<T, N> normalize(VectorT<T, N> vec)
{
	vec.normalize();	

	return std::move(vec);	
}

template <typename T, size_t N>
inline T norm(const VectorT<T, N>& vec)
{
	return vec.norm();
}

template <class T, size_t N>
inline T distance(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return norm(lhs - rhs);
}

}
#endif