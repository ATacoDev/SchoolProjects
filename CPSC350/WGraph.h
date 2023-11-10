#ifndef WGraph_H
#define WGraph_H

#include <cstdlib>
#include <iostream>
#include <limits>

//a weighted, undirected WGraph implemented with adjacency matrix
//fixed size

using namespace std;
typedef unsigned int VertexID;

class WGraph{
public:
  WGraph();
  WGraph(unsigned int sz);
  ~WGraph();
  void addEdge(VertexID i, VertexID j, double w);
  void removeEdge(VertexID i, VertexID j);
  bool areAdjacent(VertexID i, VertexID j);

  void computeMST();
  void printMST();
  double** m_adj; // adjacency matrix

private:

  double** m_conn; // connectivity matrix
  unsigned int m_size; //nodes in WGraph (fixed)

};

#endif
