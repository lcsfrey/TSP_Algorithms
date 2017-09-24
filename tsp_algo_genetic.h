#ifndef TSP_Algo_Genetic_H_
#define TSP_Algo_Genetic_H_
#include "graph.h"
#include <algorithm>
#include <queue>
#include <ctime>

namespace TSP_Algos{

class TSP_Algo_Genetic
{
public:
    TSP_Algo_Genetic(Graph* t_graph, int &Chromosome_size);
    int getCurrentFitness() const;
    double getMutationProbability() const;
    std::vector<int> getRoute() const;
    void tick();

    struct Chromosome {
            int m_route_fitness;
            std::vector<int> m_route;

            Chromosome(const Graph* t_graph, const std::vector<int> &t_route);
            void mutate(double t_probability);
            bool operator> (const Chromosome& other_chromosome) const;
    };
    Chromosome reproduce(const Chromosome& parent_1, const Chromosome& parent_2) const;

 protected:
    int m_best_fitness;
    int m_last_fitness;
    double m_mutation_probability;
    const std::vector<Vertex>* m_vertices;
    std::priority_queue<Chromosome, std::vector<Chromosome>, std::greater<Chromosome>> m_chromosome_heap;
    Graph* m_graph;
};

}

#endif  // TSP_algo_genetic_H_
