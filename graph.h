#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>

class Graph;
class Edge;

class Vertex{
public:
    bool operator> (const Vertex &other_vertex) const;
    bool operator>= (const Vertex &other_vertex) const;
    bool operator< (const Vertex &other_vertex )const;
    bool operator<= (const Vertex &other_vertex) const;
    Vertex(int &t_x, int &t_y, int &t_id) : x(t_x), y(t_y), id(t_id) {}
    void addEdge(Vertex &other_vertex);
    int getY(){return y;}
    int getX(){return x;}
    int getID(){return id;}
    std::vector<Edge> getEdges(){
        return out_edges;
    }

    friend class Graph;
    friend class Edge;

protected:
    std::vector<Edge> out_edges;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> out_edge_heap;
    int x;
    int y;
    int id;
};

class Edge{
public:
    bool operator> (const Edge &other_edge) const;
    bool operator>= (const Edge &other_edge) const;
    bool operator< (const Edge &other_edge )const;
    bool operator<= (const Edge &other_edge) const;
    Edge(Vertex &t_from, Vertex &t_to) : from(t_from.id), to(t_to.id), weight(calculateWeight(t_from, t_to)){}
    Edge(int &t_from, int &t_to, int &t_weight) : from(t_from), to(t_to) , weight(t_weight) {}
    int getWeight(){
        return weight;
    }

    friend class Graph;
    friend class Vertex;

protected:
    int calculateWeight(Vertex &t_from, Vertex &t_to);
    int from;
    int to;
    int weight;
};

using namespace std;
class Graph
{

public:
    Graph();
    Graph(std::string file_name);
    void readFromFile(std::string file_name);
    void addVertex(Vertex &t_vertex);
    void printOrderedEdges(Vertex &t_vertex);
    vector<Vertex> getVertices();

    // returns a map parent[v.id] = u.id where the parent node of vertex v is vertex u
    vector<int> primMST();

    Vertex& getVertex(const int& id);

private:
    vector<Vertex> m_vertices;
    int size = 0;
};

#endif // GRAPH_H
