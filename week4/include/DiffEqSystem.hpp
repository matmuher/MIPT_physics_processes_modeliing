#pragma once

#include <array>
#include <stdexcept>

#include <linalg.h>

#include <Simulator.hpp>

namespace hos //harmonic oscillator simulator
{		
	template<class T, int N>
	using FuncType = std::function<T(vec<T, N>, T)>; 

	template<class T, int N>
	struct FuncVector
	{
		vec<FuncType<T, N>, N> funcStore;

		const FuncType<T, N>& operator[] (int k) const
		{
			if (k < N)
			{
				return funcStore[k];
			}
			else
			{
				std::cerr << "Cant apply to " << k << "th func\n";
				throw std::out_of_range("Out of function vecotr");
			}
		}

		FuncType<T, N>& operator[] (int k) // TODO: COPYPASTE
		{
			if (k < N)
			{
				return funcStore[k];
			}
			else
			{
				std::cerr << "Cant apply to " << k << "th func\n";
				throw std::out_of_range("Out of function vecotr");
			}
		}
	};

	template<class T, int N>
	class DiffEqSystem
	{
		const FuncVector<T, N> funcVector_;

	public:

		DiffEqSystem(const FuncVector<T, N>& funcVector)
		:
			funcVector_{funcVector}
		{}

		vec<T, N> f(const vec<T, N>& stateVec, T t = 0) const
		{
			vec<T, N> result{};

			for (size_t coordId = 0; coordId < N; ++coordId)
			{
				result[coordId] = funcVector_[coordId](stateVec, t);
			}

			return result;
		}
	};
};
