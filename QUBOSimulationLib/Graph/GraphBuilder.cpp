#include "GraphBuilder.h"

#include <limits>

#include "Graph.h"

GraphBuilder::~GraphBuilder()
{}

Vertex GraphBuilder::AddVertex()
{
	if (vertices_.size() >= std::numeric_limits<int>::max()) {
		throw std::exception("GraphBuilder::AddVertex - too many vertices! Index must fit in an 'int'.");
	}

	Vertex v((int)vertices_.size());
	vertices_.push_back(v);
	return v;
}

Edge GraphBuilder::AddEdge(Vertex a, Vertex b)
{
	if (edges_.size() >= std::numeric_limits<int>::max()) {
		throw std::exception("GraphBuilder::AddEdge - too many edges! Index must fit in an 'int'.");
	}

	Edge e(a, b, (int)edges_.size());
	edges_.push_back(e);
	return e;
}

IGraph* GraphBuilder::Build()
{
	IGraph* result = new Graph(vertices_, edges_);
	vertices_.clear();
	edges_.clear();
	return result;
}