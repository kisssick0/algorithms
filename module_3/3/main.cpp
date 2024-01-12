//Требуется отыскать самый выгодный маршрут между городами.
//Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
//Формат входных данных.
//Первая строка содержит число N – количество городов.
//Вторая строка содержит число M - количество дорог.
//Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
//Последняя строка содержит маршрут (откуда и куда нужно доехать).
//Формат выходных данных.
//Вывести длину самого выгодного маршрута.


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class CityGraph {
    vector<vector<pair<int, int>>> matrix;
public:
    explicit CityGraph(int vertCnt): matrix(vertCnt){};
    vector<pair<int, int>> getVertexes (int vertId) const;
    void addEdge(int vert1, int vert2, int weight);
    size_t getSize() const {return matrix.size();}
};

vector<pair<int, int>> CityGraph::getVertexes(int vertId) const {
    return matrix[vertId];
}

void CityGraph::addEdge(int vert1, int vert2, int weight) {
    matrix[vert1].push_back({vert2, weight});
    matrix[vert2].push_back({vert1, weight});
}

int lenShortest(const CityGraph& graph, int from, int to) {
    queue<int> current;
    current.push(from);
    vector<int> lengths(graph.getSize(), 10000*10000);
    lengths[from] = 0;
    while (!current.empty()) {
        queue<int> nextCurrent;
        while (!current.empty()) {
            int currVert = current.front();
            current.pop();
            vector<pair<int, int>> currVertVertex = graph.getVertexes(currVert);
            for (int i = 0; i < currVertVertex.size(); ++i) {
                if (lengths[currVert] + currVertVertex[i].second < lengths[currVertVertex[i].first]){
                    nextCurrent.push(currVertVertex[i].first);
                    lengths[currVertVertex[i].first] = lengths[currVert] + currVertVertex[i].second;
                }
            }
        }
        current = nextCurrent;
    }
    return lengths[to];
}

int main() {
    int numVertex, numEdges;
    int from, to, length;
    cin >> numVertex;
    cin >> numEdges;
    CityGraph graph(numVertex);
    for (int i = 0; i < numEdges; i++) {
        cin >> from >> to >> length;
        graph.addEdge(from, to, length);
    }
    cin >> from >> to;
    cout << lenShortest(graph, from, to) << endl;
};
