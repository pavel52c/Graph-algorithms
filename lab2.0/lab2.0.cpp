#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>

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
};

struct Road {
	Point src;
	Point dest;

	Road() {
		this->src = Point();
		this->dest = Point();
	}

	Road(Point src, Point dest) {
		this->src = src;
		this->dest = dest;
	}
};

vector<string> splitBySpace(const string str) {
	stringstream strStream(str);
	string vertice;
	vector<string> vertices;
	while (getline(strStream, vertice, ' ')) {
		vertices.push_back(vertice);
	}
	return vertices;
}

void addEdge(queue<Road> Queue, Point src, Point dest) {
	Queue.push(Road(src, dest));
}

void printVector(vector<string> vect) {
	for (int i = 0; i < vect.size(); i++) {
		cout << vect[i] << ' ';
	}
	cout << '\n';
}

int readFromFile(const char* fileName, queue<Road> Queue) {
	ifstream input(fileName);
	int countRoads;
	input >> countRoads;
	string line;
	if (input.is_open()) {
		getline(input, line);
		while (getline(input, line)) {
			vector<string> coord = splitBySpace(line);

			Point src(coord.at(0), coord.at(1));
			Point dest(coord.at(2), coord.at(3));
			
			addEdge(Queue, src, dest);
		}
	}
	return countRoads;
}

int main() {
	vector<bool> State;
	queue<Road> Queue;
	vector<Point> Pred;
	int countRoads = readFromFile("Input.txt", Queue);
	cout << countRoads;
}
