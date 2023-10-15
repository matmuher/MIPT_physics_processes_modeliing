#pragma once

#include <array>
#include <linalg.h>

namespace hos //harmonic oscillator simulator
{		
	using namespace linalg::ostream_overloads;
	using namespace linalg;

	using Vec2 = vec<float_t, 2>;

	struct Range
	{
		float_t t1;
		float_t t2;
		size_t sampleNum;
	};
};
