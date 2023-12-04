#pragma once

#include <array>
#include <linalg.h>

#include <DiffEqSystem.hpp>

namespace hos
{		
	template<class T>
	class HarmonicOscillatorT : public DiffEqSystem<T, 2>
	{
		const T w_;

		FuncVector<T, 2> setOscillatorEquationSystem()
		{
			FuncVector<T, 2> funcVector;

			funcVector[0] =  [](const vec<T, 2>& stateVec, T t) -> T
								{
									return stateVec.y;
								};

			funcVector[1] =  [this](const vec<T, 2>& stateVec, T t) -> T
								{
									return -w_ * w_ * stateVec.x;
								};

			return funcVector;
		}

		HarmonicOscillatorT(T w)
		:
			w_{w},
			DiffEqSystem<T, 2>(setOscillatorEquationSystem())
		{}

	public:

		static const HarmonicOscillatorT<T>& getDiffEqSystem(T w = 0)
		{
			static HarmonicOscillatorT<T> hOs{w};

			return hOs;
		}

		T w() const
		{
			return w_;
		}	
	};

	using HarmonicOscillator = HarmonicOscillatorT<float>;
};
