#pragma once

#include <Solver.hpp>

namespace hos
{
	template<class T, int N>
	class RK4SolverT : public SolverT<T, N>
	{
		using SolverT<T, N>::diffSystem_;

		using SolverT<T, N>::deltaT;

		using SolverT<T, N>::tRange_;

		using SolverT<T, N>::startConds_;

		void fillSolutions() override;

	public:

		RK4SolverT(	DiffEqSystem<T, N> diffSystem,
					vec<T, N> startConds,
					RangeT<T> tRange,
					const std::string& fileName)
		:
			SolverT<T, N>{diffSystem, startConds, tRange, fileName}
		{}
	};

	template<class T, int N>
	void RK4SolverT<T, N>::fillSolutions()
	{
		vec<T, N> prevSolution = startConds_;

		for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			vec<T, N> k1 = diffSystem_.f(prevSolution);

			vec<T, N> k2 = diffSystem_.f(prevSolution + deltaT / 2 * k1);

			vec<T, N> k3 = diffSystem_.f(prevSolution + deltaT / 2 * k2);

			vec<T, N> k4 = diffSystem_.f(prevSolution + deltaT * k3);

			// y_{k+1} = y_{k} + deltaT / 2 * (f(y_{k} + f(y*_{k+1}))
			vec<T, N> currSolution = prevSolution + deltaT * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

			SolverT<T, N>::addSolution(currSolution);

			prevSolution = currSolution;
		}
	}

	using RK4Solver = RK4SolverT<float, 2>;
};