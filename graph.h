/************************************************************************************
**                                                                                 **
**  MIT License                                                                    **
**                                                                                 **
**  Copyright (c) 2017 Lucas Frey                                                  **
**                                                                                 **
**  Permission is hereby granted, free of charge, to any person obtaining          **
**  a copy of this software and associated documentation files (the "Software"),   **
**  to deal in the Software without restriction, including without limitation      **
**  the rights to use, copy, modify, merge, publish, distribute, sublicense,       **
**  and/or sell copies of the Software, and to permit persons to whom the          **
**  Software is furnished to do so, subject to the following conditions:           **
**                                                                                 **
**  The above copyright notice and this permission notice shall be included        **
**  in all copies or substantial portions of the Software.                         **
**                                                                                 **
**  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS        **
**  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    **
**  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
**  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
**  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
**  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
**  SOFTWARE.                                                                      **
**                                                                                 **
************************************************************************************/

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
#include <utility>

class Graph;
class Edge;

class Vertex{
 public:
    friend class Graph;
    friend class Edge;

    Vertex(const int &t_x, const int &t_y, const int &t_id) : x(t_x), y(t_y), id(t_id) {}
    void addEdge(const Vertex &other_vertex);

    std::vector<Edge> getEdges() { return out_edges; }
    const Edge* getEdge(const int& i) { return &(out_edges.at(i)); }
    //int getEdgeWeight(const int& t_to) { return out_edges.at(t_to).getWeight(); }
    inline int getY() const { return y; }
    inline int getX() const { return x; }
    inline int getID() const { return id; }

 protected:
    std::vector<Edge> out_edges;
    const int x;
    const int y;
    const int id;
};


class Edge{
 public:
    friend class Graph;
    friend class Vertex;

    Edge(const Vertex &t_from, const Vertex &t_to) : to(t_to.id), weight(calculateWeight(t_from, t_to)) {}
    Edge(const int &t_to, const int &t_weight) : to(t_to) , weight(t_weight) {}

    inline int getTo() const { return to; }
    inline int getWeight() const { return weight; }

    bool operator> (const Edge &other_edge) const;

 protected:
    int calculateWeight(const Vertex &t_from, const Vertex &t_to);
    const int to;
    const int weight;
};


class Graph {
 public:
    explicit Graph(std::string file_name);
    explicit Graph(const std::vector<std::pair<int, int> > &coords);

    void addVertex(const int &t_vertex_id, const int &t_vertex_x, const int &t_vertex_y);
    void addVertex(const Vertex &t_vertex);
    void addVertices(const std::vector<Vertex> &t_vertices);

    // returns a map parent[v.id] = u.id where the parent node of vertex v is vertex u
    Vertex getVertex(const int& id);
    int getEdgeWeight(const int& t_from, const int& t_to) const;
    std::vector<Vertex> &getVertices();
    inline int getNumVertices() const {return size;}
    std::vector<int> getPrimMST();
    std::vector<int> getDijkstraPath(int starting_index);

 private:
    void readFromFile(std::string file_name);
    std::vector<Vertex> m_vertices;
    int size = 0;
};

#endif // GRAPH_H
