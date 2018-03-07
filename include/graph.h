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

#include "vertex.h"

class Graph {
 public:
  Graph();
  explicit Graph(std::string file_name, bool is_complete = true);
  explicit Graph(const std::vector<std::pair<int,int>> &coords,
                 bool is_complete = true);

  ~Graph() {}

  void addVertex(const int t_id);
  void addVertex(const int t_id, const int t_x, const int t_y);
  void addVertices(const std::vector<VertexEuclid> &t_vertices);

  void addEdge(const int from, const int to, bool bidirectional = true);
  void connectVertices(const std::vector<std::vector<bool>> &adj_matrix);
  void makeGraphComplete();

  bool hasEdge(const int from, const int to) const;

  void generateRandomDirectedGraphFile(std::string &file_name, int num_vertices,
                                       int upper_x_bound, int upper_y_bound,
                                       float edge_load_factor = .5);

  void generateRandomCompleteGraphFile(std::string &file_name, int num_vertices,
                                       int upper_x_bound, int upper_y_bound);

  // returns const pointer to vertex if id corresponds to
  // a vertex id, or nullptr if the vertex doesn't exist
  const VertexEuclid* getVertex(const int id) const;

  // returns const pointer to the vector m_vertices
  const std::vector<VertexEuclid> *getVertices() const;

  // returns edge weight if edge exists, or INT32_MAX if edge does not exist
  int getEdgeWeight(const int from, const int to) const;

  int getNumVertices() const { return size; }

  std::vector<int> getPrimMST();
  std::vector<int> getDijkstraPath(int starting_index);

  // calculates the length of the path connecting all nodes in t_route
  int calcPathLength(const std::vector<int> &t_route) const;

 protected:
  // loads vertices stored in file
  void readFromFile(std::string file_name);

  std::vector<VertexEuclid> m_vertices;
  int size;
  bool m_is_complete;
};

inline bool Graph::hasEdge(const int from, const int to) const {
  return m_is_complete ? true : getVertex(from)->hasEdge(to);
}

inline const VertexEuclid *Graph::getVertex(const int id) const {
  return 0 <= id && id < size ? &m_vertices.at(id) : nullptr;
}

inline int Graph::getEdgeWeight(const int from, const int to) const {
  return hasEdge(from, to) ? getVertex(from)->getEdgeWeight(to) : INT32_MAX;
}

inline int Graph::calcPathLength(const std::vector<int> &t_route) const {
  int t_total_length = getEdgeWeight(t_route[0], t_route[1]);
  for (int i = 1; i < size - 1; i++) {
    t_total_length += getEdgeWeight(t_route[i], t_route[i+1]);
  }
  return t_total_length + getEdgeWeight(t_route[size - 1], t_route[0]);
}


#endif  // GRAPH_H_
