#include "tsp_algo_genetic.h"
#include "tsp_algo_nearest_neighbors.h"
#include <iostream>

int TSP_Algo_Genetic::getCurrentFitness() const{
    return this->m_best_fitness;
}

std::vector<int> TSP_Algo_Genetic::getRoute() const {
    return this->m_best_route;
}

void TSP_Algo_Genetic::tick(){
    calcFitness();
    m_last_fitness = m_best_fitness;
    //m_fitness = TSP_Algos::calcPathLength(this->m_graph, m_best_route);
}

void TSP_Algo_Genetic::calcFitness() {
    int t_total_fitness = 0;
    int size = this->m_best_route.size();
    for(int i = 0; i < size - 1; i++){
        t_total_fitness += this->m_graph->getEdgeWeight(m_best_route[i], m_best_route[i+1]);
    }
     t_total_fitness += this->m_graph->getEdgeWeight(m_best_route[size-1], m_best_route[0]);
    m_best_fitness = t_total_fitness;
}
