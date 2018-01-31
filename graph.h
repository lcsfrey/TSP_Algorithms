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
#include <unordered_map>

// used to store edge information
//  first int - stores the ID of the connected vertex
// second int - stores the weight of the edge
using Edge = std::pair<int,int>;

class Vertex {
 public:
  explicit Vertex(const int &t_id);
  void addEdge(const Vertex &other_vertex, const int weight = 1);

  // returns the edged weight
  int getEdgeWeight(int to) const;

  bool hasEdge(int to) const { return out_edges.find(to) != out_edges.end(); }
  int getID() const { return id; }
  const std::unordered_map<int, int>* getEdges() const { return &out_edges; }

 protected:
  std::unordered_map<int, int> out_edges;
  const int id;
};

class VertexEuclid : public Vertex {
 public:
  explicit VertexEuclid(const int& t_id) : Vertex(t_id), x(0), y(0) {}
  VertexEuclid(const int & t_id, const int &t_x, const int &t_y)
     : Vertex(t_id), x(t_x), y(t_y) { }

  void addEdge(const VertexEuclid &other_vertex);

  int getX() const { return x; }
  int getY() const { return y; }

protected:
  int calculateWeight(const VertexEuclid &t_to) const;
  const int x;
  const int y;
};

inline int Vertex::getEdgeWeight(int to) const {
  const auto weight = out_edges.find(to);
  if (weight != out_edges.end())
    return weight->second;
  else
    return INT32_MAX;
}


class Graph {
 public:
  Graph();
  explicit Graph(std::string file_name);
  explicit Graph(const std::vector<Edge> &coords);

  ~Graph() {}

  void addVertex(const int &t_id);
  void addVertex(const int &t_id, const int &t_x, const int &t_y);
  void addVertices(const std::vector<VertexEuclid> &t_vertices);

  void generateRandomDirectedGraphFile(std::string &file_name, int num_vertices,
                                       int upper_x_bound, int upper_y_bound);

  void generateRandomCompleteGraphFile(std::string &file_name,int num_vertices,
                                       int upper_x_bound, int upper_y_bound);

  // returns const pointer to vertex if id is a valid size or nullptr if not
  const VertexEuclid* getVertex(const int& id) const {
    return 0 <= id && id < size ? &m_vertices.at(id) : nullptr;
  }

  // returns const pointer to the vector m_vertices
  const std::vector<VertexEuclid> *getVertices() const;

  // returns edge weight if edge exists, or INT32_MAX if edge does not exist
  int getEdgeWeight(const int& from, const int& to) const {
    return hasEdge(from, to) ? getVertex(from)->getEdgeWeight(to) : INT32_MAX;
  }

  int getNumVertices() const { return size; }

  std::vector<int> getPrimMST();
  std::vector<int> getDijkstraPath(int starting_index);

  // calculates the length of the path connecting all nodes in t_route
  int calcPathLength(const std::vector<int> &t_route) const;

 protected:
  // loads vertices stored in file
  void readFromFile(std::string file_name);

  void connectVertices(const std::vector<std::vector<bool> > &adj_matrix);

  bool hasEdge(const int& from, const int& to) const {
    return getVertex(from)->hasEdge(to);
  }

  std::vector<VertexEuclid> m_vertices;
  int size;
};

inline int Graph::calcPathLength(const std::vector<int> &t_route) const {
  int t_total_length = getEdgeWeight(t_route[0], t_route[1]);
  for (int i = 1; i < size - 1; i++) {
    t_total_length += getEdgeWeight(t_route[i], t_route[i+1]);
  }
  return t_total_length + getEdgeWeight(t_route[size - 1], t_route[0]);
}


#endif  // GRAPH_H_
