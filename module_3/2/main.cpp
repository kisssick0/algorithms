//Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами.
//Требования: сложность O(V+E).
//Формат ввода.
//v: кол-во вершин (макс. 50000),
//n: кол-во ребер (макс. 200000),
//n пар реберных вершин,
//пара вершин u, w для запроса.
//Формат вывода.
//Количество кратчайших путей от u к w.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    vector<vector<int>> matrix;
public:
    explicit Graph(int vertCnt): matrix(vertCnt){};
    
    size_t getSize() const {return matrix.size();}
    
    vector<int> getVertexes(int vertId) const {
        return matrix[vertId];
    }
    
    void addEdge(int vert1, int vert2) {
        matrix[vert1].push_back(vert2);
        matrix[vert2].push_back(vert1);
    }
};


int minCount(const Graph& graph, int from, int to) {
    queue<int> current;
    current.push(from);
    vector<int> lengths(graph.getSize(), 10000*10000);
    vector<int> countMin(graph.getSize(), 0);
    lengths[from] = 0;
    countMin[from] = 1;
    while (!current.empty()) {
        queue<int> nextCurrent;
        while (!current.empty()) {
            int currVert = current.front();
            current.pop();
            vector<int> currVertVertex = graph.getVertexes(currVert);
            for (int i = 0; i < currVertVertex.size(); ++i) {
                if (lengths[currVert] + 1 < lengths[currVertVertex[i]]) {
                    lengths[currVertVertex[i]] = lengths[currVert] + 1;
                    nextCurrent.push(currVertVertex[i]);
                }
                if (lengths[currVertVertex[i]] == lengths[currVert] + 1) {
                    countMin[currVertVertex[i]] += countMin[currVert];
                }
            }
        }
        current = nextCurrent;
    }
    return countMin[to];
}

int main() {
    int numVertex, numEdges, from, to;
    cin >> numVertex;
    cin >> numEdges;
    Graph graph(numVertex);
    for (int i = 0; i < numEdges; ++i) {
        cin >> from >> to;
        graph.addEdge(from, to);
    }
    cin >> from >> to;
    cout << minCount(graph, from, to) << endl;
};
