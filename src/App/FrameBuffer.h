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
// 文件名称:		FrameBuffer.h
// 创建时间:		2016-11-03
//
// 作者信息:		裴博翔
// 联系方式:		frankpei1992@gmail.com
//
// 作用描述:     图像Buffer
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <vector>

#include "Color.hpp"

class FrameBuffer
{
	using type = std::vector<uint8_t>;

public:
	FrameBuffer(long width, long height);

	~FrameBuffer();

	const void* Data() const
	{
		return buffer_.data();
	}

	long GetWidth() const
	{
		return  width_;
	}

	long GetHeight() const
	{
		return height_;
	}

	void Clear();

	void Resize( long width, long height );

	void SetColor(math3D::Color&& color, long x, long y);

	void SetColor(const math3D::Color& color, long x, long y);

private:
	long	width_;
	long	height_;
	type	buffer_;
};

