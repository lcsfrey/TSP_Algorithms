#ifndef GRAPH_PATH_TRIE_H_
#define GRAPH_PATH_TRIE_H_
#include "graph.h"


class Vertex_TrieNode {
    //  t_graph : the graph we are using
    //  t_vert_pointer : pointer to vertex of the current node we are at
    //  inPath : array of booleans indicating which elements are already in array
    //  size : number of total vertices
    //  t_length : length of tour if it ended here
    public:
        Vertex_TrieNode(Graph* t_graph,
                    Vertex* t_vert_pointer,
                    bool inPath[],
                    const int& size,
                    int t_length) : m_vertices(&t_graph->getVertices()) {

        m_vert_pointer = t_vert_pointer;
        //this->m_vertices = &t_graph->getVertices();
        m_length_so_far = t_length;
        // reinitialize visited array
        bool t_in_path[size];
        for (int i = 0; i < size; i++) {
            t_in_path[i] = inPath[i];
        }

        for (int i = 0; i < size; i++) {
            // if the i th node has not been visited
            if (!inPath[i]) {

                // visit node
                m_in_path[i] = true;

                // calculate the cost of moving to this node
                int change = t_vert_pointer->getEdge(i)->getWeight();

                // create node with with the state of the tour if we had
                // visited that vertex next
                // length of tour in that state = = m_length_so_far + change
                Vertex_TrieNode* t_node_pointer;
                t_node_pointer = new Vertex_TrieNode(t_graph,
                                                     &m_vertices->at(i),
                                                     m_in_path,
                                                     size,
                                                     m_length_so_far + change);

                // Add this node to the set of possible next
                m_potential_next_paths.push_back(t_node_pointer);

                // Necessary tp mark it as false (unvisited) again as each
                // iteration through the for loop we want it to create a
                // potential path where only one new vertex (inPath[i]) is
                // visited.
                m_in_path[i] = false;
            }
        }
    }
    private:
    const Vertex* m_vert_pointer;
    int m_length_so_far = 0;
    bool* m_in_path;
    std::vector<Vertex_TrieNode*> m_potential_next_paths;
    std::vector<Vertex>* m_vertices;
};

class Graph_path_trie {
 public:
        Graph_path_trie(Graph *t_graph,
                        const int& t_size) : m_graph(t_graph), size(t_size){

                for (int i = 0; i < size; i++) {
                    m_in_path = new bool[size];
                    for (int i = 0; i < size; i++) {
                        m_in_path[i] = false;
                    }
                    m_in_path[i] = true;
                    std::vector<Vertex>* t_vertices_pointer = &t_graph->getVertices();
                    Vertex* t_vertex_pointer = &t_vertices_pointer->at(i);
                    Vertex_TrieNode* t_vertex_trie_pointer = new Vertex_TrieNode(t_graph, t_vertex_pointer, m_in_path, size, 0);
                    m_starting_vertex.push_back(t_vertex_trie_pointer);

                    m_in_path[i] = false;

                //m_in_path = new bool[size];
               // m_starting_vertex.push_back(new Vertex_TrieNode(t_graph, &t_graph->getVertex(i), m_in_path, size, 0));

           }
        }

 private:
        Graph* m_graph;
        bool *m_in_path;
        std::vector<Vertex_TrieNode*> m_starting_vertex;
        const int size;
};

#endif  // GRAPH_PATH_TRIE_H_
