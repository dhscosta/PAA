#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

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

    void generateCompleteGraph(int n)
    {
        // Adiciona n vértices ao grafo
        for (int i = 1; i <= n; i++)
        {
            addVertex(i);
        }

        // Adiciona arestas entre todos os pares de vértices distintos
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                addEdge(i, j);
            }
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

    int permutacao()
{
    int count = 0;
    vector<int> vertexIds;
    for (const auto &vertex : vertices)
    {
        vertexIds.push_back(vertex.id);
    }

    // Sort the vertex IDs in ascending order
    sort(vertexIds.begin(), vertexIds.end());


    for (int vertexId : vertexIds)
    {
        cout << vertexId << " ";
    }
    cout << endl;
    cout << endl;
    
    // Loop through all possible cycle lengths from 3 to vertexIds.size()
    for (int cycleLength = 3; cycleLength <= vertices.size(); cycleLength++)
    {
        do
        {
            // Generate a permutation of the vertex IDs
            vector<int> permutation(vertexIds.begin(), vertexIds.begin() + cycleLength);
            
            
            // Check if the permutation forms a cycle
            bool isCycle = true;
            for (int i = 0; i < cycleLength; i++)
            {
                int current = permutation[i];
                int next = permutation[(i + 1) % cycleLength];

                auto it = find(vertices[current - 1].neighbors.begin(), vertices[current - 1].neighbors.end(), next);

                if (it == vertices[current - 1].neighbors.end())
                {
                    isCycle = false;
                    break;
                }
            }

            if (isCycle)
            {
                for (int vertexId : permutation)
                {
                    cout << vertexId << " ";
                }
                cout << endl;
                count++;
            }
            if (vertices.size() - cycleLength >= 2)
            {
                for (int i = 0; i < vertices.size() -4; i++)
                {
                    next_permutation(vertexIds.begin(), vertexIds.end())   ;   
                }
                
                      }
            
        } while (next_permutation(vertexIds.begin(), vertexIds.end()));
    }

    return count;
}


};

int main()
{
    int n;
    cout << "Digite o valor de n para gerar o grafo completo K_n: ";
    cin >> n;
    Graph completeGraph;
    completeGraph.generateCompleteGraph(n);
    std::chrono::system_clock::time_point inicio;
    std::chrono::system_clock::time_point fim;

    inicio = std::chrono::system_clock::now();

    // Exibindo o grafo
    cout << "Grafo nao direcionado e nao ponderado:" << endl;
    completeGraph.display();

    // Contando os ciclos
    int cycleCount = completeGraph.permutacao();
    cout << "Numero de ciclos no grafo: " << cycleCount << endl;
    fim = std::chrono::system_clock::now();

    double tempofinal = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count() / 1000.0; // Convertendo para segundos

    cout << "Tempo de execucao: " << tempofinal << " segundos" << endl;
    return 0;
}
