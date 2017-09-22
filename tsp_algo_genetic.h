#ifndef TSP_Algo_Genetic_H
#define TSP_Algo_Genetic_H
#include "graph.h"
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <ctime>

namespace TSP_Algos{

class TSP_Algo_Genetic
{
public:
    TSP_Algo_Genetic(Graph* t_graph, int &Chromosome_size) : m_graph(t_graph) {
        srand(time(0));
        m_vertices = new std::vector<Vertex>(m_graph->getVertices());
        m_best_fitness = INT32_MAX;
        m_last_fitness = 0;
        m_mutation_probability = .25;
        std::priority_queue<Chromosome, std::vector<Chromosome>, std::greater<Chromosome>> temp_heap;

        // creates random Chromosomes and stores the best Chromosomes in min heap
        std::vector<int> t_route(m_vertices->size());
        std::iota(t_route.begin(), t_route.end(), 0);
        for(int i = 0; i < 50000; i++) {
            std::shuffle(t_route.begin(), t_route.end(), std::mt19937{std::random_device{}()});
            temp_heap.push(Chromosome(t_graph, t_route));
        }
        for (int i = 0; i < Chromosome_size; i++) {
            Chromosome candidate = temp_heap.top();
            m_chromosome_heap.push(candidate);
            temp_heap.pop();
        }
    }

    int getCurrentFitness() const;
    double getMutationProbability() const;
    std::vector<int> getRoute() const;
    void tick();

    struct Chromosome {
            Chromosome(const Graph* t_graph, const std::vector<int> &t_route) : m_route(t_route) {
                m_route_fitness = t_graph->calcPathLength(m_route);
            }
            void mutate(double t_probability) {
                if((double) rand() / RAND_MAX <= t_probability) {
                    int size = m_route.size();
                    std::swap(m_route[rand() % size], m_route[rand() % size]);
                    mutate(t_probability - .01);
                }
            }
            bool operator> (const Chromosome& other_chromosome) const {
                return m_route_fitness > other_chromosome.m_route_fitness;
            }
            int m_route_fitness;
            std::vector<int> m_route;
    };
    Chromosome reproduce(const Chromosome& parent_1, const Chromosome& parent_2) {
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

 protected:
    int m_best_fitness;
    int m_last_fitness;
    double m_mutation_probability;
    const std::vector<Vertex>* m_vertices;
    std::priority_queue<Chromosome, std::vector<Chromosome>, std::greater<Chromosome>> m_chromosome_heap;
    Graph* m_graph;

};

}

#endif // TSP_algo_genetic_H
