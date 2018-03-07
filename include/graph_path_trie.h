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

// Graph Path Trie
// Data structure that views the traveling salesman problem as a prefix tree,
// otherwise known as a trie. The structure creates a starting node, containing
// an array of node pointers to the next potential vertex that can be visited.
// This structure considers all permutations of the TSP route, so this method
// is technically no better than the brute force approach.

#ifndef GRAPH_PATH_TRIE_H_
#define GRAPH_PATH_TRIE_H_
#include "graph.h"
#include <vector>

class Vertex_TrieNode {
  //  t_graph : the graph we are using
  //  t_vert_pointer : pointer to vertex of the current node we are at
  //  t_in_route : array of booleans indicating which elements are already in final route
  //  size : number of total vertices
  //  t_length : length of tour if it ended here
 public:
  Vertex_TrieNode(Graph* t_graph, const VertexEuclid *t_vert_pointer,
                  std::vector<bool> t_in_route, const int size, int t_length);

  // member variables:
  //   m_ver_pointer : pointer to vertex that was visited by creating this node
  //   m_length_so_far : current length of route
  //   m_in_route : boolean array of which vertices are in the tour already
  //   m_potential_next_paths : vector of pointers to nodes we could look at visiting next
  //   m_vertices : pointer to the vector of vertices
  private:
  const Vertex* m_vert_pointer;
  int m_length_so_far;
  std::vector<bool> m_in_route;
  std::vector<Vertex_TrieNode*> m_potential_next_paths;
};

class Graph_path_trie {
 public:
  Graph_path_trie(Graph *t_graph, const int t_size);

 private:
  const Graph* m_graph;
  std::vector<bool> m_in_route;
  Vertex_TrieNode* m_starting_vertex;
  const int size;
};

#endif  // GRAPH_PATH_TRIE_H_
