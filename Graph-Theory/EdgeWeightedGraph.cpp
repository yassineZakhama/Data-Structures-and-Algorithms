#include "EdgeWeightedGraph.h"
#include <fstream>
#include <assert.h>
#include <iostream>

// Creates a graph with V vertices and with no edges
EdgeWeightedGraph::EdgeWeightedGraph(int V) 
	: V{ V } , E{ 0 } 
{
	adj.resize(V);
}

// creates a graph from a file
EdgeWeightedGraph::EdgeWeightedGraph(std::string filename)
{
	std::ifstream infile(filename);
	int tmp_e = 0;
	infile >> this->V >> tmp_e;

	this->E = 0;

	this->adj.resize(this->V, std::vector<Edge>());

	int v, w;
	double weight;
	while (infile >> v >> w >> weight)
	{
		this->add(Edge(v, w, weight));
	}

	assert(("Missing edges!", tmp_e == this->E));
}

// creates a graph with V vertices and edges from edges list E
EdgeWeightedGraph::EdgeWeightedGraph(int V, std::vector<Edge> E)
{
	this->V = V;
	this->adj.resize(V);

	for (Edge e : E)
	{
		this->add(e);
	}
}

// checks if the vertex v is a valid vertex 
bool EdgeWeightedGraph::validateVertex(int v) const
{
	return v >= 0 && v < this->V;
}

// logs an error when the vertex v is not valid
void EdgeWeightedGraph::validateVertexWithError(int v) const
{
	assert(("Vertex is out of bounds!", this->validateVertex(v)));
}

// getters
int EdgeWeightedGraph::getV() const { return this->V; }
int EdgeWeightedGraph::getE() const { return this->E; }
std::vector<std::vector<Edge>> EdgeWeightedGraph::getAdj() const { return this->adj; }

// Returns a vector withh all adjacent edges to v
std::vector<Edge> EdgeWeightedGraph::getAdj(int v) const
{
	std::vector<Edge> neighbors;
	for (auto const& n : adj[v]) {
		neighbors.push_back(n);
	}
	return neighbors;
}

// returns a vector with all edges in the graph
std::vector<Edge> EdgeWeightedGraph::edges() const
{
	std::vector<Edge> edgeList;
	for (int v = 0; v < this->V; v++)
	{
		int selfLoops = 0;
		for (Edge e : this->adj[v])
		{
			if (e.other(v) > v) {
				edgeList.push_back(e);
			}
			// add only one copy of each self loop (self loops will be consecutive)
			else if (e.other(v) == v) {
				if (selfLoops % 2 == 0) edgeList.push_back(e);
				selfLoops++;
			}
		}
	}
	return edgeList;
}

// returns a vector with connected vertices with v
const std::vector<Edge> EdgeWeightedGraph::operator[](int v) const
{
	this->validateVertexWithError(v);
	return this->adj[v];
}

void EdgeWeightedGraph::add(Edge e)
{
	this->validateVertexWithError(e.either());
	this->validateVertexWithError(e.other(e.either()));

	this->adj[e.either()].push_back(e);
	this->adj[e.other(e.either())].push_back(e);

	this->E++;
}

bool EdgeWeightedGraph::del_Edge(Edge e)
{
	int either = e.either();
	int other = e.other(e.either());

	// find and delete first edge if found
	std::vector<Edge>::iterator it = std::find(adj[either].begin(), adj[either].end(), e);
	if (it != adj[either].end()) // found
		adj[either].erase(it);
	else 
		return false; // not found

	// find and delete second edge if found
	it = std::find(adj[other].begin(), adj[other].end(), e);
	if (it != adj[other].end())
		adj[other].erase(it);
	else
		return false;

	// deleted both successfully
	--E;
	return true; 
}

void EdgeWeightedGraph::log() const
{
	for (int i = 0; i < adj.size(); ++i)
	{
		std::cout << i;

		for (size_t j = 0; j < adj[i].size(); ++j)
		{
			std::cout << " -> " << adj[i][j].other(i) << " [" << adj[i][j].weight() << "]";
		}
		std::cout << std::endl;
	}
}