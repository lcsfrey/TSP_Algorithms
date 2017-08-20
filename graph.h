#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <queue>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <functional>
#include <string>
#include <set>

class Graph;
class Edge;

class Vertex{
public:
    friend class Graph;
    friend class Edge;

    Vertex(int &t_x, int &t_y, int &t_id) : x(t_x), y(t_y), id(t_id) {}
    void addEdge(Vertex &other_vertex);

    inline int getY(){return y;}
    inline int getX(){return x;}
    inline int getID(){return id;}
    std::vector<Edge> getEdges(){return out_edges;}
    Edge* getEdge(const int& i){return &(out_edges.at(i));}

protected:
    std::vector<Edge> out_edges;
    int x;
    int y;
    int id;
};

class Edge{
public:
    friend class Graph;
    friend class Vertex;

    bool operator> (const Edge &other_edge) const;
//    bool operator>= (const Edge &other_edge) const;
//    bool operator< (const Edge &other_edge )const;
//    bool operator<= (const Edge &other_edge) const;
    Edge(Vertex &t_from, Vertex &t_to) : to(t_to.id), weight(calculateWeight(t_from, t_to)){}
    Edge( int &t_to, int &t_weight) : to(t_to) , weight(t_weight) {}

    inline int getTo()const {return to;}
    inline int getWeight() const {return weight;}

protected:
    int calculateWeight(Vertex &t_from, Vertex &t_to);
    int to;
    int weight;
};

using namespace std;
class Graph
{

public:
    Graph(std::string &file_name);
    Graph(std::vector<pair<int, int> > &coords);

    void addVertex(int &t_vertex_id, int &t_vertex_x, int &t_vertex_y);
    void addVertex(Vertex &t_vertex);
    void addVertices(vector<Vertex> &t_vertices);

    // returns a map parent[v.id] = u.id where the parent node of vertex v is vertex u
    Vertex getVertex(const int& id);
    vector<Vertex>& getVertices();
    inline int getNumVertices() {return size;}
    vector<int> primMST();

private:
    void readFromFile(std::string file_name);
    vector<Vertex> m_vertices;
    int size = 0;
};

#endif // GRAPH_H
