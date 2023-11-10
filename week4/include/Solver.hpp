#pragma once

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include <Simulator.hpp>
#include <DiffEqSystem.hpp>

namespace hos //harmonic oscillator simulator
{
	std::ostream& operator<< (std::ostream& cout, const Vec2& vec)
	{
		cout << '[' << vec.x << ',' << vec.y<< ']';
		return cout;
	}

	struct BufferInfo
	{
		const char* startPointer;
		size_t size;
	};

	template<class T, int N>
	class SolverT
	{
		public:

		SolverT(DiffEqSystem<T, N> diffSystem,
				vec<T, N> startConds,
				RangeT<T> tRange);
	
		void computeSolutions();

		void dumpSolutions() const;

		BufferInfo getBuffer() const;

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
	};

	template<class T, int N>
	SolverT<T, N>::SolverT(DiffEqSystem<T, N> diffSystem,
			vec<T, N> startConds,
			RangeT<T> tRange)
	:
		diffSystem_{diffSystem},
		startConds_{startConds},
		tRange_{tRange},
		deltaT{(tRange.t2 - tRange.t1) / tRange.sampleNum}
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
	BufferInfo SolverT<T, N>::getBuffer() const
	{
		return
		BufferInfo
		{
			(const char*) &solutionVec[0],
			solutionVec.size() * sizeof(solutionVec[0])
		};
	}

	void SaveBuffer(const std::string& fileName, BufferInfo bufferInfo)
	{
		std::ofstream fileOutputStream(fileName, std::ios::binary);
		if (!fileOutputStream)
		{
			perror("");
			std::cerr << "Cant open file for binary output: " << fileName << '\n';
			return;
		}

		fileOutputStream.write(bufferInfo.startPointer, bufferInfo.size);
	}

	using Solver = SolverT<float, 2>; 
};