#include <assert.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include "EdgeWeightedDigraph.h"

// returns true if v is a valid vertex in the graph
bool EdgeWeightedDigraph::validateVertex(int v) const
{
	return v >= 0 && v < this->V;
}

// logs an error when v is an invalid vertex in the graph
void EdgeWeightedDigraph::validateVertexWithError(int v) const
{
	assert(("Vertex is out of bounds!", this->validateVertex(v)));
}

// creates a graph with V vertices
EdgeWeightedDigraph::EdgeWeightedDigraph(int V)
	: V{ V }, E{ 0 }
{
	adj.resize(V);
}

// creates an edge weighted directed graph from a file
EdgeWeightedDigraph::EdgeWeightedDigraph(std::string filename)
{
	std::ifstream infile(filename);
	int tmp_e = 0;
	infile >> this->V >> tmp_e;

	this->E = 0;

	this->adj.resize(this->V, std::vector<DirectedEdge>());

	int v, w;
	double weight;
	while (infile >> v >> w >> weight)
	{
		this->add(DirectedEdge(v, w, weight));
	}

	assert(("Missing edges!", tmp_e == this->E));
}

// getters
int EdgeWeightedDigraph::getV() const { return this->V; }
int EdgeWeightedDigraph::getE() const { return this->E; }
std::vector<std::vector<DirectedEdge>> EdgeWeightedDigraph::getAdj() const { return this->adj; } // adjacency list

// returns adjacents of a vertex v
std::vector<DirectedEdge> EdgeWeightedDigraph::getAdj(int v) const
{
	std::vector<DirectedEdge> neighbors;
	for (auto const& n : adj[v]) {
		neighbors.push_back(n);
	}
	return neighbors;
}

// returns all edges in the graph
std::vector<DirectedEdge> EdgeWeightedDigraph::edges() const
{
	std::vector<DirectedEdge> list;
	for (int v = 0; v < this->V; v++)
	{
		for (DirectedEdge e : this->adj[v])
		{
			list.push_back(e);
		}
	}
	return list;
}

// add the edge e to the graph
void EdgeWeightedDigraph::add(DirectedEdge e)
{
	this->validateVertexWithError(e.from());
	this->validateVertexWithError(e.to());

	this->adj[e.from()].push_back(e);

	this->E++;
}
bool EdgeWeightedDigraph::del_Edge(DirectedEdge e)
{
	int v = e.from();

	std::vector<DirectedEdge>::iterator it = std::find(adj[v].begin(), adj[v].end(), e);

	if (it != adj[v].end()) // iterator not at the end -> found -> delete edge
		adj[v].erase(it);
	else
		return false; // iterator at the end -> not found

	--E;
	return true;
}

// returns edge list of a vertex "from"
const std::vector<DirectedEdge> EdgeWeightedDigraph::operator[](int from) const
{
	return this->adj[from];
}



