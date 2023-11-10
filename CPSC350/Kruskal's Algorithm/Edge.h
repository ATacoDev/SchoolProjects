#ifndef EDGE_H
#define EDGE_H

class Edge {
friend class WGraph; // allows use of WGraph methods/var that are private

    public:
      Edge();
      virtual ~Edge();
      bool operator<(const Edge &Edge); // compare edge weights

    private:
      int row;
      int column;
      double weight;
};
#endif

bool Edge::operator<(const Edge &Edge) { // compare edge weights
    if (weight < Edge.weight) {
        return true;
    }
    else {
        return false;
    }
}

Edge::Edge(){
    row = 0;
    column = 0;
    weight = 0.0;
}

Edge::~Edge(){

}
