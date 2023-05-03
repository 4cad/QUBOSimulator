#pragma once
class IGraph;

template<typename T>
class CustomIterator {
public:
	CustomIterator(const IGraph& graph, int index)
		: graph_(graph)
		, index_(index)
	{}

	const T& operator*() const
	{
		return Get(graph_, index_);
	}

	void operator++()
	{
		index_ += 1;
	}

	bool operator!=(const CustomIterator& other) const
	{
		return index_ != other.index_;
	}

	virtual const T& Get(const IGraph& graph, int index) const = 0;
private:
	const IGraph& graph_;
	int index_ = 0;
};

template<typename T, typename Iterator>
class CustomContainer {
public:
	CustomContainer(const IGraph& graph)
		: graph_(graph)
	{}

	const Iterator begin() const
	{
		return Iterator(graph_, 0);
	}

	const Iterator end() const
	{
		return Iterator(graph_, GetCount(graph_));
	}

	virtual int GetCount(const IGraph& graph) const = 0;

private:
	const IGraph& graph_;
};