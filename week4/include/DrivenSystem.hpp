#pragma once

#pragma once

#include <array>
#include <linalg.h>

#include <DiffEqSystem.hpp>

namespace hos
{		
	template<class T>
	using DriveForce = std::function<T(T)>;

	template<class T>
	class DrivenOscillatorT : public DiffEqSystem<T, 2>
	{
		const T w_;

		const T damp_ratio_;

		FuncVector<T, 2> setOscillatorEquationSystem(	T w, 
														T damp_ratio,
														T m,
														DriveForce<T> driveForce)
		{
			FuncVector<T, 2> funcVector;

			funcVector[0] =  [](const vec<T, 2>& stateVec, T t) -> T
								{
									return stateVec.y;
								};

			funcVector[1] =  [w, damp_ratio, m, driveForce](const vec<T, 2>& stateVec, T t) -> T
								{
									return (-w * w * stateVec.x) +
									(-2 * damp_ratio * w * stateVec.y) +
									driveForce(t) / m;
								};

			return funcVector;
		}

	public:

		DrivenOscillatorT(T w, T damp_ratio, T m, DriveForce<T> driveForce)
		:
			DiffEqSystem<T, 2>(setOscillatorEquationSystem(	w,
															damp_ratio,
															m,
															driveForce)),
			w_{w},
			damp_ratio_{damp_ratio}
		{}

		T w() const
		{
			return w_;
		}

		T damp_ratio() const
		{
			return damp_ratio_;
		}
	};

	using DrivenOscillator = DrivenOscillatorT<float>;
};
