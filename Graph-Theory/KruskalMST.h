#pragma once
#include <vector>
#include <queue>
#include "EdgeWeightedGraph.h"

class KruskalMST
{
private:
	std::vector<Edge> mst;				// MST Edges
	std::vector<int> set;				// set list for finding cycles
	double mst_weight;					// total cost

	void unify(int, int); // unify 2 subsets
	int find_parent(int u); // finds head of a subset containing u
public:
	KruskalMST() :mst_weight{ 0 } {};
	KruskalMST(EdgeWeightedGraph G);

	std::vector<Edge> edges() const { return mst; } // returns the MST

	double weight() const { return mst_weight; } // total cost

	void log() const;
};

