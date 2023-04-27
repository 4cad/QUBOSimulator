#pragma once
#include "Model.h"

namespace QUBO {
	class CPUBruteForceSolver {
	public:
		Solution Solve(Model& model);

	private:
		Solution Evaluate(const Model& model, size_t variables);
	};
}