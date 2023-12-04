#pragma once

#include <linalg.h>

namespace hos //harmonic oscillator simulator
{		
	using namespace linalg::ostream_overloads;
	using namespace linalg;

	using Vec2 = vec<float_t, 2>;

	template<class T>
	struct RangeT
	{
		T t1;
		T t2;
		size_t sampleNum;
	};

	using Range = RangeT<float_t>;
};