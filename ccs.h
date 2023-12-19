#pragma once
#include "dfs.h"
#include "convert.h"

bool Visited(ComponentListArr& listArr, int top)
{
    for(auto & i : listArr)
        for(int j : i.tops)
            if(j == top)
                return true;
    return false;
}

void CCS(CMatrix& dataMatrix, ComponentListArr& listArr, int top)
{
    int mark = 0;
    for(int i = 0; i < dataMatrix.matrixData.size(); i++)
        if(!Visited(listArr, i))
            DFS(dataMatrix, i, ++mark, listArr);
}

void PrintCCSData(ComponentListArr& listArr)
{
    for(auto & i : listArr)
    {
        std::cout << i.mark << ": ";
        for(int j : i.tops)
            std::cout << j + 1 << ' ';
        std::cout << std::endl;
    }
}