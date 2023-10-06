#pragma once

#include <Solver.hpp>

namespace hos
{
	class AnalyticalSolver : public Solver
	{
		void fillSolutions() override;
	
		Vec2 getSolution(float_t t) const;

	public:

		AnalyticalSolver(HarmonicOscillator hOs, Vec2 startConds, Range tRange, const std::string& fileName)
		:
			Solver{hOs, startConds, tRange, fileName}
		{}
	};

	void AnalyticalSolver::fillSolutions()
	{
		for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
		{
			Vec2 currSolution = getSolution(t + deltaT);

			addSolution(currSolution);
		}
	}

	Vec2 AnalyticalSolver::getSolution(float_t t) const
	{
		Vec2 solution{};

		// TODO: consider  that when t0 != 0 coeffs should differ
		
		float_t w_ = hOs_.w();
		solution.x = startConds_.x * cos(w_ * t) 		+ startConds_.v / w_ * sin(w_ * t);
		solution.v = -startConds_.x * w_ * sin(w_ * t) 	+ startConds_.v * cos(w_ * t);

		return solution;
	}

};