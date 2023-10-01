#pragma once

#include <Solver.hpp>

namespace hos
{
	class EulerSolver : public Solver
	{
		void fillSolutions() override;

	public:

		EulerSolver(float_t w, Vec2 startConds, Range tRange, const std::string& fileName)
		:
			Solver{w, startConds, tRange, fileName}
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
	void EulerSolver::fillSolutions()
	{
		Vec2 prevSolution = startConds_;

		for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			Vec2 currSolution{};

			currSolution.x = prevSolution.x + deltaT * prevSolution.v;
			currSolution.v = prevSolution.v + deltaT * (-w_ * w_ * prevSolution.x);

			addSolution(currSolution);

			prevSolution = currSolution;
		}
	}
};