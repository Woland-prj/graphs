#include "convert.h"
#include "bfs.h"

int main(int argc, char* argv[]) {
    if(argc < 2)
    {
        std::cout << "Need to enter filename of edge list" << std::endl;
        exit(1);
    }
    CEdgeList list(argv[1]);
    CMatrix matrix(list.listData);
    BFS(matrix, 0);
}
