#pragma once
#include <string>
#include <vector>
#include <iomanip>

class Edge
{
private:
	int		_either;  
	int		_other;   
	double	_weight;  
public:
	Edge(int either, int other, double weight)
		: _either{ either }, _other{ other }, _weight{ weight } {}

	double weight() const { return _weight; } 
	int either() const { return _either; }    
	int other(int vertex) const {			  
		if (vertex == _either) return _other;
		else if (vertex == _other) return _either;
		else throw new std::invalid_argument("Illegal endpoint");
	}
};

inline bool operator==(const Edge& lhs, const Edge& rhs) { return lhs.weight() == rhs.weight(); }
inline bool operator!=(const Edge& lhs, const Edge& rhs) { return !operator==(lhs, rhs); }
inline bool operator< (const Edge& lhs, const Edge& rhs) { return lhs.weight() < rhs.weight(); }
inline bool operator> (const Edge& lhs, const Edge& rhs) { return  operator< (rhs, lhs); }
inline bool operator<=(const Edge& lhs, const Edge& rhs) { return !operator> (lhs, rhs); }
inline bool operator>=(const Edge& lhs, const Edge& rhs) { return !operator< (lhs, rhs); }


class EdgeWeightedGraph
{
private:
	int V;  
	int E;  
	std::vector<std::vector<Edge>> adj; 
	bool validateVertex(int v) const;
	void validateVertexWithError(int v) const;

public:
	EdgeWeightedGraph(int V);			     
	EdgeWeightedGraph(std::string filename); 
	EdgeWeightedGraph(int V, std::vector<Edge> E);

	void add(Edge e);  						 
	bool del_Edge(Edge e);

	int getV() const;            			 
	int getE() const;            			 

	std::vector<Edge> getAdj(int v) const;	 
	std::vector<std::vector<Edge>> getAdj() const;

	std::vector<Edge> edges() const;	 	 

	const std::vector<Edge> operator[](int v) const;

	void log() const;
};

