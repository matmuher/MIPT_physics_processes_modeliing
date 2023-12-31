#pragma once

#include <Solver.hpp>

namespace hos
{
	template<class T, int N>
	class EulerSolverT : public SolverT<T, N>
	{
		using SolverT<T, N>::diffSystem_;

		using SolverT<T, N>::deltaT;

		using SolverT<T, N>::tRange_;

		using SolverT<T, N>::startConds_;

		void fillSolutions() override;

	public:

		EulerSolverT(DiffEqSystem<T, N> diffSystem,
					vec<T, N> startConds,
					RangeT<T> tRange)
		:
			SolverT<T, N>{diffSystem, startConds, tRange}
		{}
	};

	/*
		this iteration through time samples is common for every solver.
		may be move this part to superclass. so its method will be look like:

		void Solver::fillSolutionVec()
		{
			for (float_t t = tRange.t1; t < tRange.t2; t += deltaT)
			{
				addSolution(computeSolution(t));
			}
		}

		where computeSolution(t) - call of subclass's method
	*/
	template<class T, int N>
	void EulerSolverT<T, N>::fillSolutions()
	{
		vec<T, N> prevSolution = startConds_;

		for (T t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			vec<T, N> currSolution{};

			currSolution = prevSolution + deltaT * diffSystem_.f(prevSolution, t);

			SolverT<T, N>::addSolution(currSolution);

			prevSolution = currSolution;
		}
	}

	using EulerSolver = EulerSolverT<float, 2>;
};