#include "PrimMST.h"
#include <vector>
#include <iostream>

// creates a MST with prim's algorithm starting from vertex s
PrimMST::PrimMST(EdgeWeightedGraph G, int s)
{
	mst_weight = 0.0;

	int V = G.getV();

	visited.resize(V);
	for (int i = 0; i < V; ++i) // Initialise visited with false
		visited[i] = false;

	visit(G, s);

	while (!pq.empty())
	{
		Edge minimum_cost_edge = pq.top();
		pq.pop();

		int either = minimum_cost_edge.either();
		int other = minimum_cost_edge.other(either);

		if (visited[either] && visited[other]) // if both are already visited -> do nothing (cycle detection)
			continue;

		mst.push_back(minimum_cost_edge); // add edge to mst
		mst_weight += minimum_cost_edge.weight(); // add cost


		if (!visited[either])
			visit(G, either);
		else if (!visited[other])
			visit(G, other);
	}
}

void PrimMST::visit(EdgeWeightedGraph G, int v)
{
	visited[v] = true;

	// push all not visited neighbors to the priority queue
	for (const Edge& temp_edge : G[v])
	{
		if (!visited[temp_edge.other(v)])
			pq.push(temp_edge);
	}
}

void PrimMST::log() const
{
	std::cout << "Minimum Spanning Tree with Kruskal Algorithm:" << std::endl;
	std::cout << "Total cost: " << mst_weight << std::endl << std::endl;

	for (size_t i = 0; i < visited.size(); ++i)
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