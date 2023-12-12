#include "convert.h"

int main(int argc, char* argv[]) {
    if(argc < 2)
    {
        std::cout << "Need to enter filename of edge list" << std::endl;
        exit(1);
    }
    CEdgeList list(argv[1]);
    CEdgeList outputList;
    CMatrix matrix(list.listData);
    std::cout << "Adjacency matrix:" << std::endl;
    matrix.PrintMatrix();
    matrix.ToEdgeList(outputList);
    std::cout << std::endl;
    std::cout << "New edge list:" << std::endl;
    outputList.PrintEdgeList();
}
