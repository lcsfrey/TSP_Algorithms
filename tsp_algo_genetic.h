#ifndef TSP_Algo_Genetic_H
#define TSP_Algo_Genetic_H
#include "graph.h"

class TSP_Algo_Genetic
{
public:
    TSP_Algo_Genetic(std::string &file_name) : m_graph(file_name){
        m_min_spanning_tree = m_graph.primMST();
        m_vertices = new vector<Vertex>(m_graph.getVertices());
    }

    int getCurrentFitness() const;

    vector<Edge> getRoute();
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

#endif // TSP_algo_genetic_H
