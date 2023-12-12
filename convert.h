#include <fstream>
#include <iostream>
#include <vector>

size_t Split(const std::string &txt, std::vector<int> &nums, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    nums.clear();

    while(pos != std::string::npos)
    {
        const std::string text = txt.substr(initialPos, pos - initialPos);
        if(!text.empty() && text != "0") nums.push_back(stoi(text));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    const std::string text = txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1);
    if(!text.empty() && text != "0") nums.push_back(stoi(text));

    return nums.size();
}

class CEdgeList
{
public:
    typedef struct {
        size_t topCount;
        size_t edgeCount;
        std::vector<std::string> edges;
    } EdgeList;
private:
    static void GetInitData(std::ifstream& inFile, size_t& topCount, size_t& edgeCount)
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
    static void ReadEdgeList(const std::string& fileName, EdgeList& edgeList)
    {
        std::ifstream inFile(fileName);
        std::string str;

        GetInitData(inFile, edgeList.topCount, edgeList.edgeCount);
        edgeList.edges.clear();

        while (std::getline(inFile, str))
            edgeList.edges.push_back(str);
    }
public:
    EdgeList listData = {
            .topCount =  0,
            .edgeCount = 0,
            .edges =  std::vector<std::string>(0),
    };

    explicit CEdgeList(const std::string& fileName)
    {
        ReadEdgeList(fileName, listData);
    }
    CEdgeList() = default;

    void PrintEdgeList()
    {
        std::cout << listData.edgeCount << ' ' << listData.topCount << std::endl;
        for(const auto & i : listData.edges)
            std::cout << i << std::endl;
    }
};

class CMatrix
{
public:
    using Matrix = std::vector<std::vector<int>>;
private:
    static void InitializeMatrix(CMatrix::Matrix& matrix, size_t topCount)
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

    static size_t ReadEdges(CEdgeList::EdgeList& edgeList, Matrix& adjMatrix)
    {
        size_t realEdgeCount = 0;
        std::vector<int> dataNums;
        for(const auto & edge : edgeList.edges)
            try
            {
                if (realEdgeCount > edgeList.edgeCount)
                    break;
                const size_t nums_size = Split(edge, dataNums, ' ');
                if (nums_size == 0 )
                    continue;
                realEdgeCount ++;
                if (nums_size != 3 )
                    throw edge;
                const int top1 = dataNums[0];
                const int top2 = dataNums[1];
                const int weight = dataNums[2];
                if(top1 == top2 || top1 <= 0 || top2 <= 0 || weight <= 0 || top1 > edgeList.topCount || top2 > edgeList.topCount)
                    throw edge;
                adjMatrix[dataNums[0] - 1][dataNums[1] - 1] = dataNums[2];
                adjMatrix[dataNums[1] - 1][dataNums[0] - 1] = dataNums[2];
            }
            catch (const std::string& edge)
            {
                std::cout << "Incorrect edge definition: " << edge << std::endl;
                exit(3);
            }
        return realEdgeCount;
    }

    static void ToAdjacencyMatrix(CEdgeList::EdgeList& edgeList, Matrix& adjMatrix)
    {
        InitializeMatrix(adjMatrix, edgeList.topCount);
        size_t realEdgeCount = ReadEdges(edgeList, adjMatrix);

        if (realEdgeCount < edgeList.edgeCount)
        {
            std::cout << "The number of edges indicated in the header - " << edgeList.edgeCount << " does not match the number of edges read - " << realEdgeCount << std::endl;
            exit(4);
        }
    }

public:
    Matrix matrixData = std::vector<std::vector<int>>(0, std::vector<int>(0));
    explicit CMatrix(CEdgeList::EdgeList& list)
    {
        ToAdjacencyMatrix(list, matrixData);
    }

    void PrintMatrix() const
    {
        std::cout << matrixData.size() << std::endl;
        for(auto & i : matrixData)
        {
            for(int j : i)
                std::cout << j << ' ';
            std::cout << std::endl;
        }
    }

    void ToEdgeList(CEdgeList& list)
    {
        list.listData.edges.clear();
        list.listData.topCount = matrixData.size();
        for(size_t i = 0; i < matrixData.size(); i++)
            for(size_t j = 0; j < i; j++)
                if(matrixData[i][j] != 0)
                    list.listData.edges.emplace_back(std::to_string(i + 1) + ' ' + std::to_string(j + 1) +  ' ' + std::to_string(matrixData[i][j]));
        list.listData.edgeCount = list.listData.edges.size();
    }
};