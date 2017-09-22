#include "tsp_algo_genetic.h"
#include "tsp_algo_nearest_neighbors.h"
#include <iostream>

namespace TSP_Algos {

int TSP_Algo_Genetic::getCurrentFitness() const{
    return this->m_best_fitness;
}

double TSP_Algo_Genetic::getMutationProbability() const {
    return this->m_mutation_probability;
}

std::vector<int> TSP_Algo_Genetic::getRoute() const {
    return this->m_chromosome_heap.top().m_route;
}

void TSP_Algo_Genetic::tick(){
    std::priority_queue<Chromosome, std::vector<Chromosome>, std::greater<Chromosome>> temp_chromosome_heap;
    Chromosome best_chromosome = m_chromosome_heap.top();
    temp_chromosome_heap.push(best_chromosome);
    int iterations = m_chromosome_heap.size() / 4;
    int children = 6;
    int interval = iterations / children;

    while (iterations > 0 && children >= 0) {
        Chromosome parent_1 = m_chromosome_heap.top();
        m_chromosome_heap.pop();
        Chromosome parent_2 = m_chromosome_heap.top();
        m_chromosome_heap.pop();
        Chromosome parent_3 = m_chromosome_heap.top();
        m_chromosome_heap.pop();
        Chromosome parent_4 = m_chromosome_heap.top();
        m_chromosome_heap.pop();
        int i = interval;
        while (iterations > 0 && i > 0) {
            temp_chromosome_heap.push(reproduce(parent_1, parent_2));
            temp_chromosome_heap.push(reproduce(parent_2, parent_3));
            temp_chromosome_heap.push(reproduce(parent_3, parent_4));
            temp_chromosome_heap.push(reproduce(parent_4, parent_1));
            iterations--;
            i--;
        }
        children--;
    }
    m_chromosome_heap = temp_chromosome_heap;
    int current_fitness = m_chromosome_heap.top().m_route_fitness;
    if (m_best_fitness == current_fitness) {
        if (m_mutation_probability < .6) {
            m_mutation_probability += .005;
        }
    } else {
        if (current_fitness < m_best_fitness) {
            m_last_fitness = m_best_fitness;
            m_best_fitness = current_fitness;
        }
        if (m_mutation_probability >= .35) {
            m_mutation_probability -= .1;
        }
    }
}

}
