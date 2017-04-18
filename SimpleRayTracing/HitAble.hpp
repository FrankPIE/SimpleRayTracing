///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017 Boxiang.Pei
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
// FileName:	HitAble.hpp
// CreateDate:	2017-04-09
//
// E-Mail:		frankpei1992@gmail.com
//
// Descript:    Åö×²½Ó¿Ú
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "Ray.hpp"

template<typename T>
class Material;

template<typename T>
struct HitRecord
{
	using value_type = T;
	using vec3_type  = math3D::VectorT<T, 3>;

	value_type			t;
	vec3_type			point;
	vec3_type			normal;
	SPtr<Material<T>>	material_ptr;
};

template <typename T>
class HitAble abstract
{
public:
	virtual ~HitAble() { }

public:
	virtual bool HitTest(const math3D::Ray3D<T>& ray, T t_min, T t_max, HitRecord<T>& rec) const = 0;
};