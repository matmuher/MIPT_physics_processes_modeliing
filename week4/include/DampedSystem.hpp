#pragma once

#include <array>
#include <linalg.h>

#include <DiffEqSystem.hpp>

namespace hos
{		
	template<class T>
	class DampedOscillatorT : public DiffEqSystem<T, 2>
	{
		const T w_;

		const T damp_ratio_;

		FuncVector<T, 2> setOscillatorEquationSystem(T w, T damp_ratio)
		{
			FuncVector<T, 2> funcVector;

			funcVector[0] =  [](const vec<T, 2>& stateVec, T t) -> T
								{
									return stateVec.y;
								};

			funcVector[1] =  [w, damp_ratio](const vec<T, 2>& stateVec, T t) -> T
								{
									return (-w * w * stateVec.x) +
									(-2 * damp_ratio * w * stateVec.y);
								};

			return funcVector;
		}

		DampedOscillatorT(T w, T damp_ratio)
		:
			DiffEqSystem<T, 2>(setOscillatorEquationSystem(w, damp_ratio)),
			w_{w},
			damp_ratio_{damp_ratio}
		{}

	public:

		static const DampedOscillatorT<T>& getDiffEqSystem(T w = 0, T damp_ratio = 0)
		{
			static DampedOscillatorT<T> dOs{w, damp_ratio};

			return dOs;
		}

		T w() const
		{
			return w_;
		}

		T damp_ratio() const
		{
			return damp_ratio_;
		}
	};

	using DampedOscillator = DampedOscillatorT<float>;
};
