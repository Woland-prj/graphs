#pragma once
#include "convert.h"
#include <queue>

using TVisited = std::vector<int>;

bool CheckVisited(TVisited& visited, int top)
{
    for(int i : visited)
        if(i == top)
            return true;
    return false;
}

void BFS(CMatrix& dataMatrix, int top = 0)
{
    std::queue<int> qe;
    TVisited visited;
    qe.push(top);
    visited.clear();
    while(!qe.empty())
    {
         top = qe.front();
         qe.pop();
         for(int i = 0; i < dataMatrix.matrixData.size(); i++)
             if(dataMatrix.matrixData[top][i] > 0 && !CheckVisited(visited, i))
             {
                 qe.push(i);
                 std::cout << "Вершина: " << top + 1 << " Связаннные с ней вершины: "<< i + 1 << std::endl;
             }
        visited.push_back(top);
    }
}