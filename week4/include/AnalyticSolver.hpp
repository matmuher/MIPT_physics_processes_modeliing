#pragma once

#include <Solver.hpp>
#include <linalg.h>

namespace hos
{
    template<class T>
    using SolutionFunc = std::function<T(T)>;

    template<class T, int N>
    using SolutionFuncVec = vec<SolutionFunc<T>, N>;

    template <class T, int N>
    class AnalyticSolverT : public SolverT<T, N>
    {
        
        vec<SolutionFunc<T>, N> solFuncVec_;

    public:

        AnalyticSolverT(vec<SolutionFunc<T>, N> solFuncVec,
                        vec<T, N> startConds,
				        RangeT<T> tRange)
        :
            SolverT{startConds, tRange},
            solFuncVec_{solFuncVec}
        {}

        void fillSolutions() override
        {
            for (float_t t = tRange_.t1; t < tRange_.t2; t += deltaT)
            {
                vec<T, N> currSolution = ;

                SolverT<T, N>::addSolution();
            }
        }
    };

};