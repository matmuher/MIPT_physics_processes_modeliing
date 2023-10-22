#pragma once

#include <Solver.hpp>

namespace hos
{
	class RK4Solver : public Solver
	{
		void fillSolutions() override;

	public:

		RK4Solver(HarmonicOscillator hOs, Vec2 startConds, Range tRange, const std::string& fileName)
		:
			Solver{hOs, startConds, tRange, fileName}
		{}
	};

	void RK4Solver::fillSolutions()
	{
		Vec2 prevSolution = startConds_;

		for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			Vec2 k1 = diffSystem_.f(prevSolution);

			Vec2 k2 = diffSystem_.f(prevSolution + deltaT / 2 * k1);

			Vec2 k3 = diffSystem_.f(prevSolution + deltaT / 2 * k2);

			Vec2 k4 = diffSystem_.f(prevSolution + deltaT * k3);

			// y_{k+1} = y_{k} + deltaT / 2 * (f(y_{k} + f(y*_{k+1}))
			Vec2 currSolution = prevSolution + deltaT * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

			addSolution(currSolution);

			prevSolution = currSolution;
		}
	}
};