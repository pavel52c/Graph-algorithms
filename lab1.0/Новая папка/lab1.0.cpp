#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

vector<string> splitBySpace(const string str) {
	stringstream strStream(str);
	string vertice;
	vector<string> vertices;
	while (getline(strStream, vertice, ' ')) {
		vertices.push_back(vertice);
	}
	return vertices;
}

void printVector(vector<string> vect) {
	for (int i = 0; i < vect.size(); i++) {
		cout << vect[i] << ' ';
	}
	cout << '\n';
}

void printLs(map<string, vector<string>>  graph, vector<string> vertices, string outputFile) {
	ofstream output;
	output.open(outputFile);

	if (output.is_open()) {
		vector<string> value;
		for (string vertice : vertices) {
			output << vertice << ": ";

			auto pointer = graph.find(vertice);
			if (pointer != graph.end()) {
				value = graph.find(vertice)->second;
				for (string s : value)
					output << s << " ";
			}
			else {
				output << " ";
			}
			output << endl;
		}
		output << endl;
	}
}

void printMx(map<string, vector<string>>  graph, vector<string> vertices, string fileName) {
	ofstream output;
	output.open(fileName);
	if (output.is_open()) {
		vector<string> value;
		for (string verticeOutside : vertices) {
			auto pointer = graph.find(verticeOutside);
			string res = "";
			if (pointer != graph.end()) {
				value = graph.find(verticeOutside)->second;
				for (string verticeInside : vertices) {
					if (find(value.begin(), value.end(), verticeInside) != value.end()) {
						res += "1 ";
					}
					else
						res += "0 ";
				}
			}
			else {
				for (string verticeInside : vertices)
					res += "0 ";
			}
			output << res << endl;
		}
	}
}


void insertToMap(map<string, vector<string>>& graph, vector<string> value) {
	auto pointer = graph.find(value[0]);
	if (pointer != graph.end()) {
		graph[value[0]].push_back(value[1]);
	}
	else {
		vector<string> values = { value[1] };
		graph.insert({ value[0], values });
	}
}

void addToMap(map<string, vector<string>>& graph, string line) {
	vector<string> value = splitBySpace(line);

	insertToMap(graph, value);

	reverse(value.begin(), value.end());

	insertToMap(graph, value);
}

void makeSolution(map<string, vector<string>>& graph, char* argv[]) {
	ifstream input(argv[1]);
	string line;
	vector<string> vertices;

	if (input.is_open()) {
		getline(input, line);
		vertices = splitBySpace(line);

		while (getline(input, line)) {
			addToMap(graph, line);
		}
	}

	printLs(graph, vertices, argv[2]);
	printMx(graph, vertices, argv[3]);
}

int main(int argc, char* argv[]) {
	map<string, vector<string>> graph;
	makeSolution(graph, argv);

	return 0;
}