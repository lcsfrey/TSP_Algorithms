#include "tsp_algo_genetic.h"
#include "tsp_algo_nearest_neighbors.h"
#include <iostream>

namespace TSP_Algos {

TSP_Algo_Genetic::TSP_Algo_Genetic(Graph *t_graph, int &Chromosome_size) : m_graph(t_graph) {
    srand(time(0));
    m_vertices = new std::vector<Vertex>(m_graph->getVertices());
    m_best_fitness = INT32_MAX;
    m_last_fitness = 0;
    m_mutation_probability = .25;
    std::priority_queue<Chromosome, std::vector<Chromosome>, std::greater<Chromosome>> temp_heap;

    // creates random Chromosomes and stores the best Chromosomes in min heap
    std::vector<int> t_route(m_vertices->size());
    std::iota(t_route.begin(), t_route.end(), 0);
    for(int i = 0; i < 30000; i++) {
        std::shuffle(t_route.begin(), t_route.end(), std::mt19937{std::random_device{}()});
        temp_heap.push(Chromosome(t_graph, t_route));
    }
    for (int i = 0; i < Chromosome_size; i++) {
        Chromosome candidate = temp_heap.top();
        m_chromosome_heap.push(candidate);
        temp_heap.pop();
    }
}

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
        if (m_mutation_probability < .75) {
            m_mutation_probability += .005;
        }
    } else {
        if (current_fitness < m_best_fitness) {
            m_last_fitness = m_best_fitness;
            m_best_fitness = current_fitness;
        }
        if (m_mutation_probability >= .30) {
            m_mutation_probability -= .05;
        }
    }
}

TSP_Algo_Genetic::Chromosome TSP_Algo_Genetic::reproduce(const TSP_Algo_Genetic::Chromosome &parent_1, const TSP_Algo_Genetic::Chromosome &parent_2) const {
    int size = m_vertices->size();
    int size_from_parent_1 = rand() % size;
    int offset_from_parent_1 = rand() % (size - size_from_parent_1);
    std::vector<int> t_child;
    std::vector<bool> in_path(size, false);
    for (int i = offset_from_parent_1; i < size_from_parent_1 + offset_from_parent_1; i++) {
        t_child.push_back(parent_1.m_route[i]);
        in_path[parent_1.m_route[i]] = true;
    }
    for (int i = 0; i < size; i++) {
        if (!in_path[parent_2.m_route[i]]) {
            t_child.push_back(parent_2.m_route[i]);
        }
    }
    Chromosome child_chromosome(m_graph, t_child);
    child_chromosome.mutate(m_mutation_probability);
    child_chromosome.m_route_fitness = m_graph->calcPathLength(child_chromosome.m_route);
    return child_chromosome;
}

TSP_Algo_Genetic::Chromosome::Chromosome(const Graph *t_graph, const std::vector<int> &t_route) : m_route(t_route) {
    m_route_fitness = t_graph->calcPathLength(m_route);
}

void TSP_Algo_Genetic::Chromosome::mutate(double t_probability) {
    if((double) rand() / RAND_MAX <= t_probability) {
        int size = m_route.size();
        std::swap(m_route[rand() % size], m_route[rand() % size]);
        mutate(t_probability - .005);
    }
}

bool TSP_Algo_Genetic::Chromosome::operator >(const Chromosome& other_chromosome) const{
    return m_route_fitness > other_chromosome.m_route_fitness;
}

}
