#pragma once

namespace hos //harmonic oscillator simulator
{
	using float_t = float;

	struct Vec2
	{
		float_t x;
		float_t v;
	};

		struct Range
	{
		float_t t1;
		float_t t2;
		size_t sampleNum;
	};
};