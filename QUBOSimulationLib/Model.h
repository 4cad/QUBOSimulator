#pragma once

namespace QUBO {
    struct LinearTerm {
        int Variable;
        float Coeff;
    };

    struct QuadraticTerm {
        short Variable1;
        short Variable2;
        float Coeff;
    };

    struct Solution {
        size_t variables = 0;
        double objective = 0;

        inline char operator[](short var) {
            return (variables & (1ull << var)) != 0 ? 1 : 0;
        }
    };

    struct LinearTermArray {
        LinearTerm* buffer_ = nullptr;
        size_t size_ = 0;
    };

    struct QuadraticTermArray {
        QuadraticTerm* buffer_ = nullptr;
        size_t size_ = 0;
    };

    // Just a collection of pointers and sizes, someone else owns the buffers.
    struct Model {
        LinearTerm* linear_terms = nullptr;
        QuadraticTerm* quadratic_terms = nullptr;
        size_t linear_term_count = 0;
        size_t quadratic_term_count = 0;
        short variable_count = 0;
    };
}