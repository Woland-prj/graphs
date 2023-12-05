#include <fstream>
#include <iostream>

void GetInitData(std::ifstream& inFile, int& edgeCount, int& topCount) {
    std::string initInf;
    try {
        bool closeFileException = false;
        if(!inFile.is_open()) {
            closeFileException = true;
            throw closeFileException;
        }
        std::getline(inFile, initInf);
        for(size_t i = 0; i<=initInf.length(); i++) {
            if (initInf[i] == ' ')
                continue;
            if (edgeCount == 0){
                edgeCount = initInf[i] - '0';
                continue;
            }
            if (topCount == 0) {
                topCount = initInf[i] - '0';
                continue;
            }
        }
        if (edgeCount == 0 || topCount == 0)
            throw initInf;
    }
    catch (const std::string& voidStr) {
        std::cout << "incorrect file header: " << voidStr << std::endl;
        exit(1);
    }
    catch (const bool& closeFileException) {
        std::cout << "This file is not exist or path is incorrect" << std::endl;
        exit(2);
    }
}

void ToAdjacencyMatrix(const std::string& fileName) {
    std::ifstream inFile(fileName);
    std::string str;
    int edgeCount = 0;
    int topCount = 0;

    GetInitData(inFile, edgeCount, topCount);

    while (std::getline(inFile, str)) {
        std::cout << str << std::endl;
    }
}