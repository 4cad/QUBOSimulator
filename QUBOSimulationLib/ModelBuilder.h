#pragma once

#include "Model.h"

#include <vector>
#include <unordered_map>

#include "StdPairHash.h"

namespace QUBO {

    struct Variable {
        Variable(short i)
            : index(i)
        {
            if (index >= 64) {
                throw std::exception("Variable index must be less than 64.");
            }
            if (index < 0) {
                throw std::exception("Variable index must be positive.");
            }
        }

        short index;
    };

    struct LinearTermBuilder {
        explicit LinearTermBuilder(const Variable variable, double coeff)
            : variable(variable)
            , coeff(coeff)
        {}

        Variable variable;
        double coeff;
    };

    struct QuadraticTermBuilder {
        explicit QuadraticTermBuilder(const Variable var1, const Variable var2, double coeff)
            : var1(var1)
            , var2(var2)
            , coeff(coeff)
        {}

        const QuadraticTermBuilder operator*(double coeff) const
        {
            return QuadraticTermBuilder(var1, var2, this->coeff * coeff);
        }

        Variable var1;
        Variable var2;
        double coeff;
    };

    const LinearTermBuilder operator*(const Variable var, double coeff);
    const QuadraticTermBuilder operator*(const Variable var1, const Variable var2);

    class ModelBuilder {
    public:
        // These are meant to be used in temporary expressions only, and be written only once since there is no lookup being done.
        // Subsequent calls to Q or L can invalidate the double reference returned. 
        float& Q(Variable a, Variable b);
        float& L(Variable a);

        void operator+=(const LinearTermBuilder linear_term) {
            L(linear_term.variable) = linear_term.coeff;
        }

        void operator+=(const QuadraticTermBuilder q )  {
            Q(q.var1, q.var2) = q.coeff;
        }

        short VariableCount() { return variable_count_; }


        Variable NewVar() { Variable result(variable_count_); variable_count_ += 1; return result; }

        // Once this is called, the add functions will trigger an error. Model is built once and then cached
        Model* Build();

    private:
        void UpdateVariableCount(short var);

        Model *model_ = nullptr;
        short variable_count_ = 0;

        std::unordered_map<short, float> linear_terms_;
        std::unordered_map<std::pair<short,short>, float> quadratic_terms_; // first element of the pair must always be less than second
    };
}