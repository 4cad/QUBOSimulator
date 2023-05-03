#include "ModelBuilder.h"

#include "CudaUtils.h"

namespace QUBO {
    template<typename T>
    T* CopyToUnifiedMemory(std::vector<T>& buf) {
        T* result = nullptr;

        size_t bytes = sizeof(T) * buf.size();
        THROW_IF_ERROR(cudaMallocManaged((void**)&result, bytes));
        THROW_IF_ERROR(cudaMemcpy((void*)result, (void*)buf.data(), bytes, cudaMemcpyHostToHost));
        return result;
    }

    float& ModelBuilder::Q(Variable a, Variable b) {
        UpdateVariableCount(a.index);
        UpdateVariableCount(b.index);
        short i = a.index;
        short j = b.index;
        if (i == j) {
            throw std::exception("ModelBuilder::Q - quadratic terms require i != j");
        }
        if (j < i) {
            std::swap(i, j);
        }

        std::pair<short, short> key(i, j);
        return quadratic_terms_[key];
    }

    float& ModelBuilder::L(Variable a) {
        UpdateVariableCount(a.index);
        return linear_terms_[a.index];
    }

    Model* ModelBuilder::Build() {
        if (model_) {
            return model_;
        }

        std::vector<LinearTerm> linear_terms_flat;
        for (auto iter : linear_terms_) {
            short var = iter.first;
            float coeff = iter.second;
            linear_terms_flat.emplace_back(LinearTerm{ var, coeff });
        }

        std::vector<QuadraticTerm> quadratic_terms_flat;
        for (auto iter : quadratic_terms_) {
            short var1 = iter.first.first;
            short var2 = iter.first.second;
            float coeff = iter.second;
            quadratic_terms_flat.emplace_back(QuadraticTerm{ var1, var2, coeff });
        }

        THROW_IF_ERROR(cudaMallocManaged((void**)&model_, sizeof(Model)));

        model_->linear_term_count = linear_terms_.size();
        model_->linear_terms = CopyToUnifiedMemory(linear_terms_flat);

        model_->quadratic_term_count = quadratic_terms_.size();
        model_->quadratic_terms = CopyToUnifiedMemory(quadratic_terms_flat);

        model_->variable_count = variable_count_;
        return model_;
    }


    void ModelBuilder::UpdateVariableCount(short var)
    { 
        variable_count_ = std::max<short>(var + 1, variable_count_); 
    }


    const QuadraticTermBuilder operator*(const Variable a, const Variable b)
    {
        return QuadraticTermBuilder(a, b, 1);
    }

    const LinearTermBuilder operator*(Variable var, double coeff)
    {
        return LinearTermBuilder(var, coeff);
    }

}