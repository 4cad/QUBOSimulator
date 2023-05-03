#pragma once

#include "IGraph.h"

/*
 * This graph object cannot have vertices or edges added/removed.
 * To add/remove edges a GraphBuilder must be used
 */
class Graph : public IGraph {
public:
	~Graph() override;
	Graph(std::vector<Vertex> vertices, std::vector<Edge> edges);

	const Vertex& GetVertex(int i) const override { return vertices_.at(i); }
	const Edge& GetEdge(int i) const override { return edges_.at(i); }

	int VertexCount() const override { return (int)vertices_.size(); }
	int EdgeCount() const override { return (int)edges_.size(); }

	VertexContainer Vertices() const override;
	EdgeContainer Edges() const override;

private:
	std::vector<Vertex> vertices_;
	std::vector<Edge> edges_;

	std::vector<std::pair<const Vertex*, const Edge*>> edges_by_vertex_;
	std::vector<int> vertex_start_idx_;
};