#pragma once

#include <HarmonicSystem.hpp>
#include <Solver.hpp>

namespace hos
{
	template<class T>
	class AnalyticalSolverT : public SolverT<T, 2> // TODO: generalize of 2 dimensions
	{
		using SolverT<T, 2>::deltaT;

		using SolverT<T, 2>::startConds_;

		using SolverT<T, 2>::tRange_;

		using SolverT<T, 2>::diffSystem_;

		void fillSolutions() override;
	
		vec<T, 2> getSolution(T t) const;

		T w_; 

	public:

		AnalyticalSolverT(	HarmonicOscillatorT<T> hOs,
							vec<T, 2> startConds,
							RangeT<T> tRange)
		:
			SolverT<T, 2>{hOs, startConds, tRange},
			w_{hOs.w()}
		{}
	};

	template<class T>
	void AnalyticalSolverT<T>::fillSolutions()
	{
		for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			vec<T, 2> currSolution = getSolution(t + deltaT);

			SolverT<T, 2>::addSolution(currSolution);
		}
	}

	template<class T>
	vec<T, 2> AnalyticalSolverT<T>::getSolution(T t) const
	{
		vec<T, 2> solution{1, 1};

		T B_coef = 1/w_ *
						(
							startConds_.x * w_ * sin(w_ * tRange_.t1) +
							startConds_.y * cos(w_ * tRange_.t1)
						);

		T A_coef = 1/w_ *
						(
							startConds_.x * w_ * cos(w_ * tRange_.t1) -
							startConds_.y * sin(w_ * tRange_.t1)
						);
						
		solution.x = A_coef * cos(w_ * t) + B_coef * sin(w_ * t);
		solution.y = -A_coef * w_ * sin(w_ * t) + B_coef * w_ * cos(w_ * t);

		return solution;
	}

	using AnalyticalSolver = AnalyticalSolverT<float>;
};