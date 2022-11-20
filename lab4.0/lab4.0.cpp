#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include<queue>
using namespace std;

typedef pair<int, int> edge;

int result = 0;
int n, m, k, w;
vector<vector<edge>> adjList;
vector<vector<char>> plan;
vector<int> fullPart;

void addEdge(int key, edge value) {
	adjList[key].push_back(value);
}

int compareFloors(vector<char> firstFloor, vector<char> secondFloor) {
	int changes = 0;
	for (int i = 0, j = 0; i < firstFloor.size() && j < secondFloor.size(); i++, j++) {
		if (firstFloor[i] != secondFloor[i])
			changes++;
	}
	return changes;
}

void fillGraph() {
	int cost;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (i != j) {
				int changes = compareFloors(plan[i], plan[j]);
				if (changes * w > n * m) {
					cost = n * m;
				}
				else {
					cost = changes * w;
				}
				addEdge(i, { j, cost });
			}
		}
	}
}

void readFromFile(const char* fileName) {
	ifstream input(fileName);
	string line;
	vector<char> emptyaFloor;
	vector<edge> emptyEdge;

	if (input.is_open()) {
		input >> n;
		input >> m;
		input >> k;
		input >> w;

		for (int i = 0; i < k; i++) {
			plan.push_back(emptyaFloor);
			adjList.push_back(emptyEdge);
			fullPart.push_back(-1);
		}

		int numberFloor = 0;
		getline(input, line); // почему-то дальше из файла считывает пустую строку
		while (!input.eof() && numberFloor < k) {
			for (int i = 0; i < n; i++) {
				getline(input, line);
				for (char chr : line) {
					plan[numberFloor].push_back(chr);
				}
			}
			numberFloor++;
		}
	}
}

void Prim() {
	priority_queue<edge, vector<edge>, greater<edge>> prioritQueue;
	vector<int> key(k, INT_MAX);
	vector<bool> inMST(k, false);
	vector<int> parent(k, -1);

	
	int src = 0;				   // Берем нулевую вершину для начала
	prioritQueue.push({ 0, src }); // Добавляем для начала ребро из 0 в 0
	key[src] = 0;				   // Вес перемещения соответственно 0
	result += n * m;			   // Первый этаж передаем целиком
	fullPart[src] = 0;			   // Первый этаж передаем целиком
	
	while (!prioritQueue.empty()) {
		edge itemNode = prioritQueue.top();
		prioritQueue.pop();

		int dest = itemNode.second;

		if (inMST[dest])
			continue;
		else {
			inMST[dest] = true;
			for (edge vertice : adjList[dest]) {
				int node = vertice.first; // vertice
				int cost = vertice.second; // weight
				if (!inMST[node] && key[node] >= cost) {
					key[node] = cost;
					prioritQueue.push({ key[node], node });
					if (n * m <= key[node]) {
						parent[node] = -1; // Передаем целиком
					}
					else
						parent[node] = dest; // Передаем частично
				}
			}
		}
	}
	for (int i = 1; i < k; ++i) {
		result += key[i];
		fullPart[i] = parent[i] + 1;
	}
}

void makeOutput(const char* fileName) {
	ofstream output;
	output.open(fileName);
	output << result << endl;
	for (int i = 0; i < k; i++) {
		output << i + 1 << ' ' << fullPart[i] << endl;
	}
}

int main(int argc, char* argv[]) {
	readFromFile(argv[1]);
	fillGraph();
	
	Prim();
	makeOutput(argv[2]);
}