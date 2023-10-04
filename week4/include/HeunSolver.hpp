#pragma once

#include <Solver.hpp>

namespace hos
{
	class HeunSolver : public Solver
	{
		void fillSolutions() override;

	public:

		HeunSolver(HarmonicOscillator hOs, Vec2 startConds, Range tRange, const std::string& fileName)
		:
			Solver{hOs, startConds, tRange, fileName}
		{}
	};

	void HeunSolver::fillSolutions()
	{
		Vec2 prevSolution = startConds_;

		for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			Vec2 intermediateSolution{};

			// y_{k+1} = y_{k} + deltaT * f(y_{k})
			intermediateSolution.x = prevSolution.x + deltaT * hOs_.f1(prevSolution);
			intermediateSolution.v = prevSolution.v + deltaT * hOs_.f2(prevSolution);
			//        -------------------------------------------------------^
			//        |
			// It's easy to make a mistake in formulas f(y_{k}) part
			// It's better tp wrap initial equation in class

			Vec2 currSolution{};

			currSolution.x =	prevSolution.x +
							 	deltaT / 2 * (hOs_.f1(prevSolution) + hOs_.f1(intermediateSolution));

			currSolution.v = 	prevSolution.v +
							 	deltaT / 2 * (hOs_.f2(prevSolution) + hOs_.f2(intermediateSolution));

			addSolution(currSolution);

			prevSolution = currSolution;
		}
	}
};