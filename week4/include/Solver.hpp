#pragma once

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <HarmonicOscillator.hpp>

namespace hos //harmonic oscillator simulator
{
	std::ostream& operator<< (std::ostream& cout, const Vec2& vec)
	{
		cout << '[' << vec.x << ',' << vec.y<< ']';
		return cout;
	}

	class Solver
	{
	public:

		Solver(HarmonicOscillator hOs, Vec2 startConds, Range tRange, const std::string& fileName);
	
		void computeSolutions();

		void dumpSolutions() const;

	protected:

		HarmonicOscillator hOs_;
		const Vec2 startConds_;
		const Range tRange_;

		// Is it ok to name one variable with postfix '_'
		// and another without it?
		const float_t deltaT;

		virtual void fillSolutions() = 0;

		void addSolution(Vec2 solution);

	private:

		std::vector<Vec2> solutionVec;

		const std::string fileName_; // Seems like it shouldn't belong to Solver class
	};

	Solver::Solver(HarmonicOscillator hOs, Vec2 startConds, Range tRange, const std::string& fileName)
	:
		hOs_{hOs},
		startConds_{startConds},
		tRange_{tRange},
		deltaT{(tRange.t2 - tRange.t1) / tRange.sampleNum},
		fileName_{fileName}
	{}

	void Solver::computeSolutions()
	{
		solutionVec.clear();
		solutionVec.reserve(tRange_.sampleNum);
		
		addSolution(startConds_);

		fillSolutions();
	}

	void Solver::addSolution(Vec2 solution)
	{
		solutionVec.push_back(solution); // vs use solutionVec[i] = solution?
	}

	void Solver::dumpSolutions() const
	{
		std::ofstream fileOutputStream(fileName_, std::ios::binary);
		if (!fileOutputStream)
		{
			perror("");
			std::cerr << "Cant open file for binary output: " << fileName_ << '\n';
			return;
		}

		fileOutputStream.write((const char*) &solutionVec[0], solutionVec.size() * sizeof(solutionVec[0]));
	}
};