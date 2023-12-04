#pragma once

#pragma once

#pragma once

#include <array>
#include <linalg.h>

#include <DrivenSystem.hpp>

namespace hos
{		
	template<class T>
	class HarmonicDrivenOscillatorT : public DrivenOscillatorT<T>
	{
		DriveForce<T> createHarmonicF(T A, T Omega)
		{
			auto harmonicF = [A, Omega] (T t) -> T {return A * cos(Omega * t);};

			return harmonicF;
		}

		HarmonicDrivenOscillatorT(T w, T damp_ratio, T m, T A, T Omega)
		:
			 DrivenOscillatorT<T>(w, damp_ratio, m, createHarmonicF(A, Omega))
		{}

	public:

		static const HarmonicDrivenOscillatorT<T>& getDiffEqSystem(	T w = 0,
																	T damp_ratio = 0,
																	T m = 0,
																	T A = 0,
																	T Omega = 0
																)
		{
			static HarmonicDrivenOscillatorT<T> hrDrOs{w, damp_ratio, m, A, Omega};

			return hrDrOs;
		}
	};

	using HarmonicDrivenOscillator = HarmonicDrivenOscillatorT<float>;
};
