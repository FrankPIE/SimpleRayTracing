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

#include "HitAble.hpp"
#include "Material.hpp"

template <typename T>
class Sphere
	: public HitAble<T>
{
public:
	using CenterType = math3D::VectorT<typename T, 3>;

public:
	Sphere(const CenterType& c, T r, SPtr<Material<T>> ptr)
		: center(c)
		, radius(r) 
		, material(ptr)
	{ }

	Sphere(math3D::float3&& c, T r, SPtr<Material<T>> ptr)
		: center(std::move(c))
		, radius(r)
		, material(ptr)
	{ }

	Sphere(const Sphere& sphere)
		: center(sphere.center)
		, radius(sphere.radius)
		, material(sphere.material)
	{ }

	Sphere(Sphere&& sphere)
		: center(std::move(sphere.center))
		, radius(std::move(sphere.radius))
		, material(std::move(sphere.material))
	{ }

	Sphere& operator=(const Sphere& sphere)
	{
		if (this == &sphere)
			return (*this);

		center = sphere.center;
		radius = sphere.radius;
		material = sphere.material;

		return (*this);
	}

	Sphere& operator=(Sphere&& sphere)
	{
		if (this == &sphere)
			return (*this);

		center = std::move(sphere.center);
		radius = std::move(sphere.radius);
		material = std::move(sphere.material);

		return (*this);
	}

	virtual bool HitTest(const math3D::Ray3D<T>& ray, T t_min, T t_max, HitRecord<T>& rec) const
	{
		auto oc = ray.origin - center;

		auto a = math3D::dot_product(ray.direction, ray.direction);
		auto b = T(2) * math3D::dot_product(oc, ray.direction);
		auto c = math3D::dot_product(oc, oc) - radius * radius;

		auto discriminant = b * b - 4 * a * c;

		if (!(discriminant < 0))
		{		
			auto temp_t = (-b - sqrt(discriminant)) / T(2.0 * a);

			if (temp_t < t_max && temp_t > t_min)
			{
				rec.t = temp_t;
				rec.point = ray.point_at(rec.t);
				rec.normal = math3D::normalize(rec.point - center);

				rec.material_ptr = material;

				return true;
			}

			temp_t = (-b + sqrt(discriminant)) / T(2.0 * a);

			if (temp_t < t_max && temp_t > t_min)
			{
				rec.t = temp_t;
				rec.point = ray.point_at(rec.t);
				rec.normal = math3D::normalize(rec.point - center);

				rec.material_ptr = material;

				return true;
			}
		}

		return false;
	}

	CenterType			center;
	T					radius;
	SPtr<Material<T>>	material;
};