#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <inttypes.h>
#include <stdio.h>
using namespace std;

typedef pair<int, int> Point;
typedef pair<Point, double> Edge; //Vertice and weigth

int n, r;
map<Point, vector<Edge>> adjList;
map<Point, Point> pred;
map<Point, double> dist;
vector<Point> vertices;
const double eps = 0.01;

vector<string> splitBySpace(const string str) {
	stringstream strStream(str);
	string vertice;
	vector<string> vertices;
	while (getline(strStream, vertice, ' ')) {
		vertices.push_back(vertice);
	}
	return vertices;
}

double getDistance(Point a, Point b) {
	double first = pow(b.first - a.first, 2);
	double second = pow(b.second - a.second, 2);
	return sqrt(first + second);
}

void readFromFile(const char* fileName) {
	ifstream input(fileName);
	string line;
	vector<Edge> emptyEdge;

	if (input.is_open()) {
		input >> n;
		input >> r;

		getline(input, line); // почему-то дальше из файла считывает пустую строку
		while (getline(input, line)) {
			vector<string> tmp = splitBySpace(line);
			Point current(stoi(tmp[0]), stoi(tmp[1]));
			adjList.insert({ current, emptyEdge});
			vertices.push_back(current);
		}
	}
}

void fillGraph() {
	for (int i = 0; i < vertices.size(); i++) {
		for (int j = 0; j < vertices.size(); j++) {
			if (i != j) {
				const double len = getDistance(vertices[i], vertices[j]);
				if (len <= r)
					adjList[vertices[i]].push_back({ vertices[j], len });
			}
		}
	}
}

bool compareDouble(double first, double second) {
	return second - first >= eps;
}

void addPred(Point child, Point parent) {
	auto pointer = pred.find(child);
	if (pointer != pred.end())
		pred[child] = parent;
	else
		pred.insert({ child, parent });
}

void Dijkstra() {
	map<Point, bool> visited;
	for (int i = 0; i < n; i++) {
		dist.insert({ vertices[i], INFINITY });
	}

	dist[vertices[0]] = 0; // Путь из стартовой вершины
	
	for (int i = 0; i < n; i++) {
		Point current(INFINITY, INFINITY);
		for (int j = 0; j < n; j++) {
			if (!visited[vertices[j]] && (current == Point(INFINITY, INFINITY) || compareDouble(dist[vertices[j]], dist[current]))) {
				current = vertices[j];
			}
		}
		visited[current] = true;

		for (size_t j = 0; j < adjList[current].size(); ++j) {
			Point to = adjList[current][j].first;
			double weight = adjList[current][j].second;
			if (compareDouble(dist[current] + weight, dist[to])) {
				dist[to] = dist[current] + weight;
				addPred(to, current);
			}
		}
	}
}

vector<Point> makePath() {
	vector<Point> path;
	vector<Point> emptyCase;
	if (pred[vertices[n - 1]] == Point()) {
		return emptyCase;
	}

	for (Point v = vertices[n - 1]; v != vertices[0]; v = pred[v]) {
		path.push_back(v);
	}
	path.push_back(vertices[0]);
	reverse(path.begin(), path.end());

	return path;
}

void makeOutput(const char* fileName) {
	ofstream output;
	output.open(fileName);
	vector<Point> path = makePath();
	if (path.size() == 0) {
		output << -1;
		return;
	}
	// Не знаю почему, но если просто округлять до двух знаков, он слишком рано отбрасывает дальнейшие знаки, и не получает заветную сотую
	// Если применить вот такое округление получим нужный ответ
	cout << round(ceil(dist[vertices[n - 1]]*1000)/ 1000 * 100)/100 << endl;

	output << dist[vertices[n - 1]] << endl;
	for (Point vertice : path) {
		output << vertice.first << " " << vertice.second << "\n";
	}
}

int main(int argc, char* argv[]) {
	readFromFile(argv[1]);
	fillGraph();
	Dijkstra();
	makeOutput(argv[2]);
}