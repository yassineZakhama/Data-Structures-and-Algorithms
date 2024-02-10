#pragma once
#include <vector>
#include <queue>
#include "EdgeWeightedGraph.h"

class PrimMST
{
private:
	std::vector<bool> visited;	
	std::vector<Edge> mst;		
	double mst_weight;
	// Queue with priority to the edge with the smallest weight
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

	void visit(EdgeWeightedGraph G, int v);
	
public:
	PrimMST() : mst_weight{ 0.0 } {}
	PrimMST(EdgeWeightedGraph G, int s);
	
	std::vector<Edge> edges() const { return mst; };
	double weight() const { return mst_weight; }

	void log() const;
};

