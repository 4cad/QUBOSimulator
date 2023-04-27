#pragma once

#include "Model.h"

#include <vector>
#include <unordered_map>

#include "StdPairHash.h"

namespace QUBO {

    class Variable {
    public:
        Variable(short i)
            : index_(i)
        {
            if (index_ >= 64) {
                throw std::exception("Variable index must be less than 64.");
            }
            if (index_ < 0) {
                throw std::exception("Variable index must be positive.");
            }
        }

        operator short() { return index_; }

    private:
        short index_;
    };

    class ModelBuilder {
    public:
        // These are meant to be used in temporary expressions only, and be written only once since there is no lookup being done.
        // Subsequent calls to Q or L can invalidate the double reference returned. 
        float& Q(Variable a, Variable b);

        float& L(Variable a);

        short VariableCount() { return variable_count_; }

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