#pragma once
#include <vector>
#include <queue>
#include <map>
#include "EdgeWeightedDigraph.h"
#include "PriorityQueue.h"


#define pair std::pair<int,int> // pair.first: distance, pair.second : vertex

class DijkstraSP
{
private:
	int start;

	std::vector<double> d;
	std::vector<int> parent;
	std::priority_queue<pair, std::vector<pair>, std::greater<pair>> pq;


	std::vector<DirectedEdge> path_to;

	void relax(const EdgeWeightedDigraph& G, DirectedEdge e);

public:
	DijkstraSP() : start{ 0 } {};
	DijkstraSP(EdgeWeightedDigraph G, int s);

	// distance from starting vertex to v
	double distTo(int v) const { return d[v]; }	

	// returns true if there is a path from the starting vertex to v
	bool hasPathTo(int v) const;				

	// returns path from starting vertex to v
	std::vector<DirectedEdge> pathTo(int v);	

	void log_path(int to);
};

