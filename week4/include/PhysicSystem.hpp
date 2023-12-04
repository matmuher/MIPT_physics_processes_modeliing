#pragma once

#include <array>
#include <linalg.h>

#include <DiffEqSystem.hpp>

namespace hos //harmonic oscillator simulator
{		
	/*

		Teta'' + w^2 * sin(Teta) = 0

		Teta' = V
		V' = -w^2 * sin(Teta)

	*/

	template<class T>
	class PhysicsOscillatorT : public DiffEqSystem<T, 2>
	{
		const T w_;

		FuncVector<T, 2> setOscillatorEquationSystem() // make it virtual?
		{
			FuncVector<T, 2> funcVector;

			funcVector[0] =  [](const vec<T, 2>& stateVec, T t) -> T
								{
									return stateVec.y;
								};

			funcVector[1] =  [this](const vec<T, 2>& stateVec, T t) -> T
								{
									return -w_ * w_ * sin(stateVec.x);
								};

			return funcVector;
		}

		PhysicsOscillatorT(T w)
		:
			w_{w},
			DiffEqSystem<T, 2>(setOscillatorEquationSystem())
		{}

	public:

		static const PhysicsOscillatorT<T>& getDiffEqSystem(T w = 0)
		{
			static PhysicsOscillatorT<T> fOs{w};

			return fOs;
		}


		T w() const
		{
			return w_;
		}	
	};

	using PhysicsOscillator = PhysicsOscillatorT<float>;
};
