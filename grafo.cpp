#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adjacencyList; // Lista de adjacência do grafo
    int numVertices;

public:
    // Construtor
    Graph(int n) : numVertices(n)
    {
        adjacencyList.resize(n + 1); // +1 porque o ID dos vértices começa de 1
    }

    // Adicionar uma aresta entre dois vértices
    void addEdge(int id1, int id2)
    {
        adjacencyList[id1].push_back(id2);
        adjacencyList[id2].push_back(id1); // Como o grafo é não direcionado, adicionamos em ambos
    }

    // Exibir o grafo
    void display()
    {
        for (int i = 1; i <= numVertices; ++i)
        {
            cout << "Vertice " << i << ": ";
            for (int neighbor : adjacencyList[i])
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
        vector<bool> visited(numVertices + 1, false); // Lista de vértices já visitados
        std::chrono::system_clock::time_point inicio;
        std::chrono::system_clock::time_point fim;

        inicio = std::chrono::system_clock::now();
        for (int i = 1; i <= numVertices; ++i)
        {
            count += countCyclesUtil(i, i, visited, -1); // -1 indica que não há pai inicialmente
        }
        fim = std::chrono::system_clock::now();

        double tempofinal = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count() / 1000.0; // Convertendo para segundos
        cout << "Tempo de execução: " << tempofinal << " segundos" << endl;
        return count;
    }

    void generateCompleteGraph(int n)
    {
        // Adiciona arestas entre todos os pares de vértices distintos
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                addEdge(i, j);
            }
        }
    }

private:
    int countCyclesUtil(int start, int current, vector<bool> &visited, int parent)
    {
        int count = 0;
        visited[current] = true;

        for (int neighbor : adjacencyList[current])
        {
            if (neighbor != parent) // Evita visitar o vértice pai
            {
                if (!visited[neighbor])
                {
                    count += countCyclesUtil(start, neighbor, visited, current);
                }
                else if (neighbor == start)
                {
                    ++count;
                }
            }
        }

        visited[current] = false; // Marcar o vértice como não visitado ao retornar da recursão
        return count;
    }
};

int main()
{
    Graph g(5);
    g.addEdge(1, 4);
    g.addEdge(4, 2);
    g.addEdge(4, 3);
    g.addEdge(6, 4);
    g.addEdge(2, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 5);
    g.addEdge(2, 5);
    g.addEdge(5, 6);
    g.addEdge(3, 5);
    g.addEdge(3, 6);

    cout << "Grafo:" << endl;
    g.display();

    cout << "Número de ciclos no grafo: " << g.countCycles() << endl;

    return 0;
}