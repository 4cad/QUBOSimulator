#include "Graph.h"

Edge::Edge(const Vertex& a, const Vertex& b, int index)
	: Indexed(index)
	, lower_(a < b? a : b)
	, upper_(a < b? b : a)
{}


Graph::Graph(std::vector<Vertex> vertices, std::vector<Edge> edges)
	: vertices_(vertices)
	, edges_(edges)
{
	if (vertices_.size() >= std::numeric_limits<int>::max()) {
		throw std::exception("Graph::Graph - too many vertices! Index must fit in an 'int'.");
	}

	if (edges_.size() >= std::numeric_limits<int>::max()) {
		throw std::exception("Graph::Graph - too many edges! Index must fit in an 'int'.");
	}

	edges_by_vertex_.reserve(edges_.size() * 2);
	for (const Edge &e : edges)
	{
		edges_by_vertex_.push_back(std::pair<const Vertex*, const Edge*>(&e.GetLowerVertex(), &e));
		edges_by_vertex_.push_back(std::pair<const Vertex*, const Edge*>(&e.GetUpperVertex(), &e));
	}

	std::sort(edges_by_vertex_.begin(), edges_by_vertex_.end()); 

	vertex_start_idx_.resize(vertices_.size());

	Vertex* last_vertex = nullptr;
	for (int i = 0; i < edges_by_vertex_.size(); i++) {
		auto entry = edges_by_vertex_[i];
		Vertex* v = &vertices_[entry.first->GetIndex()];
		v->SetEdgeOffset(i);
	}
}

Graph::~Graph()
{}

VertexContainer Graph::Vertices() const {
	return VertexContainer(*this);
}

EdgeContainer Graph::Edges() const {
	return EdgeContainer(*this);
}

int VertexContainer::GetCount(const IGraph& graph) const {
	return graph.VertexCount();
}

const Vertex& VertexIterator::Get(const IGraph& graph, int i) const {
	return graph.GetVertex(i);
}

int EdgeContainer::GetCount(const IGraph& graph)  const {
	return graph.EdgeCount();
}

const Edge& EdgeIterator::Get(const IGraph& graph, int i) const {
	return graph.GetEdge(i);
}