#include "WGraph.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

string input = argv[1];
ifstream inFile(input);

cout << "Original: " << endl << endl;

int numNodes;
inFile >> ws >> numNodes;
WGraph inputGraph(numNodes);
int count = 0;
for (int i = 0; i < numNodes; ++i) { // add edges and their respective weights
  for (int j = 0; j < numNodes; ++j) {
    string edgeWeight;
    inFile >> edgeWeight;
    // inputGraph.m_adj[i][j] = stod(edgeWeight);
    if (stod(edgeWeight) > 0 && stod(edgeWeight) != numeric_limits<double>::max()) {
      inputGraph.addEdge(count, i, stod(edgeWeight));
      count++;
      cout << stoi(edgeWeight) << " ";
    } else {
      inputGraph.addEdge(count, i, numeric_limits<double>::max());
      count++;
      cout << 0 << " ";
    }
    if (edgeWeight == "END") {
      inFile.close();
      break;
    }
  }
  cout << endl;
  count = 0;
}

cout << "- - - - - - -" << endl;

inputGraph.computeMST();
// if (inputGraph.areAdjacent(0, 4)) {
//   cout << "Adjacent" << endl;
// } else {
//   cout << "Not adjacent" << endl;
// }

  return 0;
}
