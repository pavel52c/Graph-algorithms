#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>


std::vector<std::string> graphVertices;
std::map<std::string, std::string> graphLs;
std::vector<std::vector<int>> graphMx;


void printLs(const char* filePath) {
    std::ofstream outFile;
    outFile.open(filePath);

    for (auto node : graphLs) {
        outFile << node.first << ": " << node.second << std::endl;
    }
}

void printMx(const char* filePath) {
    std::ofstream outFile;
    outFile.open(filePath);

    for (auto row : graphMx) {
        for (auto elem : row) {
            outFile << elem << ' ';
        }
        outFile << std::endl;
    }
}


void fillVertices(std::string text) {
    std::string token;
    std::istringstream tokenStream(text);
    while (std::getline(tokenStream, token, ' ')) {
        graphVertices.push_back(token);
    }
}

void fillLsGraph(std::string first, std::string second) {
    if (graphLs.find(first) != graphLs.end()) {
        if (graphLs[first].find(second) == -1)
            graphLs[first] += " " + second;
    }
    else {
        graphLs.insert(std::pair<std::string, std::string>(first, second));
    }
}

void fillMxGraph(std::string first, std::string second) {
    size_t fIndex = std::find(graphVertices.begin(), graphVertices.end(), first) - graphVertices.begin(),
                sIndex = std::find(graphVertices.begin(), graphVertices.end(), second) - graphVertices.begin();
    graphMx[fIndex][sIndex] = 1;
    graphMx[sIndex][fIndex] = 1;
}

void readFromFile(const char* filePath, char* outputText) {
    std::ifstream inputFile;
    inputFile.open(filePath);

    std::string first, second;
    std::getline(inputFile, first);
    fillVertices(first);
    graphMx.resize(graphVertices.size());
    for (int i = 0; i < graphVertices.size(); i++) {
        graphMx[i].resize(graphVertices.size(), 0);
    }

    do {
        inputFile >> first >> second;
        fillLsGraph(first.c_str(), second);
        fillLsGraph(second.c_str(), first);
        fillMxGraph(first, second);
    } while (!inputFile.eof());
}

int main(int argc, const char* argv[]) {
    char* inputText = nullptr;
    readFromFile(argv[1], inputText);

    printMx(argv[2]);
    printLs(argv[3]);
    std::cout << " ";
}
