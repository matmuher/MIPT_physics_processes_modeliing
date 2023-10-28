#include <fstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <EulerSolver.hpp>
#include <AnalyticalSolver.hpp>
#include <HeunSolver.hpp>
#include <RK4Solver.hpp>

#include <HarmonicSystem.hpp>
#include <PhysicSystem.hpp>

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

/*
	Задача: в зависимости от конфиг файла конструировать
	модель опредленного типа

	1) Обернуть в умный указатель

	2) Создать Oscillator'ы как статические переменные
	и выдать ссылки на них (синглтон) 

	Это адекватная идея параметризовать каждый запуск опредленной моделью?
	Или лучше прогонять через все модели сразу?
*/
const hos::DiffEqSystem<float, 2>& getDifEqSystem(const json& config)
{
	const std::string modelName = config["model"];

	if (modelName == "Harmonic")
	{
		return hos::HarmonicOscillatorT<float>::getDiffEqSystem(config["w"]);
	}

	if (modelName == "Physic")
	{
		return hos::PhysicsOscillatorT<float>::getDiffEqSystem(config["w"]);
	}

	// if (modelName == "Damped")
	// {
	// 	return hos::DampedOscillator{config["w"], config["damp_ratio"]};
	// }

	return hos::HarmonicOscillatorT<float>::getDiffEqSystem(config["w"]);
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

	const hos::DiffEqSystem<float, 2>& diffSystem = getDifEqSystem(config);

	hos::Vec2 startConds{config["x0"], config["v0"]};
	hos::Range tRange{config["t1"], config["t2"], config["sampleNum"]};

	// hos::AnalyticalSolver analyticalSolver{hOs, startConds, tRange, "analytical_output.bin"};
	hos::EulerSolver eulerSolver{diffSystem, startConds, tRange, "euler_output.bin"};
	hos::HeunSolver heunSolver{diffSystem, startConds, tRange, "heun_output.bin"};
	hos::RK4Solver rk4Solver{diffSystem, startConds, tRange, "rk4_output.bin"};

	std::vector<hos::Solver*> solvers;

	// solvers.push_back(&analyticalSolver);
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