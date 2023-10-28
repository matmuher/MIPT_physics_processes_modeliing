#pragma once

#include <Solver.hpp>

namespace hos
{
	template<class T, int N>
	class HeunSolverT : public SolverT<T, N>
	{
		using SolverT<T, N>::deltaT;

		using SolverT<T, N>::startConds_;

		using SolverT<T, N>::tRange_;

		using SolverT<T, N>::diffSystem_;

		void fillSolutions() override;

	public:

		HeunSolverT(DiffEqSystem<T, N> diffSystem,
					vec<T, N> startConds,
					RangeT<T> tRange,
					const std::string& fileName)
		:
			SolverT<T, N>{diffSystem, startConds, tRange, fileName}
		{}
	};

	template<class T, int N>
	void HeunSolverT<T, N>::fillSolutions()
	{
		vec<T, N> prevSolution = startConds_;

		for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			Vec2 intermediateSolution{};

			// y*_{k+1} = y_{k} + deltaT * f(y_{k})

			intermediateSolution = prevSolution + deltaT * diffSystem_.f(prevSolution);

			vec<T, N> currSolution{};

			// y_{k+1} = y_{k} + deltaT / 2 * (f(y_{k} + f(y*_{k+1}))

			currSolution = 	prevSolution +
							deltaT / 2 *
							(
								diffSystem_.f(prevSolution) +
								diffSystem_.f(intermediateSolution) 
							);

			SolverT<T, N>::addSolution(currSolution);

			prevSolution = currSolution;
		}
	}
 
 	using HeunSolver = HeunSolverT<float, 2>;
};