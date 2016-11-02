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
// 文件名称:		Color.hpp
// 创建时间:		2016-11-01
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     颜色类
// 
//////////////////////////////////////////////////////////////////////////

#ifndef _MATH3D_COLOR_HPP_
#define _MATH3D_COLOR_HPP_

#include <cstdint>

#include "Math.hpp"
#include "Vector.hpp"
#include "Operators.hpp"

#ifndef NOEXCEPT
#define NOEXCEPT throw()
#endif

namespace math3D {
class Color 
	: Addable1<Color
	, Subtractable1<Color
	, Multipliable1<Color
	, Multipliable2<Color, float
	, Dividable2<Color, float
	, EqualityComparable1<Color
	>>>>>>
{
public:
	enum { cElemNumber = 4 };

	typedef float value_type;

	typedef VectorT<float, cElemNumber>::pointer pointer;
	typedef VectorT<float, cElemNumber>::const_pointer const_pointer;

	typedef VectorT<float, cElemNumber>::reference reference;
	typedef VectorT<float, cElemNumber>::const_reference const_reference;

	typedef VectorT<float, cElemNumber>::size_type size_type;

	typedef VectorT<float, cElemNumber>::difference_type difference_type;

public:
	Color() { }

	explicit Color(const float rhs)
		: color_(rhs)
	{ }

	Color(const float r, const float g, const float b, const float a)
		: color_(r, g, b, a)
	{ }

	//兼容RGB宏
	explicit Color(const uint32_t dw)
	{
		static const auto cConstant = 1.0f / 255.0f;
		this->a() = cConstant * (static_cast<float>(static_cast<uint8_t>(dw >> 24)));
		this->r() = cConstant * (static_cast<float>(static_cast<uint8_t>(dw >> 16)));
		this->g() = cConstant * (static_cast<float>(static_cast<uint8_t>(dw >> 8)));
		this->b() = cConstant * (static_cast<float>(static_cast<uint8_t>(dw >> 0)));
	}

	Color(const Color& clr)
		: color_(clr.color_)
	{ }

	Color& operator=(const Color& rhs)
	{
		if (this != &rhs)
		{
			color_ = rhs.color_;
		}

		return (*this);
	}

	Color(Color&& clr)
		: color_(std::move(clr.color_))
	{ }

	Color& operator=(Color&& rhs)
	{
		if (this != &rhs)
		{
			color_ = std::move(rhs.color_);
		}

		return (*this);
	}

	void RGBA(uint8_t& R, uint8_t& G, uint8_t& B, uint8_t& A) const
	{
		R = static_cast<uint8_t>(clamp(r(), 0.0f, 1.0f) * 255.f + 0.5f);
		G = static_cast<uint8_t>(clamp(g(), 0.0f, 1.0f) * 255.f + 0.5f);
		B = static_cast<uint8_t>(clamp(b(), 0.0f, 1.0f) * 255.f + 0.5f);
		A = static_cast<uint8_t>(clamp(a(), 0.0f, 1.0f) * 255.f + 0.5f);
	}

	uint32_t ARGB() const
	{
		uint8_t r, g, b, a;
		this->RGBA(r, g, b, a);
		return (a << 24) | (r << 16) | (g << 8) | (b << 0);
	}

	uint32_t ABGR() const
	{
		uint8_t r, g, b, a;
		this->RGBA(r, g, b, a);
		return (a << 24) | (b << 16) | (g << 8) | (r << 0);
	}

	Color operator+() const
	{
		return (*this);
	}

	Color operator-() const
	{
		return Color(-r(), -g(), -b(), -a());
	}

	Color& operator+=(const Color& rhs)
	{
		color_ += rhs.color_;

		return (*this);
	}

	Color& operator-=(const Color& rhs)
	{
		color_ -= rhs.color_;

		return (*this);
	}

	Color& operator*=(const Color& rhs)
	{
		r() *= rhs.r();
		g() *= rhs.g();
		b() *= rhs.b();
		a() *= rhs.a();

		return (*this);
	}

	Color& operator*=(const float rhs)
	{
		color_ *= rhs;

		return (*this);
	}

	Color& operator/=(const float rhs)
	{
		color_ /= rhs;

		return (*this);
	}

	bool operator==(const Color& rhs)
	{
		return (color_ == rhs.color_);
	}

public:
	size_type size() const NOEXCEPT
	{
		return cElemNumber;
	}

	const_pointer data() const NOEXCEPT
	{
		return color_.data();
	}

	reference r()
	{
		return color_.x();
	}

	const_reference r() const
	{
		return color_.x();
	}

	reference g()
	{
		return color_.y();
	}

	const_reference g() const
	{
		return color_.y();
	}

	reference b()
	{
		return color_.z();
	}

	const_reference b() const
	{
		return color_.z();
	}

	reference a()
	{
		return color_.w();
	}

	const_reference a() const
	{
		return color_.w();
	}

private:
	VectorT<float, cElemNumber> color_;
};

}

#endif
