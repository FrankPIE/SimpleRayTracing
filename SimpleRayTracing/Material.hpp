///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Boxiang.Pei
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files
// (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:¡¡
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
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
// FileName:	Material.hpp
// CreateDate:	2017-04-15
//
// E-Mail:		frankpei1992@gmail.com
//
// Descript:    ²ÄÖÊ½Ó¿Ú
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "MathType.h"
#include "HitAble.hpp"

#include "drand48.h"

template <typename T>
class Material abstract
{
public:
	virtual ~Material() = 0 { }

	virtual bool Scatter(const math3D::Ray3D<T>& ray_in, const HitRecord<T>& result, math3D::VectorT<T, 3>& attenuation, math3D::Ray3D<T>& scattered) const = 0;
};

template <typename T>
inline math3D::VectorT<T, 3> RandomInUnitSphere()
{
	math3D::VectorT<T, 3> point_in_unit_sphere;

	do
	{
		point_in_unit_sphere = 2.0 * math3D::double3(drand48(), drand48(), drand48()) - math3D::double3(1.0, 1.0, 1.0);
	} while (point_in_unit_sphere.length_square() >= 1.0);

	return point_in_unit_sphere;
}

template <typename T>
class Lambertian
	: public Material<T>
{
public:
	Lambertian(const math3D::VectorT<T, 3>& a)
		: albedo(a)
	{ }

	virtual bool Scatter(const math3D::Ray3D<T>& ray_in, const HitRecord<T>& result, math3D::VectorT<T, 3>& attenuation, math3D::Ray3D<T>& scattered) const
	{
		auto target = result.point + result.normal + RandomInUnitSphere<T>();

		scattered = math3D::Ray3D<T>(result.point, target - result.point);

		attenuation = albedo;

		return true;
	}

	math3D::VectorT<T, 3> albedo;
};

template <typename T>
inline math3D::VectorT<T, 3> Reflect(const math3D::VectorT<T, 3>& v, const math3D::VectorT<T, 3>& n)
{
	return v - 2 * math3D::dot_product(v, n) * n;
}

template <typename T>
class Metal 
	: public Material<T>
{
public:
	Metal(const math3D::VectorT<T, 3>& a, const T f)
		: albedo(a)
		, fuzz(f < T(1) ? f : T(1))
	{ }

	virtual bool Scatter(const math3D::Ray3D<T>& ray_in, const HitRecord<T>& result, math3D::VectorT<T, 3>& attenuation, math3D::Ray3D<T>& scattered) const
	{
		auto reflected = Reflect(math3D::normalize(ray_in.direction), result.normal);

		scattered = math3D::Ray3D<T>(result.point, reflected + fuzz * RandomInUnitSphere<T>());

		attenuation = albedo;

		return (math3D::dot_product(scattered.direction, result.normal) > 0);
	}

	math3D::VectorT<T, 3> albedo;
	T					  fuzz;
};

