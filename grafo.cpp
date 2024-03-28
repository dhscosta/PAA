#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Vertex
{
    int id;
    vector<int> neighbors; // Lista de adjacência dos vértices vizinhos
};

class Graph
{
private:
    vector<Vertex> vertices; // Lista de vértices do grafo

public:
    // Adicionar um vértice ao grafo
    void addVertex(int id)
    {
        Vertex v;
        v.id = id;
        vertices.push_back(v);
    }

    // Adicionar uma aresta entre dois vértices
    void addEdge(int id1, int id2)
    {
        // Encontrar os vértices correspondentes na lista de vértices
        auto it1 = find_if(vertices.begin(), vertices.end(), [id1](const Vertex &v)
                           { return v.id == id1; });
        auto it2 = find_if(vertices.begin(), vertices.end(), [id2](const Vertex &v)
                           { return v.id == id2; });

        // Se os vértices existirem, adicionamos arestas em ambos
        if (it1 != vertices.end() && it2 != vertices.end())
        {
            it1->neighbors.push_back(id2);
            it2->neighbors.push_back(id1); // Como o grafo é não direcionado, adicionamos em ambos
        }
        else
        {
            cout << "Um ou ambos os vertices não foram encontrados." << endl;
        }
    }

    // Exibir o grafo
    void display()
    {
        for (const auto &vertex : vertices)
        {
            cout << "Vertice " << vertex.id << ": ";
            for (int neighbor : vertex.neighbors)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Contar os ciclos no grafo
    int countCycles()
    {
        int count = 0;
        vector<int> path;
        vector<bool> visited(vertices.size(), false);
        int numVertices = static_cast<int>(vertices.size());
        for (int i = 0; i < numVertices; i++)
        {

            path.push_back(vertices[i].id);
            visited[i] = true;
            count += countCyclesUtil(i, i, path, visited);
            path.pop_back();
            visited[i] = false;
        }

        return count; // Como cada ciclo é contado duas vezes, dividimos por 2 para obter o número correto de ciclos
    }

private:
    int countCyclesUtil(int start, int current, vector<int> &path, vector<bool> &visited)
    {
        int count = 0;


        for (int neighborId : vertices[current].neighbors)
        {

            // Encontrar o índice do vizinho em 'vertices'
            auto it = find_if(vertices.begin(), vertices.end(), [neighborId](const Vertex &v)
                              { return v.id == neighborId; });
            if (it != vertices.end())
            {
                int neighborIndex = distance(vertices.begin(), it); // Obtém o índice do vizinho
                if (neighborIndex == start)
                {

                    if (path.size() > 2)
                    {
                    count++;
                    }
                    continue;
                }

                if (!visited[neighborIndex])
                {
                    path.push_back(vertices[neighborIndex].id);
                    visited[neighborIndex] = true;

                    count += countCyclesUtil(start, neighborIndex, path, visited);
                    path.pop_back();
                    visited[neighborIndex] = false;
                }
            }
        }

        return count;
    }
};

int main()
{
    Graph graph;

    // Adicionando vértices
  /* grafo do pdf
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addVertex(6);

    // Adicionando arestas
    graph.addEdge(1, 4);
    graph.addEdge(4, 2);
    graph.addEdge(4, 3);
    graph.addEdge(6, 4);
    graph.addEdge(2, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 5);
    graph.addEdge(2, 5);
    graph.addEdge(5, 6);
    graph.addEdge(3, 5);
    graph.addEdge(3, 6);

  */

 // k5
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);

    // Adicionando arestas
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 5);
    graph.addEdge(2, 3);
    graph.addEdge(2, 5);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    // Exibindo o grafo
    cout << "Grafo nao direcionado e nao ponderado:" << endl;
    graph.display();

    // Contando os ciclos
    int cycleCount = graph.countCycles();
    cout << "Numero de ciclos no grafo: " << cycleCount << endl;

    return 0;
}
