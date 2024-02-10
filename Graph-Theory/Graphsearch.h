#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>
#include <queue>
#include <vector>

namespace Graphsearch 
{
	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& visited, std::vector<int>& parent, bool output = false)
	{
		if (!visited[v])
		{
			visited[v] = true;
			
			if(output)
				std::cout << v << " ";

			for (int i = 0; i < G[v].size(); ++i) // Explore all adjacents
			{
				int either = G[v][i].either();
				int other = G[v][i].other(G[v][i].either());

				if (either == v && !visited[other]) // either is current v, continue search with other
				{
					parent[other] = v;
					DFS_recursive(G, other, visited, parent, output);
				}
				else if (other == v && !visited[either]) // other is current v, continue search with either
				{
					parent[either] = v;
					DFS_recursive(G, either, visited, parent, output);
				}
			}
		}
	}

	// returns true if the graph is connected (Starter funktion for DFS_recursive)
	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& visited, std::vector<int>& parent, bool output = false) 
	{
		int V = G.getV();

		visited.resize(V);
		for (int i = 0; i < V; ++i) // Initialise visited with false
			visited[i] = false;

		parent.resize(V);
		for (int i = 0; i < V; ++i) // Initialise parents with -1 
			parent[i] = -1;

		DFS_recursive(G, v, visited, parent, output);
		if(output)
			std::cout << std::endl;

		for (bool i : visited)
			if (i == false)
				return false; // not connected
		
		return true; // connected
	}

	// returns true if the graph is connected
	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& visited, std::vector<int>& parent, bool output = false) 
	{
		int V = G.getV();

		visited.resize(V);
		for (int i = 0; i < V; ++i) // Initialise visited with false
			visited[i] = false;

		parent.resize(V);
		for (int i = 0; i < V; ++i) // Initialise parents with -1 
			parent[i] = -1;

		std::queue<int> q;
		q.push(v);

		while (!q.empty())
		{
			int v = q.front();
			q.pop();

			if (!visited[v])
			{
				if (output)
					std::cout << v << " ";
				visited[v] = true;

				for (const Edge& adjacent : G[v]) // push all adjacent
				{
					int either = adjacent.either();
					int other = adjacent.other(adjacent.either());

					if (either == v && !visited[other])
					{
						if (parent[other] == -1) // Doesn't have a parent -> set a parent
							parent[other] = v;

						q.push(other);
					}
					else if (other == v && !visited[either])
					{
						if (parent[either] == -1) // Doesn't have a parent -> set a parent
							parent[either] = v;
							
						q.push(either);
					}
				}
			}
		}
		if(output)
			std::cout << std::endl;

		for (bool i : visited)
			if (i == false)
				return false; // not connected

		return true; // connected
	}
}
