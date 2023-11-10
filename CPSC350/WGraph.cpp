#include "WGraph.h"
#include "Edge.h"
#include "PQueue.h"

WGraph::WGraph(){
  m_size = 0;
  m_adj = NULL;
}

WGraph::WGraph(unsigned int sz){
  m_size = sz;
  //allocate sz * sz adj matrix
  m_adj = new double*[sz];
  m_conn = new double*[sz];
  for(int i = 0; i < m_size; ++i){
    m_adj[i] = new double[sz];
    m_conn[i] = new double[sz];
  }
  //start with edges
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_adj[i][j] = std::numeric_limits<double>::max();
      m_conn[i][j] = std::numeric_limits<double>::max();
      // m_adj[i][j] = 2;
      // m_conn[i][j] = 1;
    }
  }
}

WGraph::~WGraph(){
  //release memory
}

void WGraph::addEdge(VertexID i, VertexID j, double w){
  if(i < m_size && j < m_size){
    m_adj[i][j] = w;
    m_adj[j][i] = w;
  }
}

void WGraph::removeEdge(VertexID i, VertexID j){
  if(i < m_size && j < m_size){
    m_adj[i][j] = std::numeric_limits<double>::max();
    m_adj[j][i] = std::numeric_limits<double>::max();
  }
}

bool WGraph::areAdjacent(VertexID i, VertexID j){
  return (m_adj[i][j] < std::numeric_limits<double>::max());
}

void WGraph::computeMST() {
  PQueue<Edge> edges(true); // "true" meaning this this will be a minQueue
  WGraph tempMST(this->m_size);
  Edge tempEdge;
  Edge checkEdge;
  for(int i = 0; i < m_size; ++i) { // add all edges from inputGraph into a minQueue
    for(int j = 0; j < m_size; ++j) {
      if(m_adj[i][j] != 0.0 && m_adj[i][j] != std::numeric_limits<double>::max()) {
          tempEdge.row = i;
          tempEdge.column = j;
          tempEdge.weight= m_adj[i][j];
          edges.add(tempEdge);
          // tempEdge.column = i;
          // tempEdge.row = j;
          // edges.add(tempEdge);
          //
          // checkEdge.row = i;
          // checkEdge.column = j;
      }
      // cout << "CHECK EDGE: " << endl;
      // cout << "Row: " << checkEdge.row << endl;
      // cout << "Column: " << checkEdge.column << endl;
    }
  }

  while (!edges.isEmpty()) {
    Edge currEdge = edges.remove();// remove will remove MIN of edges
    int numLimitMaxCount = 0;
    bool done = false;
    for (int i = 0; i < m_size; ++i){ // for 1
      if (done == true){
        break;
      }
        for (int j = 0; j < m_size; ++j){ // for 2
          cout << "CURR COUNT: " << numLimitMaxCount<< "; " << currEdge.row << " -> " << currEdge.column << " with weight " << currEdge.weight << " i:j: " << i << ":" << j << endl;
          if(tempMST.m_adj[currEdge.row][j] != std::numeric_limits<double>::max()){ // check if edge doesn't exist
            cout << "Not Needed OR " << currEdge.row << " is already a source node... DISCARDING" << endl;
              done = true; // won't exist if 2D array still holds numeric_limits<double>::max value
              break;
          } else if (numLimitMaxCount == m_size) { // check if no edge added yet
            // cout << "COUNT: " << count << endl;
            cout << "No edge exists, ADDING EDGE" << endl;
            tempMST.addEdge(currEdge.row, currEdge.column, currEdge.weight);
              done = true;
              break;
            } else {
              cout << "Incremented count" << endl;
          numLimitMaxCount++;
        }
      } // end of for 2
    } // end of for 1
  }

    int sum = 0;
    for (int i = 0; i < m_size; i++) { // add edge weights (CUT IN HALF AT OUTOPUT, since weight exists on both sides of 0 diagonal)
      for (int j = 0; j < m_size; j++) {
        if (tempMST.m_adj[i][j] != std::numeric_limits<double>::max()) {
            sum += tempMST.m_adj[i][j];
        }
        else {
          tempMST.m_adj[i][j] = 0;
        }
      }
    }

    std::cout << "Adjacency Matrix: " << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < m_size; i++) {
      for (int j = 0; j < m_size; j++) {
        std::cout << tempMST.m_adj[i][j] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Cost: " << sum/2 << std::endl;
    std::cout << sum << " if you are counting every single weight in the graph :)" << std::endl;
    std::cout << std::endl;
/*
  - Cut sum in half to match weight on only one side of 0 diagonal
  - If don't divide by 2, gives weight of every edge in MST
*/

}

void WGraph::printMST() {
  int cost = 0;
  cout << "Adjacency matrix: " << endl;
  cout << endl;
  for (int i = 0; i < m_size; ++i) {
    for (int j = 0; j < m_size; ++j) {
      if (j == m_size - 1) {
        cout << m_adj[i][j] << endl;
      } else {
      cout << m_adj[i][j] << " - ";
      }
    }
    cout << endl;
  }

  cout << "---------" << endl;

  cout << "Connectivity matrix: " << endl;
  for (int i = 0; i < m_size; ++i) {
    for (int j = 0; j < m_size; ++j) {
      if (j == m_size - 1) {
        cout << m_conn[i][j] << endl;
      } else {
      cout << m_conn[i][j] << " - ";
      }
    }
    cout << endl;
  }

  cout << endl;
  cout << "Cost: " << cost << endl;
}
