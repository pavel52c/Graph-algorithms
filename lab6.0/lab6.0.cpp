#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

typedef pair<string, double> Edge; //Vertice and weigth
vector<string> vertices;
vector<vector<double>> matrix;
vector<pair<string, string>> output;
map<string, int> dict;
vector<vector<double>> resultFlows;


vector<string> splitBySpace(const string str) {
	stringstream strStream(str);
	string vertice;
	vector<string> vertices;
	while (getline(strStream, vertice, ' ')) {
		vertices.push_back(vertice);
	}
	return vertices;
}

void readFromFile(const char* fileName) {
	ifstream input(fileName);
	string line;

	if (input.is_open()) {
		getline(input, line);
		vertices = splitBySpace(line);

		vector<double> empty(vertices.size(), 0);
		for (int i = 0; i < vertices.size(); i++) {
			dict.insert({ vertices[i], i});
			matrix.push_back(empty);
		}

		while (getline(input, line)) {
			vector<string> tmp = splitBySpace(line);
			if (tmp.size() > 0) { // Проверка на пустую строку в файле
				string firstVertice = tmp[0];
				string secondVertice = tmp[1];
				double flow = stod(tmp[2]);

				output.push_back({ firstVertice, secondVertice });
				matrix[dict[firstVertice]][dict[secondVertice]] = flow;
			}
			else
				continue;
		}
	}
}

bool bfs(vector<vector<double>> rGraph, int s, int t, vector<int>& parent) {
	vector<bool> visited(rGraph.size(), false); 
	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v = 0; v < vertices.size(); v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return (visited[t] == true);
}

int fordFulkerson(int s, int t) {
	int u, v;
	vector<double> empty(vertices.size(), 0);
	vector<vector<double>> rGraph(vertices.size(), empty);
	for (u = 0; u < matrix.size(); u++) {
		for (v = 0; v < matrix.size(); v++) {
			rGraph[u][v] = matrix[u][v];
		}
	}
	vector<int> parent(rGraph.size(), -1);
	int max_flow = 0;

	while (bfs(rGraph, s, t, parent)) {
		double path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}
		max_flow += path_flow;
	}
	resultFlows = rGraph;
	return max_flow;
}

void makeOutput(const char* fileName) {
	ofstream outputFile;
	outputFile.open(fileName);
	outputFile << fordFulkerson(0, vertices.size() - 1) << endl;
	for (pair<string, string> edge : output) {
		string first = edge.first;
		string second = edge.second;
		outputFile << edge.first << " " << edge.second << " " << resultFlows[dict[first]][dict[second]] << endl;
	}	
}

int main(int argc, char* argv[]) {
	readFromFile(argv[1]);
	makeOutput(argv[2]);
}