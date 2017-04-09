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
// 文件名称:		Ray.hpp
// 创建时间:		2016-11-02
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     光线类
// 
//////////////////////////////////////////////////////////////////////////

#ifndef _MATH_RAY3D_HPP_
#define _MATH_RAY3D_HPP_

#include "Vector.hpp"

namespace math3D {

template<typename T>
class Ray3D
{
public:
	Ray3D() 
		: origin(0)
		, direction(0, 0, 1) 
	{ }

	Ray3D(const VectorT<T, 3>& o, const VectorT<T, 3>& d)
		: origin(o)
		, direction(d) 
	{ }

	Ray3D(const Ray3D& ray)
		: origin(ray.origin)
		, direction(ray.direction) 
	{ }

	Ray3D(Ray3D&& ray)
		: origin(std::move(ray.origin))
		, direction(std::move(ray.direction)) 
	{ }

	Ray3D& operator=(const Ray3D& ray)
	{
		if (this == &ray)
			return (*this);

		origin    = ray.origin;
		direction = ray.direction;

		return (*this);
	}

	Ray3D& operator=(Ray3D&& ray)
	{
		if (this == &ray)
			return (*this);

		origin    = std::move(ray.origin);
		direction = std::move(ray.direction);

		return (*this);
	}

	VectorT<T, 3> point_at(const T t) const
	{
		return origin + t * direction;
	}

	VectorT<T, 3> origin;
	VectorT<T, 3> direction;
};

}

#endif
