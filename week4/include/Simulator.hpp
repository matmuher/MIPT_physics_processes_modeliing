#pragma once

#include <array>
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
				// TODO: throw
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

	public:

		HarmonicOscillatorT(T w)
		:
			w_{w},
			DiffEqSystem<T, 2>(setOscillatorEquationSystem())
		{}

		T f1(const vec<T, 2>& stateVec) const
		{
			return DiffEqSystem<T, 2>::f(stateVec, 0)[0];
		}

		T f2(const vec<T, 2>& stateVec) const
		{
			return DiffEqSystem<T, 2>::f(stateVec, 0)[1];
		}

		T w() const
		{
			return w_;
		}	
	};

	using HarmonicOscillator = HarmonicOscillatorT<float>;
};
