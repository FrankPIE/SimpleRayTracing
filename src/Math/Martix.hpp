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
// 文件名称:		Martix.hpp
// 创建时间:		2016-11-02
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     矩阵类
// 
//////////////////////////////////////////////////////////////////////////


#ifndef _MATH3D_MARTIX_HPP_
#define _MATH3D_MARTIX_HPP_

#include "Vector.hpp"
#include "Operators.hpp"

#ifndef NOEXCEPT
#define NOEXCEPT throw()
#endif

namespace math3D {

template <typename T, size_t N, size_t M>
class MatrixT;

namespace detail {

template <typename T, size_t N>
struct SquareMatrixHelper
{
	static_assert(true, "didn't implement");
};

template <typename T>
struct SquareMatrixHelper<T, 2>
{
	typedef SquareMatrixHelper Matrix;

	static Matrix mul(const Matrix& lhs, const Matrix& rhs)
	{
		return Matrix
			(
			lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0),
			lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1),

			lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0),
			lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)
			);
	}

	static Matrix transpose(const Matrix& m)
	{
		return Matrix
			(
			m(0, 0), m(1, 0),
			m(0, 1), m(1, 1)
			);
	}

	static T determinant(const Matrix& m)
	{
		return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
	}

	static Matrix adjoint(const Matrix& m)
	{
		return Matrix
			(
			m(1, 1), -m(0, 1),
			-m(1, 0), m(0, 0)
			);
	}
};

template <typename T>
struct SquareMatrixHelper<T, 3>
{
	typedef SquareMatrixHelper Matrix;

	static Matrix mul(const Matrix& lhs, const Matrix& rhs)
	{
		return Matrix
			(
			lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0),
			lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1),
			lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2),

			lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0),
			lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1),
			lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2),

			lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0),
			lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1),
			lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2)
			);
	}

	static Matrix transpose(const Matrix& m)
	{
		return Matrix
			(
			m(0, 0), m(1, 0), m(2, 0),
			m(0, 1), m(1, 1), m(2, 1),
			m(0, 2), m(1, 2), m(2, 2)
			);
	}

	static T determinant(const Matrix& m)
	{
		return m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
			m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
			m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
	}

	static Matrix adjoint(const Matrix& m)
	{
		return Matrix
			(
			+(m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)),
			-(m(0, 1) * m(2, 2) - m(0, 2) * m(2, 1)),
			+(m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)),
			-(m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)),
			+(m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)),
			-(m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)),
			+(m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)),
			-(m(0, 0) * m(2, 1) - m(0, 1) * m(2, 0)),
			+(m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0))
			);
	}
};

template <typename T>
struct SquareMatrixHelper<T, 4>
{
	typedef SquareMatrixHelper Matrix;

	static Matrix mul(const Matrix& lhs, const Matrix& rhs)
	{
		return Matrix
			(
			lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0),
			lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1),
			lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2),
			lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3) + lhs(0, 3) * rhs(3, 3),

			lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0),
			lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1),
			lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2),
			lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3) + lhs(1, 3) * rhs(3, 3),

			lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0),
			lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1),
			lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2),
			lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3) + lhs(2, 2) * rhs(2, 3) + lhs(2, 3) * rhs(3, 3),

			lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0) + lhs(3, 2) * rhs(2, 0) + lhs(3, 3) * rhs(3, 0),
			lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1) + lhs(3, 3) * rhs(3, 1),
			lhs(3, 0) * rhs(0, 2) + lhs(3, 1) * rhs(1, 2) + lhs(3, 2) * rhs(2, 2) + lhs(3, 3) * rhs(3, 2),
			lhs(3, 0) * rhs(0, 3) + lhs(3, 1) * rhs(1, 3) + lhs(3, 2) * rhs(2, 3) + lhs(3, 3) * rhs(3, 3)
			);
	}

	static Matrix transpose(const Matrix& m)
	{
		return Matrix
			(
			m(0, 0), m(1, 0), m(2, 0), m(3, 0),
			m(0, 1), m(1, 1), m(2, 1), m(3, 1),
			m(0, 2), m(1, 2), m(2, 2), m(3, 2),
			m(0, 3), m(1, 3), m(2, 3), m(3, 3)
			);
	}

	static T determinant(const Matrix& m)
	{
		const T _3142_3241(m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0));
		const T _3143_3341(m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0));
		const T _3144_3441(m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0));
		const T _3243_3342(m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1));
		const T _3244_3442(m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1));
		const T _3344_3443(m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2));

		return m(0, 0) * (m(1, 1) * _3344_3443 - m(1, 2) * _3244_3442 + m(1, 3) * _3243_3342)
			- m(0, 1) * (m(1, 0) * _3344_3443 - m(1, 2) * _3144_3441 + m(1, 3) * _3143_3341)
			+ m(0, 2) * (m(1, 0) * _3244_3442 - m(1, 1) * _3144_3441 + m(1, 3) * _3142_3241)
			- m(0, 3) * (m(1, 0) * _3243_3342 - m(1, 1) * _3143_3341 + m(1, 2) * _3142_3241);
	}

	static Matrix adjoint(const Matrix& m)
	{
		const T _2132_2231(m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
		const T _2133_2331(m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0));
		const T _2134_2431(m(1, 0) * m(2, 3) - m(1, 3) * m(2, 0));
		const T _2142_2241(m(1, 0) * m(3, 1) - m(1, 1) * m(3, 0));
		const T _2143_2341(m(1, 0) * m(3, 2) - m(1, 2) * m(3, 0));
		const T _2144_2441(m(1, 0) * m(3, 3) - m(1, 3) * m(3, 0));
		const T _2233_2332(m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1));
		const T _2234_2432(m(1, 1) * m(2, 3) - m(1, 3) * m(2, 1));
		const T _2243_2342(m(1, 1) * m(3, 2) - m(1, 2) * m(3, 1));
		const T _2244_2442(m(1, 1) * m(3, 3) - m(1, 3) * m(3, 1));
		const T _2334_2433(m(1, 2) * m(2, 3) - m(1, 3) * m(2, 2));
		const T _2344_2443(m(1, 2) * m(3, 3) - m(1, 3) * m(3, 2));
		const T _3142_3241(m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0));
		const T _3143_3341(m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0));
		const T _3144_3441(m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0));
		const T _3243_3342(m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1));
		const T _3244_3442(m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1));
		const T _3344_3443(m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2));

		return Matrix(
			+(m(1, 1) * _3344_3443 - m(1, 2) * _3244_3442 + m(1, 3) * _3243_3342),
			-(m(0, 1) * _3344_3443 - m(0, 2) * _3244_3442 + m(0, 3) * _3243_3342),
			+(m(0, 1) * _2344_2443 - m(0, 2) * _2244_2442 + m(0, 3) * _2243_2342),
			-(m(0, 1) * _2334_2433 - m(0, 2) * _2234_2432 + m(0, 3) * _2233_2332),

			-(m(1, 0) * _3344_3443 - m(1, 2) * _3144_3441 + m(1, 3) * _3143_3341),
			+(m(0, 0) * _3344_3443 - m(0, 2) * _3144_3441 + m(0, 3) * _3143_3341),
			-(m(0, 0) * _2344_2443 - m(0, 2) * _2144_2441 + m(0, 3) * _2143_2341),
			+(m(0, 0) * _2334_2433 - m(0, 2) * _2134_2431 + m(0, 3) * _2133_2331),

			+(m(1, 0) * _3244_3442 - m(1, 1) * _3144_3441 + m(1, 3) * _3142_3241),
			-(m(0, 0) * _3244_3442 - m(0, 1) * _3144_3441 + m(0, 3) * _3142_3241),
			+(m(0, 0) * _2244_2442 - m(0, 1) * _2144_2441 + m(0, 3) * _2142_2241),
			-(m(0, 0) * _2234_2432 - m(0, 1) * _2134_2431 + m(0, 3) * _2132_2231),

			-(m(1, 0) * _3243_3342 - m(1, 1) * _3143_3341 + m(1, 2) * _3142_3241),
			+(m(0, 0) * _3243_3342 - m(0, 1) * _3143_3341 + m(0, 2) * _3142_3241),
			-(m(0, 0) * _2243_2342 - m(0, 1) * _2143_2341 + m(0, 2) * _2142_2241),
			+(m(0, 0) * _2233_2332 - m(0, 1) * _2133_2331 + m(0, 2) * _2132_2231)
			);
	}
};

template <typename T, size_t N, size_t M>
struct MatrixOperator
{
	typedef Addable1<MatrixT<T, N, M>
	, Subtractable1<MatrixT<T, N, M>
	, Multipliable1<MatrixT<T, N, M>
	, Multipliable2<MatrixT<T, N, M>, T
	, Dividable2<MatrixT<T, N, M>, T
	, EqualityComparable1<MatrixT<T, N, M>
	>>>>>> type;
};

template <typename T, size_t N>
static MatrixT<T, N, N> inverse(const MatrixT<T, N, N>& m)
{
	auto det = SquareMatrixHelper<T, N>::determinant(m);

	DIV_ZERO_CHECK(det)

	if (det == static_cast<T>(0))
	{
		return m;
	}

	return SquareMatrixHelper<T, N>::adjoint(m) / det;
}

}

template < typename T, size_t N, size_t M >
class MatrixT
{
	static_assert(true, "didn't implement");
};

//2x2 Martix
template <typename T>
class MatrixT<T, 2, 2>
	: detail::MatrixOperator<T, 2, 2>::type
{
public:
	typedef T					value_type;

	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;

	typedef value_type&			reference;
	typedef const value_type&	const_reference;

	enum { cRowNumber = 2, cColNumber = 2, cElemNumber = cRowNumber * cColNumber };

public:
	MatrixT() { }

	explicit MatrixT(const T* rhs)
	{
		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i] = VectorT<T, cColNumber>(rhs);
			rhs += cColNumber;
		}
	}

	MatrixT(const T& _11, const T& _12, const T& _21, const T& _22)
	{
		this->m11() = _11; this->m12() = _12;
		this->m21() = _21; this->m22() = _22;
	}

	MatrixT(const MatrixT& rhs)
		: m_(rhs)
	{ }

	MatrixT(MatrixT&& rhs)
		: m_(std::move(rhs))
	{ }
	
	MatrixT& operator=(const MatrixT& rhs)
	{
		if (this == &rhs)
			return (*this);

		m_ = rhs;

		return (*this);
	}

	MatrixT& operator=(MatrixT&& rhs)
	{
		if (this == &rhs)
			return (*this);

		m_ = std::move(rhs);

		return (*this);
	}

	MatrixT operator+() const
	{
		return *this;
	}

	//use nrvo
	MatrixT operator-() const
	{
		MatrixT temp(*this);
		temp.m_ = -m_;
		return std::move(temp);
	}

	MatrixT& operator+=(const MatrixT& rhs)
	{
		m_ += rhs.m_;
		return *this;
	}

	MatrixT& operator-=(const MatrixT& rhs)
	{
		m_ -= rhs.m_;
		return *this;
	}

	MatrixT& operator*=(const MatrixT& rhs)
	{
		*this = detail::SquareMatrixHelper<T, 2>::mul(*this, rhs);

		return *this;
	}

	MatrixT& operator*=(const T& rhs)
	{
		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i] *= rhs;
		}

		return *this;
	}

	MatrixT& operator/=(const T& rhs)
	{
		DIV_ZERO_CHECK(rhs)

		return (*this) * (static_cast<T>(1) / rhs);
	}

	bool operator==(const MatrixT& rhs)
	{
		return m_ == rhs.m_;
	}

public:
	size_t size() const NOEXCEPT
	{
		return cElemNumber;
	}

	size_t row_size() const NOEXCEPT
	{
		return cRowNumber;
	}

	size_t col_size() const NOEXCEPT
	{
		return cColNumber;
	}

	static const MatrixT& zero_t()
	{
		static const MatrixT matrix(0, 0, 0, 0);

		return matrix;
	}

	static const MatrixT& identity_t()
	{
		static const MatrixT matrix(1, 0, 1, 0);

		return matrix;
	}

	static const MatrixT& invalid_t()
	{
		static const MatrixT matrix;

		return matrix;
	}

	MatrixT& zero()
	{
		*this = zero_t();
		return *this;
	}

	MatrixT& identity()
	{
		*this = identity_t();
		return *this;
	}

	MatrixT& invalid()
	{
		*this = invalid_t();
		return *this;		
	}

	MatrixT transpose()
	{
		return detail::SquareMatrixHelper<T, 2>::transpose(*this);
	}

	T determinant()
	{
		return detail::SquareMatrixHelper<T, 2>::determinant(*this);
	}

	MatrixT adjoint()
	{
		return detail::SquareMatrixHelper<T, 2>::adjoint(*this);
	}

	MatrixT inverse()
	{
		static_assert(cRowNumber == cColNumber, "can't resolved");

		return detail::inverse<T, 2>(*this);
	}

	MatrixT fast_inverse()
	{
		return transpose();
	}

	reference operator()(size_t n, size_t m)
	{
		assert(n < cRowNumber && m < cColNumber);

		return m_[n][m];
	}

	const_reference operator()(size_t n, size_t m) const
	{
		assert(n < cRowNumber && m < cColNumber);

		return m_[n][m];
	}

	reference operator[](size_t index)
	{
		assert(index < cElemNumber);

		return *(&m_[0][0] + index);
	}

	const_reference operator[](size_t index) const
	{
		assert(index < cElemNumber);

		return *(&m_[0][0] + index);
	}

	void row(size_t index, const VectorT<T, cColNumber>& rhs)
	{
		assert(index < cRowNumber);

		m_[index] = rhs;
	}

	void col(size_t index, const VectorT<T, cRowNumber>& rhs)
	{
		assert(index < cColNumber);

		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i][index] = rhs[i];
		}
	}

	const VectorT<T, cColNumber>& row(size_t index) const
	{
		assert(index < cRowNumber);

		return m_[index];
	}

	const VectorT<T, cRowNumber>& col(size_t index) const
	{
		assert(index < cColNumber);

		VectorT<T, cRowNumber> ret;

		for (size_t i = 0; i < cRowNumber; ++i)
		{
			ret[i] = m_[i][index];
		}

		return ret;
	}

	reference m11()
	{
		return m_[0][0];
	}

	const_reference m11() const
	{
		return m_[0][0];
	}

	reference m12()
	{
		return m_[0][1];
	}

	const_reference m12() const
	{
		return m_[0][1];
	}

	reference m21()
	{
		return m_[1][0];
	}

	const_reference m21() const
	{
		return m_[1][0];
	}

	reference m22()
	{
		return m_[1][1];
	}

	const_reference m22() const
	{
		return m_[1][1];
	}

private:
	VectorT<VectorT<T, cRowNumber>, cColNumber>  m_;
};

//3x3 Martix
template <typename T>
class MatrixT<T, 3, 3>
	: detail::MatrixOperator<T, 3, 3>::type
{
public:
	typedef T					value_type;

	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;

	typedef value_type&			reference;
	typedef const value_type&	const_reference;

	enum { cRowNumber = 3, cColNumber = 3, cElemNumber = cRowNumber * cColNumber };

public:
	MatrixT() { }

	explicit MatrixT(const T* rhs)
	{
		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i] = VectorT<T, cColNumber>(rhs);
			rhs += cColNumber;
		}
	}

	MatrixT(const T& _11, const T& _12, const T& _13,
		const T& _21, const T& _22, const T& _23,
		const T& _31, const T& _32, const T& _33)
	{
		this->m11() = _11; this->m12() = _12; this->m13() = _13;
		this->m21() = _21; this->m22() = _22; this->m23() = _23;
		this->m31() = _31; this->m32() = _32; this->m33() = _33;
	}

	MatrixT(const MatrixT& rhs)
		: m_(rhs)
	{ }

	MatrixT(MatrixT&& rhs)
		: m_(std::move(rhs))
	{ }
	
	MatrixT& operator=(const MatrixT& rhs)
	{
		if (this == &rhs)
			return (*this);

		m_ = rhs;

		return (*this);
	}

	MatrixT& operator=(MatrixT&& rhs)
	{
		if (this == &rhs)
			return (*this);

		m_ = std::move(rhs);

		return (*this);
	}

	MatrixT operator+() const
	{
		return *this;
	}

	//use nrvo
	MatrixT operator-() const
	{
		MatrixT temp(*this);
		temp.m_ = -m_;
		return std::move(temp);
	}

	MatrixT& operator+=(const MatrixT& rhs)
	{
		m_ += rhs.m_;
		return *this;
	}

	MatrixT& operator-=(const MatrixT& rhs)
	{
		m_ -= rhs.m_;
		return *this;
	}

	MatrixT& operator*=(const MatrixT& rhs)
	{
		*this = detail::SquareMatrixHelper<T, 3>::mul(*this, rhs);

		return *this;
	}

	MatrixT& operator*=(const T& rhs)
	{
		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i] *= rhs;
		}

		return *this;
	}

	MatrixT& operator/=(const T& rhs)
	{
		DIV_ZERO_CHECK(rhs)

		return (*this) * (static_cast<T>(1) / rhs);
	}

	bool operator==(const MatrixT& rhs)
	{
		return m_ == rhs.m_;
	}

public:
	size_t size() const NOEXCEPT
	{
		return cElemNumber;
	}

	size_t row_size() const NOEXCEPT
	{
		return cRowNumber;
	}

	size_t col_size() const NOEXCEPT
	{
		return cColNumber;
	}

	static const MatrixT& zero_t()
	{
		static const MatrixT matrix(0, 0, 0, 0, 0, 0, 0, 0, 0);

		return matrix;
	}

	static const MatrixT& identity_t()
	{
		static const MatrixT matrix(1, 0, 0, 0, 1, 0, 0, 0, 1);

		return matrix;
	}

	static const MatrixT& invalid_t()
	{
		static const MatrixT matrix;

		return matrix;
	}

	MatrixT& zero()
	{
		*this = zero_t();
		return *this;
	}

	MatrixT& identity()
	{
		*this = identity_t();
		return *this;
	}

	MatrixT& invalid()
	{
		*this = invalid_t();
		return *this;		
	}

	MatrixT transpose()
	{
		return detail::SquareMatrixHelper<T, 3>::transpose(*this);
	}

	T determinant()
	{
		return detail::SquareMatrixHelper<T, 3>::determinant(*this);
	}

	MatrixT adjoint()
	{
		return detail::SquareMatrixHelper<T, 3>::adjoint(*this);
	}

	MatrixT inverse()
	{
		static_assert(cRowNumber == cColNumber, "can't resolved");

		return detail::inverse<T, 3>(*this);
	}

	MatrixT fast_inverse()
	{
		return transpose();
	}

	reference operator()(size_t n, size_t m)
	{
		assert(n < cRowNumber && m < cColNumber);

		return m_[n][m];
	}

	const_reference operator()(size_t n, size_t m) const
	{
		assert(n < cRowNumber && m < cColNumber);

		return m_[n][m];
	}

	reference operator[](size_t index)
	{
		assert(index < cElemNumber);

		return *(&m_[0][0] + index);
	}

	const_reference operator[](size_t index) const
	{
		assert(index < cElemNumber);

		return *(&m_[0][0] + index);
	}

	void row(size_t index, const VectorT<T, cColNumber>& rhs)
	{
		assert(index < cRowNumber);

		m_[index] = rhs;
	}

	void col(size_t index, const VectorT<T, cRowNumber>& rhs)
	{
		assert(index < cColNumber);

		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i][index] = rhs[i];
		}
	}

	const VectorT<T, cColNumber>& row(size_t index) const
	{
		assert(index < cRowNumber);

		return m_[index];
	}

	const VectorT<T, cRowNumber>& col(size_t index) const
	{
		assert(index < cColNumber);

		VectorT<T, cRowNumber> ret;

		for (size_t i = 0; i < cRowNumber; ++i)
		{
			ret[i] = m_[i][index];
		}

		return ret;
	}

	reference m11()
	{
		return m_[0][0];
	}

	const_reference m11() const
	{
		return m_[0][0];
	}

	reference m12()
	{
		return m_[0][1];
	}

	const_reference m12() const
	{
		return m_[0][1];
	}

	reference m13()
	{
		return m_[0][2];
	}

	const_reference m13() const
	{
		return m_[0][2];
	}

	reference m21()
	{
		return m_[1][0];
	}

	const_reference m21() const
	{
		return m_[1][0];
	}

	reference m22()
	{
		return m_[1][1];
	}

	const_reference m22() const
	{
		return m_[1][1];
	}

	reference m23()
	{
		return m_[1][2];
	}

	const_reference m23() const
	{
		return m_[1][2];
	}

	reference m31()
	{
		return m_[2][0];
	}

	const_reference m31() const
	{
		return m_[2][0];
	}

	reference m32()
	{
		return m_[2][1];
	}

	const_reference m32() const
	{
		return m_[2][1];
	}

	reference m33()
	{
		return m_[2][2];
	}

	const_reference m33() const
	{
		return m_[2][2];
	}

private:
	VectorT<VectorT<T, cRowNumber>, cColNumber>  m_;
};

//4x4 Martix
template <typename T>
class MatrixT<T, 4, 4>
	: detail::MatrixOperator<T, 4, 4>::type
{
public:
	typedef T					value_type;

	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;

	typedef value_type&			reference;
	typedef const value_type&	const_reference;

	enum { cRowNumber = 4, cColNumber = 4, cElemNumber = cRowNumber * cColNumber };

public:
	MatrixT() { }

	explicit MatrixT(const T* rhs)
	{
		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i] = VectorT<T, cColNumber>(rhs);
			rhs += cColNumber;
		}
	}

	MatrixT(const T& _11, const T& _12, const T& _13, const T& _14,
		const T& _21, const T& _22, const T& _23, const T& _24,
		const T& _31, const T& _32, const T& _33, const T& _34,
		const T& _41, const T& _42, const T& _43, const T& _44)
	{
		this->m11() = _11; this->m12() = _12; this->m13() = _13; this->m14() = _14;
		this->m21() = _21; this->m22() = _22; this->m23() = _23; this->m24() = _24;
		this->m31() = _31; this->m32() = _32; this->m33() = _33; this->m34() = _34;
		this->m41() = _41; this->m42() = _42; this->m43() = _43; this->m44() = _44;
	}

	MatrixT(const MatrixT& rhs)
		: m_(rhs)
	{ }

	MatrixT(MatrixT&& rhs)
		: m_(std::move(rhs))
	{ }
	
	MatrixT& operator=(const MatrixT& rhs)
	{
		if (this == &rhs)
			return (*this);

		m_ = rhs;

		return (*this);
	}

	MatrixT& operator=(MatrixT&& rhs)
	{
		if (this == &rhs)
			return (*this);

		m_ = std::move(rhs);

		return (*this);
	}

	MatrixT operator+() const
	{
		return *this;
	}

	//use nrvo
	MatrixT operator-() const
	{
		MatrixT temp(*this);
		temp.m_ = -m_;
		return std::move(temp);
	}

	MatrixT& operator+=(const MatrixT& rhs)
	{
		m_ += rhs.m_;
		return *this;
	}

	MatrixT& operator-=(const MatrixT& rhs)
	{
		m_ -= rhs.m_;
		return *this;
	}

	MatrixT& operator*=(const MatrixT& rhs)
	{
		*this = detail::SquareMatrixHelper<T, 4>::mul(*this, rhs);

		return *this;
	}

	MatrixT& operator*=(const T& rhs)
	{
		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i] *= rhs;
		}

		return *this;
	}

	MatrixT& operator/=(const T& rhs)
	{
		DIV_ZERO_CHECK(rhs)

		return (*this) * (static_cast<T>(1) / rhs);
	}

	bool operator==(const MatrixT& rhs)
	{
		return m_ == rhs.m_;
	}

public:
	size_t size() const NOEXCEPT
	{
		return cElemNumber;
	}

	size_t row_size() const NOEXCEPT
	{
		return cRowNumber;
	}

	size_t col_size() const NOEXCEPT
	{
		return cColNumber;
	}

	static const MatrixT& zero_t()
	{
		static const MatrixT matrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		return matrix;
	}

	static const MatrixT& identity_t()
	{
		static const MatrixT matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

		return matrix;
	}

	static const MatrixT& invalid_t()
	{
		static const MatrixT matrix;

		return matrix;
	}

	MatrixT& zero()
	{
		*this = zero_t();
		return *this;
	}

	MatrixT& identity()
	{
		*this = identity_t();
		return *this;
	}

	MatrixT& invalid()
	{
		*this = invalid_t();
		return *this;		
	}

	MatrixT transpose()
	{
		return detail::SquareMatrixHelper<T, 4>::transpose(*this);
	}

	T determinant()
	{
		return detail::SquareMatrixHelper<T, 4>::determinant(*this);
	}

	MatrixT adjoint()
	{
		return detail::SquareMatrixHelper<T, 4>::adjoint(*this);
	}

	MatrixT inverse()
	{
		static_assert(cRowNumber == cColNumber, "can't resolved");

		return detail::inverse<T, 4>(*this);
	}

	MatrixT fast_inverse()
	{
		return transpose();
	}

	reference operator()(size_t n, size_t m)
	{
		assert(n < cRowNumber && m < cColNumber);

		return m_[n][m];
	}

	const_reference operator()(size_t n, size_t m) const
	{
		assert(n < cRowNumber && m < cColNumber);

		return m_[n][m];
	}

	reference operator[](size_t index)
	{
		assert(index < cElemNumber);

		return *(&m_[0][0] + index);
	}

	const_reference operator[](size_t index) const
	{
		assert(index < cElemNumber);

		return *(&m_[0][0] + index);
	}

	void row(size_t index, const VectorT<T, cColNumber>& rhs)
	{
		assert(index < cRowNumber);

		m_[index] = rhs;
	}

	void col(size_t index, const VectorT<T, cRowNumber>& rhs)
	{
		assert(index < cColNumber);

		for (size_t i = 0; i < cRowNumber; ++i)
		{
			m_[i][index] = rhs[i];
		}
	}

	const VectorT<T, cColNumber>& row(size_t index) const
	{
		assert(index < cRowNumber);

		return m_[index];
	}

	const VectorT<T, cRowNumber>& col(size_t index) const
	{
		assert(index < cColNumber);

		VectorT<T, cRowNumber> ret;

		for (size_t i = 0; i < cRowNumber; ++i)
		{
			ret[i] = m_[i][index];
		}

		return ret;
	}

	reference m11()
	{
		return m_[0][0];
	}

	const_reference m11() const
	{
		return m_[0][0];
	}

	reference m12()
	{
		return m_[0][1];
	}

	const_reference m12() const
	{
		return m_[0][1];
	}

	reference m13()
	{
		return m_[0][2];
	}

	const_reference m13() const
	{
		return m_[0][2];
	}

	reference m14()
	{
		return m_[0][3];
	}

	const_reference m14() const
	{
		return m_[0][3];
	}

	reference m21()
	{
		return m_[1][0];
	}

	const_reference m21() const
	{
		return m_[1][0];
	}

	reference m22()
	{
		return m_[1][1];
	}

	const_reference m22() const
	{
		return m_[1][1];
	}

	reference m23()
	{
		return m_[1][2];
	}

	const_reference m23() const
	{
		return m_[1][2];
	}

	reference m24()
	{
		return m_[1][3];
	}

	const_reference m24() const
	{
		return m_[1][3];
	}

	reference m31()
	{
		return m_[2][0];
	}

	const_reference m31() const
	{
		return m_[2][0];
	}

	reference m32()
	{
		return m_[2][1];
	}

	const_reference m32() const
	{
		return m_[2][1];
	}

	reference m33()
	{
		return m_[2][2];
	}

	const_reference m33() const
	{
		return m_[2][2];
	}

	reference m34()
	{
		return m_[2][3];
	}

	const_reference m34() const
	{
		return m_[2][3];
	}

	reference m41()
	{
		return m_[3][0];
	}

	const_reference m41() const
	{
		return m_[3][0];
	}

	reference m42()
	{
		return m_[3][1];
	}

	const_reference m42() const
	{
		return m_[3][1];
	}

	reference m43()
	{
		return m_[3][2];
	}

	const_reference m43() const
	{
		return m_[3][2];
	}

	reference m44()
	{
		return m_[3][3];
	}

	const_reference m44() const
	{
		return m_[3][3];
	}

private:
	VectorT<VectorT<T, cRowNumber>, cColNumber>  m_;
};

template <typename T, size_t N>
VectorT<T, N> operator*(const MatrixT<T, N, N>& lhs, const VectorT<T, N>& rhs)
{
	VectorT<T, N> ret;
	for (size_t i = 0; i < N; ++i)
	{
		ret[i] = dot_product(lhs.row(i), rhs);
	}

	return std::move(ret);
}

}
#endif