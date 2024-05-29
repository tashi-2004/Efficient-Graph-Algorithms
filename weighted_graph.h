#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <cmath>
#include <cstdlib>
#include<ctime>
#include <limits>
using namespace std;
//````````````````````````````````````````````` Class Weighted_Graph```````````````````````````````````````````````````
class Weighted_graph
{
private:
    int num_ver;
    double** adjacency_matrix;
    static const double INF;
public:
    Weighted_graph();
    Weighted_graph(int n);
    int degree(int n) const;
    int edge_count() const;
    double adjacent(int m, int n) const;
    double distance(int m, int n) const;
    void insert(int m, int n, double w);
    ~Weighted_graph();
    friend ostream& operator<<(ostream&, Weighted_graph const&);
};
const double Weighted_graph::INF = std::numeric_limits<double>::infinity();
//``````````````````````````````````````````````  Default Constructor `````````````````````````````````````````````````````
Weighted_graph::Weighted_graph()
{
    num_ver = 0;
    adjacency_matrix = nullptr;
}
//````````````````````````````````````````````` Parameterized Constructor ``````````````````````````````````````````````````
Weighted_graph::Weighted_graph(int n = 50)
{
    num_ver = (n <= 0) ? 1 : n;
    adjacency_matrix = new double* [num_ver];
    for (int i = 0; i < num_ver; ++i)
    {
        adjacency_matrix[i] = new double[num_ver];
        for (int j = 0; j < num_ver; ++j)
            adjacency_matrix[i][j] = -1.0;
    }
}
//`````````````````````````````````````````````````````` Degree ```````````````````````````````````````````````````````````
int Weighted_graph::degree(int n) const
{
    if (n < 0 || n >= num_ver)
        throw "Vertex index out of bounds";

    int degree_count = 0;
    for (int i = 0; i < num_ver; ++i)
    {
        if (i != n && adjacency_matrix[n][i] >= 0)
            ++degree_count;
    }
    return degree_count;
}
//````````````````````````````````````````````````````` Edge Count````````````````````````````````````````````````````````````
int Weighted_graph::edge_count() const
{
    int count = 0;
    for (int i = 0; i < num_ver; ++i)
    {
        for (int j = i + 1; j < num_ver; ++j)
        {
            if (adjacency_matrix[i][j] >= 0)
                ++count;
        }
    }
    return count;
}
//```````````````````````````````````````````````````````` Adjacent ````````````````````````````````````````````````````````````
double Weighted_graph::adjacent(int m, int n) const
{
    if (m < 0 || m >= num_ver || n < 0 || n >= num_ver)
        throw "Vertex index out of bounds";
    if (m == n)
        return 0.0;
    if (adjacency_matrix[m][n] >= 0)
        return adjacency_matrix[m][n];
    return std::numeric_limits<double>::infinity();
}
//````````````````````````````````````````````````````````` Distance `````````````````````````````````````````````````````````````
double Weighted_graph::distance(int m, int n) const
{
    //Applying Dijistra Algo
    if (m < 0 || m >= num_ver || n < 0 || n >= num_ver)
        throw "Vertex index out of bounds";
    double* dist = new double[num_ver];
    for (int i = 0; i < num_ver; ++i)
        dist[i] = std::numeric_limits<double>::infinity();
    dist[m] = 0.0;
    bool* visited = new bool[num_ver] {false};

    while (!visited[n])
    {
        int u = -1;
        for (int i = 0; i < num_ver; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        if (u == -1)
            break;
        visited[u] = true;
        for (int v = 0; v < num_ver; ++v) {
            if (!visited[v] && adjacency_matrix[u][v] >= 0) {
                dist[v] = std::min(dist[v], dist[u] + adjacency_matrix[u][v]);
            }
        }
    }
    double result = dist[n];
    delete[] dist;
    delete[] visited;
    return result;
}
//``````````````````````````````````````````````````````````` Insert ``````````````````````````````````````````````````````````````
void Weighted_graph::insert(int m, int n, double w)
{
    if (m < 0 || m >= num_ver || n < 0 || n >= num_ver || m == n)
        throw "Invalid vertex indices";
    if (w <= 0 || isinf(w))
        throw "Invalid edge weight";
    adjacency_matrix[m][n] = w;
    adjacency_matrix[n][m] = w;
}
//`````````````````````````````````````````````````````````` Destructor ````````````````````````````````````````````````````````````
Weighted_graph::~Weighted_graph() {
    if (adjacency_matrix) {
        for (int i = 0; i < num_ver; ++i)
            delete[] adjacency_matrix[i];
        delete[] adjacency_matrix;
    }
}
//`````````````````````````````````````````````````````````` Operator<< `````````````````````````````````````````````````````````````
ostream& operator<<(ostream& out, const Weighted_graph& graph)
{
    int numVertices = graph.num_ver;
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (graph.adjacency_matrix[i][j] >= 0)
            {
                out << graph.adjacency_matrix[i][j] << "\t";
            }
            else
            {
                out << "INF\t";
            }
        }
        out << endl;
    }
    return out;
}

#endif


//For more Projects
//Contact: +92 3495312852 || +92 3145520810  
// Thank you :)   