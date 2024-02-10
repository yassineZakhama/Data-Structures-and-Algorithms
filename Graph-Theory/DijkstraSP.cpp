#include <assert.h>
#include "DijkstraSP.h"
#include <stack>
#include <iostream>

#define INF 2147483647

void DijkstraSP::relax(const EdgeWeightedDigraph& G, DirectedEdge e)
{
	int u = e.from();
	int v = e.to();
	
	if (d[v] > d[u] + e.weight())
	{
		d[v] = d[u] + e.weight();
		parent[v] = u;
		pq.push({ d[v], v });
	}

}


DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	start = s;

	int V = G.getV();

	d.resize(V, INF);
	d[s] = 0;

	parent.resize(V, INF);
	parent[s] = -1;

	pq.push({d[s],s});

	while (!pq.empty())
	{
		// get the next smallest distance and relax its neighbors
		pair p = pq.top(); // p == (d[v],v) 
		pq.pop();

		int h = p.first; // h == distance pushed
		if (h > d[p.second]) // if pushed distance greater than current distance -> already relaxed
			continue;
		
		// else relax the vertex
		for (const DirectedEdge& e : G[p.second])
			relax(G, e);
	}
}

bool DijkstraSP::hasPathTo(int v) const
{
	if(d[v] == INF)
		return false;

	return true;
}

std::vector<DirectedEdge> DijkstraSP::pathTo(int v)
{
	path_to.resize(0);

	std::stack<DirectedEdge> s;

	while (parent[v] != -1)
	{
		DirectedEdge e(parent[v], v, d[v] - d[parent[v]]); // e(from,either,weight)
		s.push(e);
		v = parent[v]; // go back
	}

	while (!s.empty())
	{
		DirectedEdge e = s.top();
		path_to.push_back(e);
		s.pop();
	}

	return path_to;
}

void DijkstraSP::log_path(int to) 
{
	std::vector<DirectedEdge> tmp = pathTo(to);
	std::cout << "Start: " << start << std::endl;

	std::cout << "Target: " << to << std::endl;

	std::cout << "Path:\t" << tmp[0].from() << " [" << tmp[0].weight() << "]";
	for (size_t i = 1; i < tmp.size(); ++i)
		std::cout << " -> " << tmp[i].from() << " [" << tmp[i].weight() << "]";
	std::cout << " -> " << to;
	std::cout << std::endl;

	std::cout << "Total cost: " << d[to] << std::endl;
}
