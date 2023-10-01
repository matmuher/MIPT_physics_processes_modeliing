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

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include <EulerSolver.hpp>
#include <AnalyticalSolver.hpp>

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

using json = nlohmann::json;

std::string getConfigPath(const int argc, const char* argv[])
{
	const std::string DefaultPath = "config.json";

	if (argc < 2)
	{
		return DefaultPath;
	}

	return argv[1];
}

int main(const int argc, const char* argv[])
{
	const std::string configFileName = getConfigPath(argc, argv);

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
	hos::Range tRange{config["t1"], config["t2"], config["sampleNum"]};

	hos::AnalyticalSolver analyticalSolver{w, startConds, tRange, "analytical_output.bin"};
	hos::EulerSolver eulerSolver{w, startConds, tRange, "euler_output.bin"};

	analyticalSolver.computeSolutions();
	analyticalSolver.dumpSolutions();

	eulerSolver.computeSolutions();
	eulerSolver.dumpSolutions();

	return 0;
}