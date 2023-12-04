#pragma once

/*
	class Equation:
		
		+ Equation(vector<function_t> f);

		+ Vec f(t, y);


	RK4Solver::fillSolution()
	{
		for (...)
		{
			k1 = f(t, prevSolution);

			k2 = f(t + deltaT/2, prevSolution + k1 * deltaT/2);

			k3 = f(t + deltaT/2, prevSolution + k2 * deltaT/2);

			k4 = f(t + deltaT, prevSolution + k3 * deltaT);

			currSolution = prevSolution + h * (k1 + 2 k2 + 2 k3 + k4)/6;

			AddSolution(currSolution);
		}
	}

	Todo:

		[] add vector operations: +, -, * vec, * scalar (go out from Vec2 -> Vec)

		[] add equation that gets vec and returns vector
*/
