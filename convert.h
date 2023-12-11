#include <fstream>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

size_t Split(const std::string &txt, std::vector<int> &nums, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    nums.clear();

    while(pos != std::string::npos)
    {
        const std::string text = txt.substr(initialPos, pos - initialPos);
        if(!text.empty() || text != "0") nums.push_back(stoi(text));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    const std::string text = txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1);
    if(!text.empty() || text != "0") nums.push_back(stoi(text));

    return nums.size();
}

void GetInitData(std::ifstream& inFile, int& edgeCount, int& topCount)
{
    std::string initDataStr;
    std::vector<int> initDataArr;
    initDataArr.clear();
    try {
        bool closeFileException = false;
        if(!inFile.is_open()) {
            closeFileException = true;
            throw closeFileException;
        }
        std::getline(inFile, initDataStr);
        size_t data_len = Split(initDataStr, initDataArr, ' ');
        if (data_len != 2 || initDataArr[0] == 0 || initDataArr[1] == 0)
            throw initDataStr;
        edgeCount = initDataArr[0];
        topCount = initDataArr[1];
    }
    catch (const std::string& initInf) {
        std::cout << "Incorrect file header: " << initInf << std::endl;
        exit(1);
    }
    catch (const bool& closeFileException) {
        std::cout << "This file is not exist or path is incorrect" << std::endl;
        exit(2);
    }
}

void InitializeMatrix(Matrix& matrix, int topCount)
{
    using matrixRow = std::vector<int>;
    matrixRow row;
    const int initialValue = 0;
    std::string str;
    matrix.clear();
    for(size_t i=0; i < topCount; i++)
    {
        row.clear();
        for(size_t j=0; j < topCount; j++)
            row.push_back(initialValue);
        matrix.push_back(row);
    }
}

void printMatrix(Matrix& matrix)
{
    std::cout << matrix.size() << std::endl;
    for(auto & i : matrix)
    {
        for(int j : i)
            std::cout << j << ' ';
        std::cout << std::endl;
    }
}

void ToAdjacencyMatrix(const std::string& fileName)
{
    Matrix adjMatrix(0, std::vector<int>(0));
    std::vector<int> dataNums;

    std::ifstream inFile(fileName);
    std::string str;
    int edgeCount = 0;
    int topCount = 0;
    int realEdgeCount = 0;

    GetInitData(inFile, edgeCount, topCount);
    InitializeMatrix(adjMatrix, topCount);

    while (std::getline(inFile, str) && realEdgeCount < edgeCount - 1)
    {
        try
        {
            realEdgeCount ++;
            std::cout << str << std::endl;
            const size_t nums_size = Split(str, dataNums, ' ');
            if (nums_size != 3 )
                throw str;
            const int top1 = dataNums[0];
            const int top2 = dataNums[1];
            const int weight = dataNums[2];
            if(top1 == top2 || top1 <= 0 || top2 <= 0 || weight <= 0 || top1 > topCount || top2 > topCount)
                throw str;
            adjMatrix[dataNums[0] - 1][dataNums[1] - 1] = dataNums[2];
            adjMatrix[dataNums[1] - 1][dataNums[0] - 1] = dataNums[2];
        }
        catch (const std::string& str)
        {
            std::cout << "Incorrect edge definition: " << str << std::endl;
            exit(3);
        }
    }
    if (realEdgeCount < edgeCount)
    {
        std::cout << "The number of edges indicated in the header - " << edgeCount << " does not match the number of edges read - " << realEdgeCount << str << std::endl;
        exit(4);
    }
    printMatrix(adjMatrix);
}