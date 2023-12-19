#pragma once
#include "convert.h"
#include <stack>
#include <vector>
#include <utility>

using TVisited = std::vector<int>;

bool CheckVisited(TVisited& visited, int top)
{
    for(int i : visited)
        if(i == top)
            return true;
    return false;
}

void DFS(CMatrix& dataMatrix, int top = 0)
{
    std::stack<int> st;
    TVisited visited;
    st.push(top);
    visited.clear();
    while(!st.empty())
    {
        top = st.top();
        st.pop();
        for(int i = 0; i < dataMatrix.matrixData.size(); i++)
            if(dataMatrix.matrixData[top][i] > 0 && !CheckVisited(visited, i))
            {
                st.push(i);
                visited.push_back(top);
                std::cout << "Вершина: " << top + 1 << " Связаннные с ней вершины: "<< i + 1 << std::endl;
            }
    }
}

typedef struct {
    int mark;
    std::vector<int> tops;
} ComponentList;

using ComponentListArr = std::vector<ComponentList>;

void DFS(CMatrix& dataMatrix, int top, int connMark, ComponentListArr& listArr)
{
    std::stack<int> st;
    ComponentList list = {
            .mark = connMark,

    };
    TVisited visited;
    st.push(top);
    visited.clear();
    while(!st.empty())
    {
        top = st.top();
        st.pop();
        for(int i = 0; i < dataMatrix.matrixData.size(); i++)
            if(dataMatrix.matrixData[top][i] > 0 && !CheckVisited(visited, i))
            {
                st.push(i);
                visited.push_back(top);
                std::cout << "Вершина: " << top + 1 << " Связаннные с ней вершины: "<< i + 1 << std::endl;
            }
    }
}