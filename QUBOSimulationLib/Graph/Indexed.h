#pragma once

template<typename T>
class Indexed {
public:
	Indexed()
	{}

	Indexed(int index)
		: index_(index)
	{}

	int GetIndex() const { return index_; }

	bool operator<(const T& other) const { return index_ < other.index_; }
	bool operator>(const T& other) const { return index_ > other.index_; }
	bool operator==(const T& other) const { return index_ == other.index_; }

protected:
	int index_ = -1;
};