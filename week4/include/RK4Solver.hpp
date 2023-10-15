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
			Vec2 k1{};

			// y*_{k+1} = y_{k} + deltaT * f(y_{k})
			k1.x = hOs_.f1(prevSolution);
			k1.y= hOs_.f2(prevSolution);

			Vec2 k2{};

			Vec2 k2_tmp{prevSolution.x + k1.x * (deltaT/2), prevSolution.y+ k1.y* (deltaT/2)};
			k2.x = hOs_.f1(k2_tmp);
			k2.y= hOs_.f2(k2_tmp) ;

			Vec2 k3{};

			Vec2 k3_tmp{prevSolution.x + k2.x * (deltaT/2), prevSolution.y+ k2.y* (deltaT/2)};
			k3.x = hOs_.f1(k3_tmp);
			k3.y= hOs_.f2(k3_tmp);			

			Vec2 k4{};

			Vec2 k4_tmp{prevSolution.x + k3.x * (deltaT), prevSolution.y+ k3.y* (deltaT)};
			k4.x = hOs_.f1(k4_tmp);
			k4.y= hOs_.f2(k4_tmp);			

			Vec2 currSolution{};

			// y_{k+1} = y_{k} + deltaT / 2 * (f(y_{k} + f(y*_{k+1}))
			currSolution.x =	prevSolution.x +
							 	deltaT * (k1.x + 2 * k2.x + 2 * k3.x + k4.x) / 6;

			currSolution.y= 	prevSolution.y+
							 	deltaT * (k1.y+ 2 * k2.y+ 2 * k3.y+ k4.y) / 6;

			addSolution(currSolution);

			prevSolution = currSolution;
		}
	}
};