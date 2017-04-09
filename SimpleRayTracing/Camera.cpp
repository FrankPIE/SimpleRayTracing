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
// FileName:	Camera.cpp
// CreateDate:	2017-04-09
//
// E-Mail:		frankpei1992@gmail.com
//
// Descript:    Ïà»ú
// 
//////////////////////////////////////////////////////////////////////////

#include "Camera.h"

Camera::Camera( const math3D::double3 &origin, const math3D::double3 &lower_left_corner, const math3D::double3 &horizontal, const math3D::double3 &vertical )
	: origin_(origin)
	, lower_left_corner_(lower_left_corner)
	, horizontal_(horizontal)
	, vertical_(vertical)
{ }

Camera::Camera( math3D::double3 &&origin, math3D::double3 &&lower_left_corner, math3D::double3 &&horizontal, math3D::double3 &&vertical )
	: origin_(std::move(origin))
	, lower_left_corner_(std::move(lower_left_corner))
	, horizontal_(std::move(horizontal))
	, vertical_(std::move(vertical))
{ }

math3D::RayD Camera::ray( double u, double v )
{
	return std::move(math3D::RayD(origin_, (lower_left_corner_ + u * horizontal_ + v * vertical_) - origin_));
}
