#include <fstream>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <EulerSolver.hpp>
#include <AnalyticalSolver.hpp>
#include <HeunSolver.hpp>

/*
	[x] Implement Analytical solver

	[x] Implement Euler method solver

		https://en.wikipedia.org/wiki/Euler_method

	[x] Plot Euler and Analytical solutions

	[x] Config solvers with json file

	[x] Start solvers from python script

	[x] Implement Heun method:
		
		https://en.wikipedia.org/wiki/Heun%27s_method

	[] Plot energy

	[] Plot phase diagrams

	[] Add Equation class

	[] Assess influence of Kahan summation:
	
		https://en.wikipedia.org/wiki/Kahan_summation_algorithm
*/

// TODO: process multiple config paths
// solver.exe few_samples_config.json many_samples_config.json 

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
	hos::HarmonicOscillator hOs{config["w"]};
	hos::Range tRange{config["t1"], config["t2"], config["sampleNum"]};

	hos::AnalyticalSolver analyticalSolver{hOs, startConds, tRange, "analytical_output.bin"};
	hos::EulerSolver eulerSolver{hOs, startConds, tRange, "euler_output.bin"};
	hos::HeunSolver heunSolver{hOs, startConds, tRange, "heun_output.bin"};

	analyticalSolver.computeSolutions();
	analyticalSolver.dumpSolutions();

	eulerSolver.computeSolutions();
	eulerSolver.dumpSolutions();

	heunSolver.computeSolutions();
	heunSolver.dumpSolutions();

	return 0;
}