#include <fstream>

void ToAdjacencyMatrix(const std::string& fileName) {
    std::ifstream inFile(fileName);
    std::string str;

    try {
        std::getline(inFile, str);
        throw str;
    }
    catch (std::string voidStr) {
//        std::cout <<
    }
    std::string initInf = str;

    while (std::getline(inFile, str)) {

    }
}