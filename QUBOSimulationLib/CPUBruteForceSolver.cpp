#include "CPUBruteForceSolver.h"

#include <limits>
#include <iostream>
#include <bitset>

namespace QUBO {
    Solution CPUBruteForceSolver::Solve(Model& model) {
        if (model.variable_count == 0)
            return Solution();

        size_t upper_bound = 1ull << model.variable_count;
        Solution best;
        best.objective = std::numeric_limits<double>::infinity(); // This should always be overridden by the 0 case
        for (size_t variables = 0; variables < upper_bound; variables++) {
            Solution candidate = Evaluate(model, variables);
            std::cout << "[" << std::bitset<8>(variables) << "] " << candidate.objective;
            if (candidate.objective < best.objective) {
                std::cout << "   <--- NEW BEST";
                best = candidate;
                
            }
            std::cout << std::endl;
        }
        return best;
    }

    Solution CPUBruteForceSolver::Evaluate(const Model& model, size_t variables) {
        Solution result;
        result.variables = variables;

        for (size_t i = 0; i < model.linear_term_count; i++) {
            const LinearTerm& term = model.linear_terms[i];
            result.objective += ((double)term.Coeff) * result[term.Variable];
        }

        for (size_t i = 0; i < model.quadratic_term_count; i++) {
            const QuadraticTerm& term = model.quadratic_terms[i];
            result.objective += ((double)term.Coeff) * result[term.Variable1] * result[term.Variable2];
        }

        return result;
    }
}