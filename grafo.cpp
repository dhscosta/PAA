#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

struct Vertex {
    int id;
    vector<int> neighbors; // Lista de adjacência dos vértices vizinhos
};

class Graph {
private:
    vector<Vertex> vertices; // Lista de vértices do grafo

public:
    // Adicionar um vértice ao grafo
    void addVertex(int id) {
        Vertex v;
        v.id = id;
        vertices.push_back(v);
    }

    // Adicionar uma aresta entre dois vértices
    void addEdge(int id1, int id2) {
        // Encontrar os vértices correspondentes na lista de vértices
        auto it1 = find_if(vertices.begin(), vertices.end(), [id1](const Vertex& v) { return v.id == id1; });
        auto it2 = find_if(vertices.begin(), vertices.end(), [id2](const Vertex& v) { return v.id == id2; });

        // Se os vértices existirem, adicionamos arestas em ambos
        if (it1 != vertices.end() && it2 != vertices.end()) {
            it1->neighbors.push_back(id2);
            it2->neighbors.push_back(id1); // Como o grafo é não direcionado, adicionamos em ambos
        } else {
            cout << "Um ou ambos os vértices não foram encontrados." << endl;
        }
    }

    // Exibir o grafo
    void display() {
        for (const auto& vertex : vertices) {
            cout << "Vértice " << vertex.id << ": ";
            for (int neighbor : vertex.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph;

    // Adicionando vértices
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);

    // Adicionando arestas
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    // Exibindo o grafo
    cout << "Grafo não direcionado e não ponderado:" << endl;
    graph.display();

    return 0;
}
