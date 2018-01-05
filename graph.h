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

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <utility>
#include <set>
#include <map>

class Graph;
class Edge;

class Vertex {
 public:
  friend class Graph;
  friend class Edge;
  friend class VertexEuclid;

  Vertex(const int &t_id);
  void addEdge(const Vertex &other_vertex, const int &weight);

  std::vector<Edge> getEdges() { return out_edges; }
  const Edge* getEdge(const int &i) const { return &(out_edges.at(i)); }
  int getID() const { return id; }

 protected:
  std::vector<Edge> out_edges;
  const int id;
};


class VertexEuclid : public Vertex {
public:
  friend class Graph;
  friend class Edge;

  VertexEuclid(const int &t_x, const int &t_y, const int & t_id)
     : Vertex(t_id), x(t_x), y(t_y) { }

  void addEdge(const VertexEuclid &other_vertex);
  int getY() const { return y; }
  int getX() const { return x; }
protected:
  int calculateWeight(const VertexEuclid &t_to) const;
  const int x;
  const int y;
};


class Edge {
 public:
  friend class Graph;
  friend class Vertex;

  Edge(const int &t_to, const int &t_weight);
  Edge(const VertexEuclid &t_from, const VertexEuclid &t_to);

  int getTo() const { return to; }
  int getWeight() const { return weight; }

  bool operator> (const Edge &other_edge) const;

 protected:
  int calculateWeight(const VertexEuclid &t_from, const VertexEuclid &t_to) const;

  const int to;
  const int weight;
};


class Graph {
 public:
  Graph();
  explicit Graph(std::string file_name);
  explicit Graph(const std::vector<std::pair<int, int>> &coords);

  void addVertex(const int &t_vertex_id, const int &t_vertex_x, const int &t_vertex_y);
  void addVertex(const VertexEuclid &t_vertex);
  void addVertices(const std::vector<VertexEuclid> &t_vertices);

  const Vertex* getVertex(const int& id) const { return &m_vertices.at(id); }
  std::vector<VertexEuclid> *getVertices();
  int getEdgeWeight(const int& t_from, const int& t_to) const {
    return getVertex(t_from)->getEdge(t_to)->getWeight();
  }
  int getNumVertices() const { return size; }

  std::vector<int> getPrimMST();
  std::vector<int> getDijkstraPath(int starting_index);

  // calculates the length of the path connecting all nodes in t_route
  int calcPathLength(const std::vector<int> &t_route) const {
    int t_total_length = getEdgeWeight(t_route[0], t_route[1]);
    for (int i = 1; i < size - 1; i++) {
      t_total_length += getEdgeWeight(t_route[i], t_route[i+1]);
    }
    return t_total_length + getEdgeWeight(t_route[size - 1], t_route[0]);
  }

 private:
  // loads vertices stored in file
  void readFromFile(std::string file_name);

  std::vector<VertexEuclid> m_vertices;
  int size;
};

#endif  // GRAPH_H_
