#ifndef TSP_ALGO_NEAREST_NEIGHBOR_H
#define TSP_ALGO_NEAREST_NEIGHBOR_H
#include "graph.h"

class TSP_Algo_Nearest_Neighbor
{
public:
    TSP_Algo_Nearest_Neighbor(Graph &t_graph, std::string &file_name) : m_graph(t_graph){
        m_route = new const vector<Vertex>(m_graph.getVertices());
    }

    int getCurrentFitness() const;
    vector<Vertex>* getRoute() const;
    int tick();

private:
    int m_fitness = INT32_MAX;
    int m_last_fitness;
    const vector<Vertex>* m_route;
    Graph m_graph;

};

#endif // TSP_ALGO_NEAREST_NEIGHBOR_H
