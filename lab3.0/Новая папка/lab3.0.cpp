#include <iostream>;
#include <map>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


map<char, vector<char>> adjList;
map<char, int> State;
vector<char> TopNum;
vector<char> letters;
vector<string> words;
int CurTopNum;
int countWords;

enum typeState {
	unvisited, // 0 
	visited,   // 1
    processed, // 2
};

bool find(vector<char> array, char value) {
	return find(array.begin(), array.end(), value) != array.end();
}

void addEdge(char key, char value) {
	auto pointer = adjList.find(key);
	if (pointer != adjList.end()) {
		if (!find(adjList[key], value))
			adjList[key].push_back(value);
	}
	else {
		vector<char> values = { value };
		adjList.insert({ key, values });
	}
}

void comparisonLetters(string word1, string word2) {
	for (int i = 0, j = 0; i < word1.size() && j < word2.size(); i++, j++) {
		if (word1[i] != word2[j]) {
			addEdge(word1[i], word2[j]);
		}
		if (!find(letters, word1[i]))
			letters.push_back(word1[i]);
		if (!find(letters, word2[j]))
			letters.push_back(word2[j]);
	}
}

void readFromFile(const char* fileName) {
    ifstream input(fileName);
	string line;
	input >> countWords;

	if (input.is_open()) {
		getline(input, line); // почему-то дальше из файла считывает пустую строку
		for (int i = 0; i < countWords; i++) {
			getline(input, line);
			words.push_back(line);
		}
	}

	for (int i = 0; i < words.size() - 1; i++) {
		comparisonLetters(words[i], words[i + 1]);
	}
}

vector<char> getKeys(map<char, vector<char>> Map) {
	vector<char> result;
	for (map<char, vector<char>>::iterator iter = adjList.begin(); iter != adjList.end(); ++iter) {
		result.push_back(iter->first);
	}
	return result;
}

void printVector(vector<char> values) {
	for (char letter : values) {
		cout << letter;
	}
}

void DFS_TopSort_Visit(char vertice) {
	State[vertice] = visited;

	for (char letter : adjList[vertice]) {
		if (State[letter] == unvisited) {
			DFS_TopSort_Visit(letter);
		}
	}

	State[vertice] = processed;
	TopNum[CurTopNum - 1] = vertice;
	CurTopNum--;
}

void DFS_TopSort() {	
	for (char letter : letters) {
		State[letter] = unvisited;
	}

	char c;
	for (int i = 0; i < letters.size(); i++) {
		TopNum.push_back(c);
	}

	CurTopNum = letters.size();

	for (char letter : letters) {
		if (State[letter] == unvisited) {
			DFS_TopSort_Visit(letter);
		}
	}
}

void makeOutput(const char* fileName) {
	ofstream output;
	output.open(fileName);
	for (char letter : TopNum)
		output << letter;
}

int main(int argc, char* argv[]) {
	readFromFile(argv[1]);

	DFS_TopSort();

	makeOutput(argv[2]);
}
