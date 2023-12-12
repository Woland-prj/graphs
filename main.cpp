#include "convert.h"

int main() {
    Matrix adjMatrix(0, std::vector<int>(0));
    EdgeList list(0);
    ToAdjacencyMatrix("/home/woland/cpp/graphs/edge_list.txt", adjMatrix);
    printMatrix(adjMatrix);
    ToEdgeList(adjMatrix, list);
    PrintEdgeList(list);
}

