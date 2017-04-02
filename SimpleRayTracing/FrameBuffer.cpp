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
// FileName:	FrameBuffer.cpp
// CreateDate:	2016-12-21
//
// E-Mail:		frankpei1992@gmail.com
//
// Descript:    Í¼ÏñBuffer
// 
//////////////////////////////////////////////////////////////////////////

#include "FrameBuffer.h"

#include "Assert.hpp"

FrameBuffer::FrameBuffer(long width, long height )
	: width_(width)
	, height_(height)
	, buffer_(width * height * 4, 0)
{
	
}

FrameBuffer::~FrameBuffer()
{

}

void FrameBuffer::Clear()
{
	buffer_.clear();
}

void FrameBuffer::Resize(long width, long height)
{
	width_ = width;
	height_ = height;

	buffer_.resize(width_ * height * 4, 0);
}

void FrameBuffer::SetColor( math3D::Color &&color, long x, long y )
{
	ENSURE_ASSERT(ENSURE(x < width_ && y < height_)(x)(y), "IndexOutOfBoundsException");

	auto* data_ptr = &buffer_.front() + (width_ * y + x) * 4;

	color.RGBA(data_ptr[2], data_ptr[1], data_ptr[0], data_ptr[3]);
}

void FrameBuffer::SetColor( const math3D::Color &color, long x, long y )
{
	ENSURE_ASSERT(ENSURE(x < width_ && y < height_)(x)(y), "IndexOutOfBoundsException");

	auto* data_ptr = &buffer_.front() + (width_ * y + x) * 4;

	color.RGBA(data_ptr[2], data_ptr[1], data_ptr[0], data_ptr[3]);
}
