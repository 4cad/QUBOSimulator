#pragma once
#include <algorithm>
#include <vector>

#include "Indexed.h"

#include "ForEachAdapter.h"

class Vertex : public Indexed<Vertex> {
public:
	Vertex()
	{}

	explicit Vertex(int index)
		: Indexed(index)
	{}

	void SetEdgeOffset(int edge_buffer_offset) {
		edge_buffer_offset_ = edge_buffer_offset;
	}

	int GetEdgeOffset() const {
		return edge_buffer_offset_;
	}
private:
	int edge_buffer_offset_ = -1;
};

class Edge : public Indexed<Edge> {
public:
	Edge(const Vertex &a, const Vertex &b, int index);

	const Vertex& GetLowerVertex() const { return lower_; }
	const Vertex& GetUpperVertex() const { return upper_; }

private:
	const Vertex& lower_;
	const Vertex& upper_;
};

/* These classes are to enable iterating of vertices and edges in for-each loops */
struct VertexIterator : public CustomIterator<Vertex> {
	VertexIterator(const IGraph& graph, int i)
		: CustomIterator(graph, i)
	{}

	const Vertex& Get(const IGraph& graph, int i) const override;
};

struct VertexContainer : public CustomContainer<Vertex, VertexIterator> {
	VertexContainer(const IGraph& graph)
		: CustomContainer(graph)

	{}

	int GetCount(const IGraph& graph) const override;
};

struct EdgeIterator : public CustomIterator<Edge> {

	EdgeIterator(const IGraph& graph, int i)
		: CustomIterator(graph, i)
	{}

	const Edge& Get(const IGraph& graph, int i) const override;
};

struct EdgeContainer : public CustomContainer<Edge, EdgeIterator> {
	EdgeContainer(const IGraph& graph)
		: CustomContainer(graph)

	{}

	int GetCount(const IGraph& graph) const override;
};

/*
 * The IGraph/IGraphBuilder interfaces were needed to work around linking issues, and will come in handy if
 * we refactor the GPU logic into an optional .DLL which is a decent way to provide support for non-GPU systems.
 */
class IGraph {
public:
	virtual ~IGraph() {}

	virtual const Vertex& GetVertex(int i) const = 0;
	virtual const Edge& GetEdge(int i) const = 0;

	virtual int VertexCount() const = 0;
	virtual int EdgeCount() const = 0;

	virtual VertexContainer Vertices() const = 0;
	virtual EdgeContainer Edges() const = 0;
};

class IGraphBuilder {
public:
	virtual ~IGraphBuilder() {};
	virtual Vertex AddVertex() = 0;
	virtual Edge AddEdge(Vertex a, Vertex b) = 0;

	virtual IGraph* Build() = 0;
};
