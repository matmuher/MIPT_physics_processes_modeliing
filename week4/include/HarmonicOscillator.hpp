#pragma once

#include <Simulator.hpp>

namespace hos
{
	class HarmonicOscillator
	{
		const float_t w_;

	public:
	
		HarmonicOscillator(float_t w)
		:
			w_{w} // ?? vs define "_w" as "w" and initialize it like "this->w{w}"
		{}

		float_t f1(Vec2 vec) const // ?? Different types of oscillators should describe their equations
		{
			return vec.v;
		}

		float_t f2(Vec2 vec) const
		{
			return -w_ * w_ * vec.x;
		}

		float_t w() const
		{
			return w_;
		}
	};
};
