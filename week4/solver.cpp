/*
todo:

1. Write analytical solution to equation:

	x'' = -w^2 * x

	<=> reduce it to system of linear differential equations

	/
	|	x' = v
	|	v' = -w^2 * x
	|	x0
	|	v0
	\

	Solution is:

	x = A * cos(w * t) + B * sin(w * t)
	v = -A * w * sin(w * t) + B * w * cos(w * t)

	x(t = 0) = A = x0
	v(t = 0) = B * w = v0

	x = x0 * cos(w * t) + v0 / w * sin(w * t)
	v = -x0 * w * sin(w * t) + v0 * cos(w * t)

2. Write numerical solution: Euler method

3. Dump values
4. Analyzer in python
*/

#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

namespace hos //harmonic oscillator simulator
{
	using float_t = float;

	struct Vec2
	{
		float_t x;
		float_t v;
	};

	std::ostream& operator<< (std::ostream& cout, const Vec2& vec)
	{
		cout << '[' << vec.x << ',' << vec.v << ']';
		return cout;
	}

	Vec2 getAnalyticalSolution(Vec2 startConditions, float_t t);

	Vec2 getAnalyticalSolution(Vec2 startConds, float_t w, float_t t)
	{
		Vec2 solution{};

		solution.x = startConds.x * cos(w * t) + startConds.v / w * sin(w * t);
		solution.v = -startConds.x * w * sin(w * t) + startConds.v * cos(w * t);

		return solution;
	}

	struct Range
	{
		float_t t1;
		float_t t2;
	};

	void dumpRange(Range tRange, float_t deltaT, Vec2 startConds, float_t w)
	{
		const std::string fileName = "output.bin";

		std::ofstream fileOutputStream(fileName, std::ios::binary);
		if (!fileOutputStream)
		{
			perror("");
			std::cerr << "Cant open file for binary output: " << fileName;
			return;
		}

		for (float_t t = tRange.t1; t <= tRange.t2; t += deltaT)
		{
			Vec2 solution = getAnalyticalSolution(startConds, w, t); // TODO: hardcoded function!
			std::cout << solution << '\n';

			// TODO: too much write operations!
			fileOutputStream.write((const char*) &solution, sizeof(solution));
		}
	}
}

int main()
{
	hos::Vec2 startConds{.x = 0, .v = 1};
	hos::float_t w = 2 * M_PI;
	hos::float_t deltaT = 0.01;

	dumpRange(hos::Range{0., 1.}, deltaT, startConds, w);

	return 0;
}