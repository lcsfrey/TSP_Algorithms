#include "tsp_algo_genetic.h"
#include <iostream>

int TSP_Algo_Genetic::getCurrentFitness() const{
    return this->m_fitness;
}

vector<Edge> TSP_Algo_Genetic::getRoute(){
    return this->m_route;
}

void TSP_Algo_Genetic::tick(){
    calcFitness();
}

void TSP_Algo_Genetic::calcFitness(){
    m_last_fitness = m_fitness;
    int t_total_fitness = 0, t_current_fitness = 0;
    int size = this->m_route.size();
    for(int i = 0; i < size; i++){
        std::vector<Edge> edges = m_vertices->at(i).getEdges();
        t_current_fitness = edges.at(m_min_spanning_tree[i]).getWeight();
        t_total_fitness += t_current_fitness;
    }
    m_fitness = t_total_fitness;

}
