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

			// y*_{k+1} = y_{k} + deltaT * f(y_{k})
			intermediateSolution.x = prevSolution.x + deltaT * hOs_.f1(prevSolution);
			intermediateSolution.y= prevSolution.y+ deltaT * hOs_.f2(prevSolution);

			Vec2 currSolution{};

			// y_{k+1} = y_{k} + deltaT / 2 * (f(y_{k} + f(y*_{k+1}))
			currSolution.x =	prevSolution.x +
							 	deltaT / 2 * (hOs_.f1(prevSolution) + hOs_.f1(intermediateSolution));

			currSolution.y= 	prevSolution.y+
							 	deltaT / 2 * (hOs_.f2(prevSolution) + hOs_.f2(intermediateSolution));

			addSolution(currSolution);

			prevSolution = currSolution;
		}
	}
};