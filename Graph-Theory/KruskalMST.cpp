#include "KruskalMST.h"
#include <algorithm>
#include <iostream>
// Creates a MST with Kruskal algorithm
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
	int V = G.getV();

	mst_weight = 0.0;

	set.resize(V, -1);

	std::vector<Edge> edges = G.edges();

	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
	
	for (size_t i = 0; i < edges.size(); ++i) // add all edges to pq
		pq.push(edges[i]);

	while (!pq.empty()) 
	{
		Edge min = pq.top();
		pq.pop();

		int either = min.either();
		int other = min.other(either);

		if (find_parent(either) != find_parent(other)) // not in the same subset -> doesn't form a cycle 
		{
			mst.push_back(min);
			mst_weight += min.weight();

			unify(find_parent(either), find_parent(other));
		}
	}
	// When MST size is V-1 -> graph connected; if less than V-1 -> not connected
}

// unify 2 subsets ( u : head subset 1, v : head subset2)
void KruskalMST::unify(int u, int v)
{
	if (set[u] < set[v]) {
		set[u] += set[v];
		set[v] = u;
	}
	else {
		set[v] += set[u];
		set[u] = v;
	}
}

// returns head of the subset containing vertex u
int KruskalMST::find_parent(int u)
{
	int x = u;
	int v = 0;

	while (set[x] > 0) {
		x = set[x];
	}

	while (u != x) {
		v = set[u];
		set[u] = x;
		u = v;
	}
	return x;
}

void KruskalMST::log() const
{
	std::cout << "Minimum Spanning Tree with Kruskal Algorithm:" << std::endl;
	std::cout << "Total cost: " << mst_weight << std::endl << std::endl;

	for (size_t i = 0; i < set.size(); ++i)
	{
		std::cout << i;

		for (const Edge& e : mst)
		{
			if (e.either() == i)
				std::cout << " -> " << e.other(i) << "[" << e.weight() << "]";
		}

		std::cout << std::endl;
	}

}