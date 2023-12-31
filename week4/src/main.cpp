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
#include <DampedSystem.hpp>
#include <HarmonicDrivenSystem.hpp>

std::string getConfigPath(const int argc, const char* argv[])
{
	const std::string DefaultPath = "config.json";

	if (argc < 2)
	{
		return DefaultPath;
	}

	return argv[1];
}

// TODO: use enum?
// TODO: DSL?
const hos::DiffEqSystem<float, 2>& getDifEqSystem(const json& config)
{
	const std::string modelName = config["model"];

	if (modelName == "Harmonic")
	{
		return hos::HarmonicOscillator::getDiffEqSystem(config["w"]);
	}

	if (modelName == "Physic")
	{
		return hos::PhysicsOscillator::getDiffEqSystem(config["w"]);
	}

	if (modelName == "Damped")
	{
		return hos::DampedOscillator::getDiffEqSystem(
														config["w"],
														config["damp_ratio"]
													);
	}

	if (modelName == "HarmonicDriven")
	{
		return hos::HarmonicDrivenOscillator::getDiffEqSystem(
														config["w"],
														config["damp_ratio"],
														config["m"],
														config["A"],
														config["Omega"]
														);
	}

	return hos::HarmonicOscillator::getDiffEqSystem(config["w"]);
}

// TODO: smart pointer?
hos::Solver* getSolver(	const std::string& solverName,
						const hos::DiffEqSystem<float, 2>& diffSystem,
						const hos::Vec2& startConds,
						const hos::Range& tRange
	)
{
	if (solverName == "rk4")
	{
		return new hos::RK4Solver(diffSystem, startConds, tRange);
	}

	if (solverName == "euler")
	{
		return new hos::EulerSolver(diffSystem, startConds, tRange);
	}

	if (solverName == "heun")
	{
		return new hos::HeunSolver(diffSystem, startConds, tRange);
	}

	return new hos::RK4Solver(diffSystem, startConds, tRange);
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

	auto diffSystem = getDifEqSystem(config);

	hos::Vec2 startConds{	config["x0"],
							config["v0"]};
	
	hos::Range tRange{	config["t1"],
						config["t2"],
						config["sampleNum"]};

	hos::Solver* solver = getSolver(config["solver"],
									diffSystem,
									startConds,
									tRange);

	solver->computeSolutions();

	hos::SaveBuffer(config["output"], solver->getBuffer());

	return 0;
}