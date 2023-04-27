#pragma once

#include <list>
#include <memory>
#include <stdarg.h>

#include "Model.h"
#include "ModelBuilder.h"

namespace QUBO {

	struct TestCase {
		TestCase() {
			builder.reset(new ModelBuilder());
		}

		std::shared_ptr<ModelBuilder> builder;
		double expected_objective = 0;
		size_t expected_solution = 0;
	};

	std::list<TestCase> GetAllTests(); 
}