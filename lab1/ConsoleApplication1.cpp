#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

vector<string> graph;
vector<char> verts;
vector<int> color;
vector<int> order;

int weight;

const int WHITE = 0;
const int BLACK = 1;
const int GRAY = 2;

int map_char_to_int(char c) {
    for (auto i = 0; i < verts.size(); i++) {
        if (verts[i] == c) {
            return i;
        }
    }
    return -1;
}

int add(char c) {
    int pos = map_char_to_int(c);
    if (pos == -1) {
        verts.push_back(c);
        graph.push_back("");
        order.push_back(0);
        color.push_back(WHITE);
        return verts.size() - 1;
    }
    return pos;
}

void add_to_graph(char c, int pos) {
    string t = graph[pos];
    if (t.find(c) == string::npos) {
        graph[pos] = t + c;
    }
}

void make_graph() {
    ifstream ifs;
    ifs.open("input.txt");

    int num;
    ifs >> num;
    // Я заполняю граф как: Беру первое слово из пары как отправную точку, добавляю все буквы из первого слова.
    // Если идёт несовпадение букв первого и второго слов - рисую дугу (добавляю в граф)
    // В конце отдельно рассматриваю последнее слово, чтобы добавить недостающие буквы
    string second_word;
    ifs >> second_word;
    int j;

    for (int i = 0; i < num; i++) {
        string first_word = second_word;
        ifs >> second_word;
        j = 0;
        bool ok = true;
        for (; j < first_word.size(); j++) {
            int pos = add(first_word[j]);
            if (j < second_word.size()) {
                if (ok && first_word[j] != second_word[j]) {
                    ok = false;
                    add(second_word[j]);
                    add_to_graph(second_word[j], pos);
                }
            }
        }
    }
    for (; j < second_word.size(); j++) {
        add(second_word[j]);
    }
    weight = verts.size();
}

bool dfs_visit(int pos) {
    color[pos] = GRAY;
    for (char c : graph[pos]) {
        int number = map_char_to_int(c);
        if (color[number] == GRAY) {
            return false;
        }
        else if (color[number] == WHITE) {

            if (!dfs_visit(number)) {
                return false;
            }
        }
    }
    order[--weight] = pos;
    color[pos] = BLACK;
    return true;
}

bool topo_sort() {
    for (int i = 0; i < verts.size(); i++) {
        if (color[i] == WHITE) {
            if (!dfs_visit(i)) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    make_graph();
    cout << "AYE";
    if (!topo_sort()) {
        cout << "-";
        return 0;
    }
    for (int i : order) {
        cout << verts[i];
    }

    return 0;
}
