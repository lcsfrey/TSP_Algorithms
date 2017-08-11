#include "graph.h"

// Graph Implementations
Graph::Graph(std::string file_name){
    readFromFile(file_name);
}

void Graph::addVertex(Vertex &t_vertex){
    m_vertices.push_back(t_vertex);
    size++;
    for(int i = 0; i < size-1; i++){
       m_vertices.back().addEdge(m_vertices[i]);
    }
    for(int i = 0; i < size; i++){
        m_vertices[i].addEdge(m_vertices.back());
    }
}

void Graph::printOrderedEdges(Vertex &t_vertex){
    priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> t_queue(t_vertex.out_edge_heap);
    while(t_queue.size() > 0){
        Edge t_edge = t_queue.top();
        t_queue.pop();
        cout << "From: " << t_edge.from << endl;
        cout << "To: " << t_edge.to << endl;
        cout << "Weight: " << t_edge.weight << endl << endl;
    }
}

Vertex& Graph::getVertex(const int &id){
    return m_vertices.at(id);
}

vector<Vertex> Graph::getVertices(){
    return m_vertices;
}

vector<int> Graph::primMST(){

    struct Order{
        bool operator()(Edge* t_edge1, Edge* t_edge2){
            return *t_edge1 > *t_edge2;
        }
    };
    priority_queue<Edge*, std::vector<Edge*>, Order> t_queue;

    vector<bool> inMST(size, false);
    vector<int> key(m_vertices.size(), INT32_MAX);
    vector<int> parent(m_vertices.size(), -1);
    key[0] = 0;
    parent[0] = 0;
    t_queue.push(&m_vertices[0].out_edges[0]);
    while(t_queue.size() >0){
        Edge *t_vertex = t_queue.top();
        t_queue.pop();
        inMST[t_vertex->to] = true;
        for(Edge t_edge : m_vertices[t_vertex->to].out_edges){
            if(inMST[t_edge.to] == false && t_edge.weight < key[t_edge.to]){
                key[t_edge.to] = t_edge.weight;
                t_queue.push(&m_vertices[t_vertex->to].out_edges[t_edge.to]);
                parent[t_edge.to] = t_vertex->to;
            }
        }
    }
    for (int i = 1; i < size; ++i)
        printf("%d - %d\n", parent[i], i);
    return parent;
}

void Graph::readFromFile(std::string file_name){
    ifstream in_file(file_name);
    string str_num;
    int x = -1, y = -1, id = -1;
    if(!in_file.is_open()){
        std::cout << "File didn't open!" << endl;
        return;
    }

    while (getline(in_file,str_num)){
        if(str_num == "")
        {break;}
        stringstream stream(str_num);
        stream >> id;
        stream >> x;
        stream >> y;
        Vertex vertex_to_add(x, y, id);
        addVertex(vertex_to_add);
    }
    in_file.close();
}

// Vertex Implementations
void Vertex::addEdge(Vertex &other_vertex){
    Edge t_edge(*this, other_vertex);
    out_edges.push_back(t_edge);
    if(t_edge.weight != 0){
        out_edge_heap.push(t_edge);
    }
}

bool Vertex::operator> (const Vertex &other_vertex) const{
    return (this->out_edge_heap.top() > other_vertex.out_edge_heap.top());
}

bool Vertex::operator>= (const Vertex &other_vertex) const {
   return (this->out_edge_heap.top() >= other_vertex.out_edge_heap.top());
}

bool Vertex::operator< (const Vertex &other_vertex) const {
    return (this->out_edge_heap.top() < other_vertex.out_edge_heap.top());
}

bool Vertex::operator<= ( const Vertex &other_vertex) const {
    return (this->out_edge_heap.top() <= other_vertex.out_edge_heap.top());
}

// Edge implementations
int Edge::calculateWeight(Vertex &t_from, Vertex &t_to){
        int t_weight = -1;
        // FUNCTION CURRENTLY ONLY ROUNDS DOWN
        // TODO: MAKE FUNCTION ROUND UP OR DOWN
        if(t_from.id != t_to.id){
            t_weight = sqrt(pow((t_from.y - t_to.y), 2) + pow((t_from.x - t_to.x), 2));
        }
        else if(t_from.id == t_to.id){
            t_weight = 0;
        }
        return t_weight;
}

bool Edge::operator> (const Edge &other_edge) const{
    return (this->weight > other_edge.weight);
}

bool Edge::operator>= (const Edge &other_edge) const {
   return (this->weight >= other_edge.weight);
}

bool Edge::operator< (const Edge &other_edge) const {
    return (this->weight < other_edge.weight);
}

bool Edge::operator<= ( const Edge &other_edge) const {
    return (this->weight <= other_edge.weight);
}




