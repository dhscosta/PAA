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
        // dado o Id se procura o vértice correspondente na lista de vértices
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

    // Contar os ciclos no grafo
    int countCycles()
    {
        int count = 0;
        vector<int> path;                                    // Lista de vértices que representa o caminho
        vector<bool> visited(vertices.size(), false);        // Lista de vértices ja vizitados
        int numVertices = static_cast<int>(vertices.size()); // Quantos vertices tem no grafo
        for (int i = 0; i < numVertices; i++)
        {
            // nesse loop começa a busca por ciclos apartir de cada vértice
            // Ao mesmo tempo para cada ciclo achado é adicionado ao contador
            path.push_back(vertices[i].id);
            visited[i] = true;
            count += countCyclesUtil(i, i, path, visited);
            path.pop_back();
            visited[i] = false;
        }

        return count;
    }

   

private:
    int countCyclesUtil(int start, int current, vector<int> &path, vector<bool> &visited)
    {
        int count = 0;

        for (int neighborId : vertices[current].neighbors)
        {

            // Encontrar o índice do vizinho apartir do ID na lista de vértices
            auto it = find_if(vertices.begin(), vertices.end(), [neighborId](const Vertex &v)
                              { return v.id == neighborId; });

            if (it != vertices.end())
            {
                int neighborIndex = distance(vertices.begin(), it); // Obtém o índice do vizinho
                if (neighborIndex == start)                         // achou ciclo
                {

                    if (path.size() > 2) // nao contar ciclos com apenas 2 vértices
                    {
                        count++;
                    }
                    continue;
                }

                if (!visited[neighborIndex]) // procura caminhos nao vizitados
                {
                    path.push_back(vertices[neighborIndex].id);
                    visited[neighborIndex] = true;

                    count += countCyclesUtil(start, neighborIndex, path, visited); // chamada recursiva para continuar o caminho
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
    int n;
    cout << "Digite o valor de n para gerar o grafo completo K_n: ";
    cin >> n;
    Graph completeGraph;
    completeGraph.generateCompleteGraph(n);
    std::chrono::system_clock::time_point inicio;
    std::chrono::system_clock::time_point fim;

    inicio = std::chrono::system_clock::now();

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
    /*
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
   */

    // Exibindo o grafo
    cout << "Grafo nao direcionado e nao ponderado:" << endl;
    completeGraph.display();

    // Contando os ciclos
    int cycleCount = completeGraph.countCycles();
    cout << "Numero de ciclos no grafo: " << cycleCount << endl;
    fim = std::chrono::system_clock::now();

    double tempofinal = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count() / 1000.0; // Convertendo para segundos

    cout << "Tempo de execucao: " << tempofinal << " segundos" << endl;
    return 0;
}
