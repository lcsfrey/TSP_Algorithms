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

#ifndef VERTEX_H_
#define VERTEX_H_

#include "math.h"

#include <vector>
#include <utility>
#include <unordered_map>
#include <cstdint>

// used to store edge information
//  first int - stores the ID of the connected vertex
//  second int - stores the weight of the edge
using Edge = std::pair<int,int>;


// Vertex Declarations

class Vertex {
 public:
  Vertex() : id(-1) {}
  explicit Vertex(const Vertex &other) = default;
  Vertex(const int t_id) : id(t_id) {}

  virtual ~Vertex() = default;

  Vertex& operator=(const Vertex &other) = default;

  bool operator==(const Vertex &other) const;

  void addEdge(const Vertex &other_vertex, const int weight = 1);

  int getEdgeWeight(int to) const;

  bool hasEdge(int to) const { return out_edges.find(to) != out_edges.end(); }
  int getID() const { return id; }
  const std::unordered_map<int, int>* getEdges() const { return &out_edges; }
 protected:
  std::unordered_map<int, int> out_edges;
  int id;
};


// Vertex Implementations

inline bool Vertex::operator==(const Vertex &other) const {
  return id == other.id && out_edges == other.out_edges;
}

inline void Vertex::addEdge(const Vertex &other_vertex, const int weight) {
  out_edges[other_vertex.getID()] = weight;
}

inline int Vertex::getEdgeWeight(int to) const {
  const auto weight = out_edges.find(to);
  if (weight != out_edges.end())
    return out_edges.at(to);
  else
    return INT32_MAX;
}


// VertexEuclid Declarations

class VertexEuclid : public Vertex {
 public:
  VertexEuclid() : Vertex(), x(0), y(0) {}
  explicit VertexEuclid(const VertexEuclid &other) = default;
  explicit VertexEuclid(const int t_id) : Vertex(t_id), x(0), y(0) {}
  VertexEuclid(const int t_id, const int t_x, const int t_y)
     : Vertex(t_id), x(t_x), y(t_y) { }

  virtual ~VertexEuclid() = default;

  VertexEuclid& operator=(const VertexEuclid &other) = default;

  bool operator==(const VertexEuclid &other) const;

  void addEdge(const VertexEuclid &other_vertex);

  int getX() const { return x; }
  int getY() const { return y; }

protected:
  int calculateWeight(const VertexEuclid &t_to) const;
  int x;
  int y;
};

// VertexEuclid Emplementations

inline bool VertexEuclid::operator==(const VertexEuclid &other) const {
  return id == other.id && x == other.x &&
      y == other.y && out_edges == other.out_edges;
}

inline void VertexEuclid::addEdge(const VertexEuclid &other_vertex) {
  out_edges[other_vertex.id] = calculateWeight(other_vertex);
}

inline int VertexEuclid::calculateWeight(const VertexEuclid &t_to) const {
  if (id != t_to.id) {
    return round(sqrt(pow((y - t_to.y), 2) + pow((x - t_to.x), 2)));
  } else {
    return 0;
  }
}

#endif // VERTEX_H_
