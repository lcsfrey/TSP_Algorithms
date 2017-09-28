#ifndef TSP_Algo_Genetic_H_
#define TSP_Algo_Genetic_H_
#include "graph.h"
#include <algorithm>
#include <queue>
#include <ctime>

namespace TSP_Algos {

class TSP_Algo_Genetic
{
public:
    struct Chromosome {
        int m_route_fitness;
        std::vector<int> m_route;

        Chromosome(const Graph* t_graph, const std::vector<int> &t_route);
        void mutate(double t_probability);
        bool operator> (const Chromosome& other_chromosome) const;
    };
    // Min heap used to store Chromosomes where the top of the heap is the
    // Chromosome that is storing the best route and smallest route length.
    typedef std::priority_queue<Chromosome,
                                std::vector<Chromosome>,
                                std::greater<Chromosome>> ChromosomeHeap;
    Chromosome reproduce(const Chromosome& parent_1, const Chromosome& parent_2) const;

    //
    TSP_Algo_Genetic(const Graph *t_graph, int &Chromosome_size);
    // Uses current generation contained within m_chromosome_heap to produce
    // a new generation, replacing the old generation with the new one.
    void tick();
    // calls the tick method a number of times equal to num_generations
    void run(const int &num_generations=5000);

    int getCurrentFitness() const;
    double getMutationProbability() const;
    // returns the current best route
    std::vector<int> getRoute() const;

 protected:
    int m_best_fitness;
    int m_last_fitness;
    double m_mutation_probability;
    const std::vector<Vertex>* m_vertices;
    ChromosomeHeap m_chromosome_heap;
    const Graph* m_graph;
};

}  // namespace TSP_Algos

#endif  // TSP_algo_genetic_H_
