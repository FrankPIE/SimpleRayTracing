///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Boxiang.Pei
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files
// (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:°°
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.g
//
// THE SOFTWARE IS PROVIDED "AS IS",
// WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// FileName:	Sphere.h
// CreateDate:	2017-04-02
//
// E-Mail:		frankpei1992@gmail.com
//
// Descript:    3Dº∏∫Œ«Ú¿‡
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "Ray.hpp"
#include "Vector.hpp"

template <typename T>
using SphereHitTestResult = std::tuple<int32_t, math3D::VectorT<T, 3>, math3D::VectorT<T, 3>>;

template <typename T>
class Sphere
{
public:
	using CenterType = math3D::VectorT<typename T, 3>;

public:
	Sphere(const CenterType& c, T r)
		: center(c)
		, radius(r) 
	{ }

	Sphere(math3D::float3&& c, T r)
		: center(std::move(c))
		, radius(r)
	{ }

	Sphere(const Sphere& sphere)
		: center(sphere.center)
		, radius(sphere.radius)
	{ }

	Sphere(Sphere&& sphere)
		: center(std::move(sphere.center))
		, radius(std::move(sphere.radius))
	{ }

	Sphere& operator=(const Sphere& sphere)
	{
		if (this == &sphere)
			return (*this);

		center = sphere.center;
		radius = sphere.radius;

		return (*this);
	}

	Sphere& operator=(Sphere&& sphere)
	{
		if (this == &sphere)
			return (*this);

		center = std::move(sphere.center);
		radius = std::move(sphere.radius);

		return (*this);
	}

	CenterType	center;
	T			radius;
};

template <typename T>
SphereHitTestResult<T> SphereHitTest(const Sphere<T>& sphere, const math3D::Ray3D<T>& ray)
{
	SphereHitTestResult<T> result;

	//TODO::

	return std::move(result);
}