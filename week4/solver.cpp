/*
todo:

1. Write analytical solution to equation:

	x  = -w^2 * x

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
#include <vector>
#include <nlohmann/json.hpp>

namespace hos //harmonic oscillator simulator
{
	using float_t = float;

	struct Vec2
	{
		float_t x;
		float_t v;
	};

		struct Range
	{
		float_t t1;
		float_t t2;
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

	std::vector<Vec2> getEulerSolution(Vec2 startConds, float_t w, Range tRange, float_t deltaT)
	{
		std::vector<Vec2> solutionVec;
		solutionVec.reserve((tRange.t2 - tRange.t1) / deltaT);

		solutionVec.push_back(startConds);
		
		Vec2 prevSolution = startConds;

		for (float_t t = tRange.t1; t < tRange.t2; t += deltaT)
		{
			Vec2 currSolution{};

			currSolution.x = prevSolution.x + deltaT * prevSolution.v;
			currSolution.v = prevSolution.v + deltaT * (-w * w * prevSolution.x);

			solutionVec.push_back(currSolution);

			prevSolution = currSolution;
		}

		return solutionVec;
	}

	std::vector<Vec2> getAnalyticalSolution(Vec2 startConds, float_t w, Range tRange, float_t deltaT)
	{
		std::vector<Vec2> solutionVec;
		solutionVec.reserve((tRange.t2 - tRange.t1) / deltaT);

		solutionVec.push_back(startConds);
		
		for (float_t t = tRange.t1; t < tRange.t2; t += deltaT)
		{
			Vec2 currSolution = getAnalyticalSolution(startConds, w, t);

			solutionVec.push_back(currSolution);
		}

		return solutionVec;
	}

	void dumpSolutionVec(const std::vector<Vec2>& solutionVec, const std::string& fileName)
	{
		std::ofstream fileOutputStream(fileName, std::ios::binary);
		if (!fileOutputStream)
		{
			perror("");
			std::cerr << "Cant open file for binary output: " << fileName << '\n';
			return;
		}

		fileOutputStream.write((const char*) &solutionVec[0], solutionVec.size() * sizeof(solutionVec[0]));
	}

	// class Solver
	// {
	// 	const Oscillator oscillator_;
	// 	const Vec2 startConds_;
	// 	const Range tRange_;
	// 	const float_t deltaT_;

	// 	std::vector<Vec2> dataBuffer;

	// 	void computeAnalyticalSolution();

	// 	void computeEulerSolution();

	// public:

	// 	void dumpAnalyticalSolution();

	// 	void dumpEulerSolution;
	// };
}

/*
	This research is devoted to exploring numerical
	solutions of systems of linear differential equations.

	Every case will be determined by:
	{
		w, x0, v0, timeRange
	}

	These parameteres determine every model startup.

	Oscillator
	+ w, x0, v0, timeRange
	+ computeAnalyticalSolution()
	+ computeEulerSolution()
	+ computeSimplexSolution()
	+ dumpSolution
*/

/*
	euler method and analytical solution
	are equal in sample points!
*/

using json = nlohmann::json;

int main()
{
	const std::string configFileName = "config.json";
	std::ifstream configFileStream(configFileName);

	if (!configFileStream)
	{
		perror("");
		std::cerr << "Cant open config file: " << configFileName << '\n';
		return 1;
	}

	json config = json::parse(configFileStream);

	hos::Vec2 startConds{.x = config["x0"], .v = config["v0"]};
	hos::float_t w = config["w"];
	hos::Range tRange{config["t1"], config["t2"]};
	hos::float_t deltaT = config["deltaT"];

	hos::dumpSolutionVec(hos::getAnalyticalSolution(startConds, w, tRange, deltaT), "analytical.bin");
	hos::dumpSolutionVec(hos::getEulerSolution(startConds, w, tRange, deltaT), "euler.bin");

	return 0;
}