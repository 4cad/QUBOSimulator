#pragma once

#include <memory>

#include "IGraph.h"

class GraphBuilder : public IGraphBuilder {
public:
	~GraphBuilder() override;

	Vertex AddVertex() override;
	Edge AddEdge(Vertex a, Vertex b) override;

	IGraph* Build() override;
private:
	std::vector<Vertex> vertices_;
	std::vector<Edge> edges_;
};