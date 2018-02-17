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

#include <chrono>
#include <queue>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <tuple>

#include "graph.h"

// used to store edge information
//  first int - stores the ID of the connected vertex
// second int - stores the weight of the edge
using Edge = std::pair<int, int>;

// Graph Implementations
Graph::Graph() : size(0) {}

Graph::Graph(std::string file_name, bool is_complete)
    : size(0), m_is_complete(is_complete) {
  readFromFile(file_name);
  m_vertices.shrink_to_fit();
}

Graph::Graph(const std::vector<Edge> &coords, bool is_complete)
    : size(coords.size()), m_is_complete(is_complete) {
  for (int i = 0; i < size;i++)
    addVertex(i, coords[i].first, coords[i].second);
}

void Graph::addVertex(const int &t_id) {
  m_vertices.push_back(VertexEuclid(t_id));
  size++;
}

void Graph::addVertex(const int &t_id, const int &t_x, const int &t_y) {
  m_vertices.push_back(VertexEuclid(t_id, t_x, t_y));
  size++;
}

void Graph::generateRandomDirectedGraphFile(std::string &file_name, int num_vertices,
                                            int upper_x_bound, int upper_y_bound,
                                            float edge_load_factor) {
  srand(time(0));
  std::ofstream out_file(file_name);
  for (int from = 0; from < num_vertices; from++) {
    out_file << from << " "
             << rand() % upper_x_bound << " "
             << rand() % upper_y_bound << "\n";
  }

  out_file << "\n";

  float load_factor = edge_load_factor;
  for (int from = 0; from < num_vertices; from++) {
    for (int to = 0; to < num_vertices; to++) {
      if (from != to)
        out_file << (((rand() % 100) < load_factor) ? "1" : "0") << " ";
      else
        out_file << "0 ";
    }
    out_file << "\n";
  }
  out_file.close();
}

void Graph::generateRandomCompleteGraphFile(std::string &file_name, int n,
                                            int upper_x_bound, int upper_y_bound) {
  srand(time(0));
  std::ofstream out_file(file_name);
  for (int from = 0; from < n; from++) {
    int x = rand() % upper_x_bound;
    int y = rand() % upper_y_bound;
    out_file << from << " " << x << " " << y << "\n";
  }

  out_file << "\n";

  for (int from = 0; from < n; from++) {
    for (int to = 0; to < n; to++) {
      if (from != to)
        out_file << "1 ";
      else
        out_file << "0 ";
    }
    out_file << "\n";
  }
  out_file.close();
}

const std::vector<VertexEuclid>* Graph::getVertices() const {
  return &m_vertices;
}

// returns an array of the form parent[current_id] = parent_id
// where all edges current_id <-> parent_id form the minimum spanning tree
std::vector<int> Graph::getPrimMST() {
  printf("Calculating minimum spanning tree...\n");
  auto start = std::chrono::high_resolution_clock::now();

  // initial variables:
  //   start - record of what time the algorithm was started
  //   edge_queue - min heap of edges with the smallest edge on top
  //   in_mst - vector with indeces corresponding to vertex ids with a value of
  //            true if the vertex is in the MST and false if it is not
  //   key - vector with indeces corresponding to vertex ids wih values
  //         corresponding to smallest edge weight found to that vertex
  //
  //   return value:
  //   parent - vector with indeces corresponding to vertex ids and values
  //            corresponding to a vertex id it is connected to

  struct Order {
    bool operator()(const Edge& edge1, const Edge& edge2) {
      return edge1.second > edge2.second;
    }
  };

  std::priority_queue<Edge, std::vector<Edge>, Order> edge_queue;

  std::vector<bool> in_mst(size, false);
  std::vector<int> key(size, INT32_MAX);
  std::vector<int> parent(size, -1);

  key[0] = 0;
  parent[0] = 0;
  edge_queue.push(Edge(0, 0));
  while (edge_queue.size() > 0) {

    // pop of the next shortest edge that can be added and add it to MST
    const Edge current_edge = edge_queue.top();
    edge_queue.pop();
    in_mst[current_edge.first] = true;

    // for all edges connected to the next vertex, if the successor node is not
    // in MST and the weight of that edge is the shortest edge we've seen so far
    // to that vertex, add that edge to the priority queue and mark where it was
    // to and where it was from;
    for (const Edge &next_edge : *getVertex(current_edge.first)->getEdges()) {
      if (!in_mst[next_edge.first] && next_edge.second < key[next_edge.first]) {
        key[next_edge.first] = next_edge.second;
        edge_queue.push(next_edge);
        parent[next_edge.first] = current_edge.first;
      }
    }
  }
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  printf("Minimum spanning tree took: %f seconds\n", elapsed.count());
  printf("----------------------------------------\n");
  return parent;
}

std::vector<int> Graph::getDijkstraPath(int starting_index) {
  printf("Calculating Dijkstra's Shortest Path...\n");

  std::vector<bool> in_path(size, false);
  std::vector<int> distance(size, INT32_MAX);
  std::vector<int> parent(size);

  distance[starting_index] = 0;
  parent[starting_index] = starting_index;

  for (int count = 0, min = INT32_MAX, min_id = 0; count < size - 1; count++) {
    for (int id = 0; id < size; id++) {
      if (!in_path[id] && distance[id] < min) {
        min = distance[id];
        min_id = id;
      }
    }

    in_path[min_id] = true;
    for (int id = 0; id < size; id++) {
      int next_edge_weight = getEdgeWeight(min_id, id);
      if (next_edge_weight != INT32_MAX && !in_path[id] &&
          distance[min_id] + next_edge_weight < distance[id]) {
        parent[id] = min_id;
        distance[id] = distance[min_id] + getEdgeWeight(min_id, id);
      }
    }
  }
  return parent;

}

void Graph::readFromFile(std::string file_name) {
  std::ifstream in_file(file_name);
  if (!in_file.is_open()) {
    std::cerr << "ERROR: The file " << file_name << " didn't open!\n";
    return;
  }

  std::string str_num;
  while (getline(in_file, str_num) && str_num != "") {
    std::stringstream stream(str_num);

    // read in single vertex from file and add it to graph
    int x = -1, y = -1, id = -1;
    stream >> id >> x >> y;
    addVertex(id, x, y);

    if (id > 0 && id % 1000 == 0) printf("Loading vertex %d\n", id);
  }

  std::vector<std::vector<bool>> adj_matrix(size, std::vector<bool>(size, true));

  if (m_is_complete) {
    makeGraphComplete();
  } else {
    for(int from = 0; from < size; from++) {
      for (int to = 0; to < size; to++) {
        bool connection = false;
        in_file >> connection;
        adj_matrix[from][to] = connection;
      }
    }
  }

  connectVertices(adj_matrix);
  printf("Total vertices: %d\n", size);
  in_file.close();
}

void Graph::connectVertices(const std::vector<std::vector<bool>> &adj_matrix) {
  for (int from = 0, size = adj_matrix.size(); from < size; from++) {
    for (int to = 0; to < size; to++) {
      if (adj_matrix[from][to] == true) m_vertices[from].addEdge(m_vertices[to]);
    }
  }
}

void Graph::makeGraphComplete() {
  std::vector<std::vector<bool>> connections(size, std::vector<bool>(size, true));
  connectVertices(connections);
  m_is_complete = true;
}
