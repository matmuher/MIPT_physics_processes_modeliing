#pragma once

#include <Solver.hpp>

namespace hos
{
	class HeunSolver : public Solver
	{
		void fillSolutions() override;

	public:

		HeunSolver(float_t w, Vec2 startConds, Range tRange, const std::string& fileName)
		:
			Solver{w, startConds, tRange, fileName}
		{}
	};

	void HeunSolver::fillSolutions()
	{
		Vec2 prevSolution = startConds_;

		for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			Vec2 intermediateSolution{};

			// y_{k+1} = y_{k} + deltaT * f(y_{k})
			intermediateSolution.x = prevSolution.x + deltaT * prevSolution.v;
			intermediateSolution.v = prevSolution.v + deltaT * (-w_ * w_ * prevSolution.x);
			//        -------------------------------------------------------^
			//        |
			// It's easy to make a mistake in formulas f(y_{k}) part
			// It's better tp wrap initial equation in class

			Vec2 currSolution{};

			currSolution.x =	prevSolution.x +
							 	deltaT / 2 * (prevSolution.v + intermediateSolution.v);

			currSolution.v = 	prevSolution.v +
							 	deltaT / 2 * (-w_ * w_ * prevSolution.x + -w_ * w_ * intermediateSolution.x);

			addSolution(currSolution);

			prevSolution = currSolution;
		}
	}
};