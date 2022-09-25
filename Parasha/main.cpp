#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


vector<string> graphVertices;
map<string, string> graphLs;
vector<vector<int>> graphMx;


void printLs(const char* filePath) {
    ofstream outFile;
    outFile.open(filePath);

    for (auto node : graphLs) {
        outFile << node.first << ": " << node.second << endl;
    }
}

void printMx(const char* filePath) {
    ofstream outFile;
    outFile.open(filePath);

    for (auto row : graphMx) {
        for (auto elem : row) {
            outFile << elem << ' ';
        }
        outFile << endl;
    }
}


void fillVertices(string text = "") {
    string token;
    istringstream tokenStream(text);
    while (getline(tokenStream, token, ' ')) {
        graphVertices.push_back(token);
    }
}

void fillLsGraph(string first, string second) {
    if (graphLs.find(first) != graphLs.end()) {
        if (graphLs[first].find(second) == -1)
            graphLs[first] += " " + second;
    }
    else {
        graphLs.insert(pair<string, string>(first, second));
    }
}

void fillMxGraph(string first, string second) {
    size_t fIndex = find(graphVertices.begin(), graphVertices.end(), first) - graphVertices.begin(),
           sIndex = find(graphVertices.begin(), graphVertices.end(), second) - graphVertices.begin();
    graphMx[fIndex][sIndex] = 1;
    graphMx[sIndex][fIndex] = 1;
}

void readFromFile(const char* filePath, char* outputText) {
    ifstream inputFile;
    inputFile.open(filePath);

    string first, second;
    getline(inputFile, first);
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
    cout << " ";
}
