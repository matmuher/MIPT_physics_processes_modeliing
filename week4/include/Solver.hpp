#pragma once

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <Simulator.hpp>
#include <DiffEqSystem.hpp>

namespace hos //harmonic oscillator simulator
{
	std::ostream& operator<< (std::ostream& cout, const Vec2& vec)
	{
		cout << '[' << vec.x << ',' << vec.y<< ']';
		return cout;
	}

	template<class T, int N>
	class SolverT
	{
		public:

		SolverT(DiffEqSystem<T, N> diffSystem,
				vec<T, N> startConds,
				RangeT<T> tRange,
				const std::string& fileName);
	
		void computeSolutions();

		void dumpSolutions() const;

	protected:

		DiffEqSystem<T, N> diffSystem_;
		const vec<T, N> startConds_;
		const RangeT<T> tRange_;

		// Is it ok to name one variable with postfix '_'
		// and another without it?
		const T deltaT;

		virtual void fillSolutions() = 0;

		void addSolution(vec<T, N> solution);

	private:

		std::vector<vec<T, N>> solutionVec;

		const std::string fileName_; // Seems like it shouldn't belong to Solver class
	};

	template<class T, int N>
	SolverT<T, N>::SolverT(DiffEqSystem<T, N> diffSystem,
			vec<T, N> startConds,
			RangeT<T> tRange,
			const std::string& fileName)
	:
		diffSystem_{diffSystem},
		startConds_{startConds},
		tRange_{tRange},
		deltaT{(tRange.t2 - tRange.t1) / tRange.sampleNum},
		fileName_{fileName}
	{}

	template<class T, int N>
	void SolverT<T, N>::computeSolutions()
	{
		solutionVec.clear();
		solutionVec.reserve(tRange_.sampleNum);
		
		addSolution(startConds_);

		fillSolutions();
	}

	template<class T, int N>
	void SolverT<T, N>::addSolution(vec<T, N> solution)
	{
		solutionVec.push_back(solution); // vs use solutionVec[i] = solution?
	}

	template<class T, int N>
	void SolverT<T, N>::dumpSolutions() const
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

	using Solver = SolverT<float, 2>; 
};