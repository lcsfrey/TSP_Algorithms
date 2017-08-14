#ifndef TSP_ALGO_NEAREST_NEIGHBOR_H
#define TSP_ALGO_NEAREST_NEIGHBOR_H
#include "graph.h"

class TSP_Algo_Nearest_Neighbor
{
public:
    TSP_Algo_Nearest_Neighbor(std::string &file_name) : m_graph(file_name){
        m_min_spanning_tree = m_graph.primMST();
        m_vertices = new vector<Vertex>(m_graph.getVertices());
    }

    int getCurrentFitness() const;

    vector<Vertex>* getRoute();
    void tick();

private:
    void calcFitness();
    int m_fitness = INT32_MAX;
    int m_last_fitness;
    vector<Vertex>* m_vertices;
    vector<Edge> m_route;
    vector<int> m_min_spanning_tree;
    Graph m_graph;

};

#endif // TSP_ALGO_NEAREST_NEIGHBOR_H
