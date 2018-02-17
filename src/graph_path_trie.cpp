#include "../include/graph_path_trie.h"

Vertex_TrieNode::Vertex_TrieNode(Graph* t_graph,
    const VertexEuclid *t_vert_pointer, std::vector<bool> t_in_route,
    const int& size, int t_length) {

  m_in_route = t_in_route;
  m_length_so_far = t_length;
  for (int i = 0; i < size; i++) {
    // if the i th node has not been visited
    if (!m_in_route[i]) {
      // visit node
      m_in_route[i] = true;

      // calculate the cost of moving to this node
      m_length_so_far += t_graph->getEdgeWeight(t_vert_pointer->getID(), i);

      // create node with with the state of the tour if we had
      // visited that vertex next
      // length of tour in that state = m_length_so_far + change
      Vertex_TrieNode* t_node_pointer = nullptr;
      t_node_pointer = new Vertex_TrieNode(t_graph, t_graph->getVertex(i),
                                           m_in_route, size, m_length_so_far);

      // Add this node to the set of possible next
      m_potential_next_paths.push_back(t_node_pointer);

      // Necessary to mark it as false (unvisited) again as each iteration
      // through the for loop we want it to create a potential path where
      // only one new vertex (inPath[i]) is visited.
      m_in_route[i] = false;
    }
  }
}

Graph_path_trie::Graph_path_trie(Graph *t_graph, const int t_size)
    : m_graph(t_graph), size(t_size) {
  for (int i = 0; i < size; i++) m_in_route.push_back(false);
  m_in_route[0] = true;
  m_starting_vertex = new Vertex_TrieNode(t_graph, t_graph->getVertex(0),
                                          m_in_route, size, 0);
}
