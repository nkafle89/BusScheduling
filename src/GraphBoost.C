#include "GraphBoost.h"

using namespace boost;

//typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
void BuildAndSolveGraph()
{
	enum{ A, B, C, D, E, N};

	const int num_vertices = N;

	const char* name = "ABCDE";

	typedef std::pair<int, int> Edge;

	Edge edge_array[]=
	{ Edge(A, B), Edge(A, D), Edge(C, A), Edge(D, C),
	  Edge(C, E), Edge(B, D), Edge(D, E) };

	const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);

	Graph g(num_vertices);

	for(int i=0; i< num_edges; ++i)
	{
		add_edge(edge_array[i].first, edge_array[i].second, g);
	}
}
