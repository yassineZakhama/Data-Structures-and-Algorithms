#pragma once
#include <vector>
#include <string>

class DirectedEdge
{
private:
	int _from;		
	int _to;		
	double _weight;	
public:
	DirectedEdge() : _from{ 0 }, _to{ 0 }, _weight{ 0 } {}

	DirectedEdge(int from, int to, double weight)
		: _weight{ weight }, _from{ from }, _to{ to } {}

	double weight() const { return _weight; }
	int from() const { return _from; }
	int to() const { return _to; }
};

inline bool operator==(const DirectedEdge& lhs, const DirectedEdge& rhs) { return lhs.weight() == rhs.weight(); }
inline bool operator!=(const DirectedEdge& lhs, const DirectedEdge& rhs) { return !operator==(lhs, rhs); }
inline bool operator< (const DirectedEdge& lhs, const DirectedEdge& rhs) { return lhs.weight() < rhs.weight(); }
inline bool operator> (const DirectedEdge& lhs, const DirectedEdge& rhs) { return  operator< (rhs, lhs); }
inline bool operator<=(const DirectedEdge& lhs, const DirectedEdge& rhs) { return !operator> (lhs, rhs); }
inline bool operator>=(const DirectedEdge& lhs, const DirectedEdge& rhs) { return !operator< (lhs, rhs); }

class EdgeWeightedDigraph {
private:
	int V;													
	int E;													
	std::vector<std::vector<DirectedEdge>> adj;				
	bool validateVertex(int v) const;
	void validateVertexWithError(int v) const;
public:
	EdgeWeightedDigraph(int V);								// Empty Digraph with V vertices
	EdgeWeightedDigraph(std::string filename);				// Read graph from file
	void add(DirectedEdge e);								
	int getV() const;										
	int getE() const;										
	std::vector<std::vector<DirectedEdge>> getAdj() const;	
	std::vector<DirectedEdge> getAdj(int v) const;			
	std::vector<DirectedEdge> edges() const;				
	const std::vector<DirectedEdge> operator[](int v) const;
	bool del_Edge(DirectedEdge e);						
};

