#include <fstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <EulerSolver.hpp>
#include <AnalyticalSolver.hpp>
#include <HeunSolver.hpp>
#include <RK4Solver.hpp>

/*
	We want to process with Euler method
	different systems:

		equation: different right hands

			+ v' = f1(x, y)
			+ x' = f2(x, y)

		condition

		method

			+ Euler, RK4...

	Condition of system:

		+ (x, v, t)

	Upcoming features:

		[] Make N dimensions arithmetic

		[] Make equation more abstract to easily add new essence to system

		[] Make solver able to solve equations of random order and any nature

		[] Make wrapper for condition that allows one-way traversing


	!! Oscillator !! - essence that contains Equations:

	std::array<equ_type, 2> harmonic_oscillator_equation_set = {f1, f2};
	Oscillator harmonic_oscillator{harmonic_oscillator_equation_set};

	Oscillator oscillator{harmonic_oscillator_equation_set};

	!! Solver !!

	currentVec = Oscillator.getVec(prevVec, t);
*/

/*
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

#include <functional>

namespace hos
{

};

float f1(hos::vec<float, 2> v, float t)
{
	return v.x + v.y;
}

float f2(hos::vec<float, 2> v, float t)
{
	return v.x - v.y;
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

	hos::Vec2 startConds{config["x0"], config["v0"]};
	hos::HarmonicOscillator hOs{config["w"]};
	hos::Range tRange{config["t1"], config["t2"], config["sampleNum"]};

	hos::AnalyticalSolver analyticalSolver{hOs, startConds, tRange, "analytical_output.bin"};
	hos::EulerSolver eulerSolver{hOs, startConds, tRange, "euler_output.bin"};
	hos::HeunSolver heunSolver{hOs, startConds, tRange, "heun_output.bin"};
	hos::RK4Solver rk4Solver{hOs, startConds, tRange, "rk4_output.bin"};

	std::vector<hos::Solver*> solvers;

	solvers.push_back(&analyticalSolver);
	solvers.push_back(&eulerSolver);
	solvers.push_back(&heunSolver);
	solvers.push_back(&rk4Solver); 

	for (size_t solverId = 0; solverId < solvers.size(); solverId++)
	{
		solvers[solverId]->computeSolutions();
		solvers[solverId]->dumpSolutions();
	}

	return 0;
}