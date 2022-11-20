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
};

class Graph {
	
private:
	map<string, vector<string>> graph;
	vector<string> vertices;

public:
	Graph(const char* fileName) {
		ifstream input(fileName);
		string line;

		if (input.is_open()) {
			getline(input, line);
			setVertices(line);

			while (getline(input, line)) {
				addToMap(line);
			}
		}
	}

	map<string, vector<string>> getGraph() {
		return this->graph;
	}

	void setVertices(string vertices) {
		this->vertices = splitBySpace(vertices);
	}

	void insertToMap(vector<string> value) {
		auto pointer = graph.find(value[0]);
		if (pointer != graph.end()) {
			this->graph[value[0]].push_back(value[1]);
		}
		else {
			vector<string> values = { value[1] };
			this->graph.insert({ value[0], values });
		}
	}

	void addToMap(string line) {
		vector<string> value = splitBySpace(line);

		insertToMap(value);

		reverse(value.begin(), value.end());

		insertToMap(value);
	}

	void makeLs(const char* fileName) {
		ofstream output;
		output.open(fileName);

		if (output.is_open()) {
			vector<string> value;
			for (string vertice : this->vertices) {
				output << vertice << ": ";

				auto pointer = this->graph.find(vertice);
				if (pointer != this->graph.end()) {
					value = this->graph.find(vertice)->second;
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
	
	void makeMx(const char* fileName) {
		ofstream output;
		output.open(fileName);
		if (output.is_open()) {
			vector<string> value;
			for (string verticeOutside : this->vertices) {
				auto pointer = this->graph.find(verticeOutside);
				string res = "";
				if (pointer != this->graph.end()) {
					value = this->graph.find(verticeOutside)->second;
					for (string verticeInside : this->vertices) {
						if (find(value.begin(), value.end(), verticeInside) != value.end()) {
							res += "1 ";
						}
						else
							res += "0 ";
					}
				}
				else {
					for (string verticeInside : this->vertices)
						res += "0 ";
				}
				output << res << endl;
			}
		}
	}
};

int main(int argc, char* argv[]) {
	Graph graph = Graph(argv[1]);
	graph.makeMx(argv[2]);
	graph.makeLs(argv[3]);

	return 0;
}