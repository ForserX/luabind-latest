// Copyright (c) 2003 Daniel Wallin and Arvid Norberg

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#include <string>
#include <vector>

#include <luabind/config.hpp>
#include <luabind/detail/class_rep.hpp>

namespace luabind
{
	template <typename T>
	concept convertible_to_int = std::is_convertible_v<T, int>;

	struct value
	{
		friend class vector_class<value>;

		template <convertible_to_int T> value(const char* name, T v) : name_(name), val_(v) {}

		const char* name_ = nullptr;
		int         val_  = 0;

	  private:
		value() {}
	};

	namespace detail
	{

		template <typename From> struct enum_maker
		{
			explicit enum_maker(From&& from) : from_(std::forward<From>(from)) {}

			enum_maker(const enum_maker&)            = delete;
			enum_maker& operator=(const enum_maker&) = delete;

			enum_maker(enum_maker&&) noexcept            = default;
			enum_maker& operator=(enum_maker&&) noexcept = default;

			template <typename... Args> From operator[](Args... args) &&
			{
				(from_.add_static_constant(args.name_, args.val_), ...);
				return std::move(from_);
			}

		  private:
			From from_;
		};
	} // namespace detail
} // namespace luabind
