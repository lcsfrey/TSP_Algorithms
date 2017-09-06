#include "graph_path_trie.h"

Vertex_TrieNode::Vertex_TrieNode(Graph* t_graph,
                                 Vertex* t_vert_pointer,
                                 std::vector<bool> t_in_route,
                                 const int& size,
                                 int t_length) {
    m_in_route = t_in_route;
    // m_vertices = &t_graph->getVertices();
    // m_vert_pointer = t_vert_pointer;
    m_length_so_far = t_length;
    for (int i = 0; i < size; i++) {
        // if the i th node has not been visited
        if (!m_in_route[i]) {
            // visit node
            m_in_route[i] = true;

            // calculate the cost of moving to this node
            int change = t_graph->getEdgeWeight(t_vert_pointer->getID(), i);
            m_length_so_far += change;

            // create node with with the state of the tour if we had
            // visited that vertex next
            // length of tour in that state = m_length_so_far + change
            Vertex_TrieNode* t_node_pointer;
            t_node_pointer = new Vertex_TrieNode(t_graph,
                                                 &(t_graph->getVertices().at(i)),
                                                 m_in_route,
                                                 size,
                                                 m_length_so_far);

            // Add this node to the set of possible next
            m_potential_next_paths.push_back(t_node_pointer);

            // Necessary to mark it as false (unvisited) again as each
            // iteration through the for loop we want it to create a
            // potential path where only one new vertex (inPath[i]) is
            // visited.
            m_in_route[i] = false;
        }
    }
}

Graph_path_trie::Graph_path_trie(Graph *t_graph,
                                 const int t_size) : m_graph(t_graph), size(t_size) {
    for (int i = 0; i < size; i++)
        m_in_route.push_back(false);
    m_in_route[0] = true;
    std::vector<Vertex>* t_vertices_pointer = &t_graph->getVertices();
    Vertex* t_vertex_pointer = &(t_vertices_pointer->front());
    m_starting_vertex = new Vertex_TrieNode(t_graph, t_vertex_pointer, m_in_route, size, 0);
}
