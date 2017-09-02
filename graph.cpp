/************************************************************************************
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

#include "graph.h"

// Graph Implementations
Graph::Graph(std::string file_name) {
    readFromFile(file_name);
    m_vertices.shrink_to_fit();
    printf("Total vertices: %d\n", size);
}

Graph::Graph(const std::vector<std::pair<int, int> > &coords) {
    int size = coords.size();
    for (int i = 0; i < size; i++) {
        addVertex(i, coords[i].first, coords[i].second);
    }
}

void Graph::addVertex(const int &t_vertex_id, const int &t_vertex_x, const int &t_vertex_y) {
    Vertex t_vertex(t_vertex_x, t_vertex_y, t_vertex_id);
    addVertex(t_vertex);
}

void Graph::addVertex(const Vertex &t_vertex) {
    m_vertices.push_back(t_vertex);
    size++;
    for (int i = 0; i < size-1; i++) {
       m_vertices.back().addEdge(m_vertices[i]);
    }
    for (int i = 0; i < size; i++) {
        m_vertices[i].addEdge(m_vertices.back());
    }
}

void Graph::addVertices(const std::vector<Vertex> &t_vertices) {
    for (auto t_vertex : t_vertices) {
        addVertex(t_vertex);
    }
}

int Graph::getEdgeWeight(const int& t_from, const int& t_to) const {
    const Vertex* from_vertex = &m_vertices.at(t_from);
    return from_vertex->out_edges[t_to].getWeight();
}

Vertex Graph::getVertex(const int &id) {
    return m_vertices.at(id);
}

std::vector<Vertex>& Graph::getVertices() {
    return m_vertices;
}

std::vector<int> Graph::getPrimMST() {
    printf("Calculating minimum spanning tree...\n");
    auto start = std::chrono::high_resolution_clock::now();
    struct Order{
        bool operator()(Edge* t_edge1, Edge* t_edge2) {
            return *t_edge1 > *t_edge2;
        }
    };
    std::vector<bool> inMST(size, false);
    std::priority_queue<Edge*, std::vector<Edge*>, Order> t_queue;
    std::vector<int> key(m_vertices.size(), INT32_MAX);
    std::vector<int> parent(m_vertices.size(), -1);
    key[0] = 0;
    parent[0] = 0;
    t_queue.push(&m_vertices[0].out_edges[0]);
    while (t_queue.size() >0) {
        Edge *t_current_edge = t_queue.top();
        t_queue.pop();
        inMST[t_current_edge->to] = true;
        for (auto t_edge : m_vertices[t_current_edge->to].out_edges) {
            if (inMST[t_edge.to] == false && t_edge.weight < key[t_edge.to]) {
                key[t_edge.to] = t_edge.weight;
                t_queue.push(&m_vertices[t_current_edge->to].out_edges[t_edge.to]);
                parent[t_edge.to] = t_current_edge->getTo();
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
    std::vector<bool> inPath(size, false);
    std::vector<int> distances;

    distances[starting_index] = 0;
    inPath[starting_index] = true;
    return distances;
}

int Graph::calcPathLength(Graph* t_graph, const std::vector<int> &t_route) {
    int t_total_length = 0;
    int size = t_route.size() - 1;
    for (int i = 0; i < size - 1; i++) {
        t_total_length += t_graph->getEdgeWeight(t_route[i], t_route[i+1]);
    }
    t_total_length += t_graph->getEdgeWeight(t_route[size], t_route[0]);
    return t_total_length;
}

void Graph::readFromFile(std::string file_name) {
    std::ifstream in_file(file_name);
    std::string str_num;
    int x = -1, y = -1;
    int id = -1;
    if (!in_file.is_open()) {
        std::cout << "ERROR: The file " << file_name << " didn't open!" << std::endl;
        return;
    }

    while (getline(in_file, str_num)) {
        if (str_num == "")
        {break;}
        std::stringstream stream(str_num);
        stream >> id;
        stream >> x;
        stream >> y;
        if (id > 0 && id % 1000 == 0) {
            std::cout << "Loading vertex " << id << std::endl;
        }
        Vertex vertex_to_add(x, y, id);
        addVertex(vertex_to_add);
    }
    in_file.close();
}

// Vertex Implementations
void Vertex::addEdge(const Vertex &other_vertex) {
    out_edges.push_back(Edge(*this, other_vertex));
}

// Edge implementations
int Edge::calculateWeight(const Vertex &t_from, const Vertex &t_to) {
        int t_weight = -1;
        if (t_from.id != t_to.id) {
            float t_number = sqrt(pow((t_from.y - t_to.y), 2) + pow((t_from.x - t_to.x), 2));
            t_weight = round(t_number);
        } else {
            t_weight = 0;
        }
        return t_weight;
}

bool Edge::operator> (const Edge &other_edge) const {
    return (this->weight > other_edge.weight);
}
