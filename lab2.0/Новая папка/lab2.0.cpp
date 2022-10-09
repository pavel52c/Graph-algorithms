#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

struct Point {
    string X;
    string Y;

    Point() {
		this->X = "";
		this->Y = "";
    }

    Point(string x, string y) {
        this->X = x;
        this->Y = y;
    }

	bool operator<(Point other) const {
		if (X != other.X)
			return (X < other.X);

		if (Y != other.Y)
			return (Y < other.Y);

		return false;
	}

	bool operator==(Point other) const {
		return this->X == other.X && this->Y == other.Y;
	}

	bool operator!=(Point other) const {
		return this->X != other.X && this->Y != other.Y;
	}

	Point operator=(Point other) {
		X = other.X;
		Y = other.Y;
		return *this;
	}
};

map<Point, vector<Point>> adjList;
map<Point, Point> Pred;
vector<Point> cycle;
map<Point, string> State;

vector<string> splitBySpace(const string str) {
	stringstream strStream(str);
	string vertice;
	vector<string> vertices;
	while (getline(strStream, vertice, ' ')) {
		vertices.push_back(vertice);
	}
	return vertices;
}

void printVector(vector<Point> vect) {
	for (int i = 0; i < vect.size(); i++) {
		cout <<"(" << vect[i].X << ", " << vect[i].Y << ") ";
	}
}

void insertToMap(map<Point, vector<Point>>& adjList, Point src, Point dest) {
	auto pointer = adjList.find(src);
	if (pointer != adjList.end()) {
		adjList[src].push_back(dest);
	}
	else {
		vector<Point> values = { dest };
		adjList.insert({ src, values });
	}
}

void addEdge(map<Point, vector<Point>> &adjList, string line) {
	vector<string> coord = splitBySpace(line);

	Point src(coord.at(0), coord.at(1));
	Point dest(coord.at(2), coord.at(3));

	insertToMap(adjList, src, dest);
	insertToMap(adjList, dest, src);
}

int readFromFile(const char* fileName) {
	ifstream input(fileName);
	int countRoads;
	input >> countRoads;
	string line;
	if (input.is_open()) {
		getline(input, line); // Почему-то дальше из файла считывает пустую строку
		while (getline(input, line)) {
			addEdge(adjList, line);
		}
	}
	return countRoads;
}

vector<Point> getKeys(map<Point, vector<Point>> Map) {
	vector<Point> result;
	for (map<Point, vector<Point>>::iterator iter = adjList.begin(); iter != adjList.end(); ++iter) {
		result.push_back(iter->first);
	}
	return result;
}

void DFS_Visit(Point vertex) {
	State[vertex] = "visited";
	for (Point i : adjList[vertex]) {
		if (State[i] == "unvisited") {
			Pred[i] = vertex;
			DFS_Visit(i);
		}
		else if (Pred[vertex] != i && State[i] == "visited") {
			auto pointer = find(cycle.begin(), cycle.end(), vertex);
			if (pointer == cycle.end()) {
				cycle.push_back(vertex);
				DFS_Visit(i);
			}
		}
	}
	State[vertex] = "processed";
}

void DFS() {
	vector<Point> vertices = getKeys(adjList);

	for (Point vertice : vertices) {
		State[vertice] = "unvisited";
		Pred[vertice] = Point();
	}

	for (Point vertice : vertices) {
		if (State[vertice] == "unvisited") {
			DFS_Visit(vertice);
		}
	}
}

void makeOutput(const char* fileName) {
	ofstream output;
	output.open(fileName);
	output << cycle.size() << endl;
	for (int i = 0; i < cycle.size(); i++) {
		output << cycle[i].X << " " << cycle[i].Y << endl;
	}
}

int main(int argc, char* argv[]) {
	int countVertices = readFromFile(argv[1]);
	DFS();
	makeOutput(argv[2]);
}