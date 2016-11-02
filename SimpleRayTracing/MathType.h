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
// 文件名称:		MathType.h
// 创建时间:		2016-11-02
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     Math3D头文件声明
// 
//////////////////////////////////////////////////////////////////////////

#ifndef _MATH3D_TYPE_H_
#define _MATH3D_TYPE_H_

#include "Vector.hpp"
#include "Martix.hpp"
#include "Color.hpp"

namespace math3D {
typedef VectorT < int, 2 > int2;
typedef VectorT < int, 3 > int3;
typedef VectorT < int, 4 > int4;
typedef VectorT < float, 2 > float2;
typedef VectorT < float, 3 > float3;
typedef VectorT < float, 4 > float4;
typedef VectorT < double, 2 > double2;
typedef VectorT < double, 3 > double3;
typedef VectorT < double, 4 > double4;

typedef MatrixT<int, 2, 2> int2x2;
typedef MatrixT<int, 3, 3> int3x3;
typedef MatrixT<int, 4, 4> int4x4;
		  
typedef MatrixT<float, 2, 2> float2x2;
typedef MatrixT<float, 3, 3> float3x3;
typedef MatrixT<float, 4, 4> float4x4;
		  
typedef MatrixT<double, 2, 2> double2x2;
typedef MatrixT<double, 3, 3> double3x3;
typedef MatrixT<double, 4, 4> double4x4;
}

#endif
