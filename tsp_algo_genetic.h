#ifndef TSP_Algo_Genetic_H_
#define TSP_Algo_Genetic_H_
#include "graph.h"
#include <algorithm>
#include <queue>
#include <ctime>

// Traveling Sales Person Genetic Algorithm
// Algorithm that constructs random population of route solutions, recombining
// best solutions to produce improved routes. As the routes of species get
// more common, the probability that each new route will mutate(swap nodes)
// increases.

namespace TSP_Algos {

class TSP_Algo_Genetic {
 public:

    // Stores independent TSP route and fitness
    struct Chromosome {
        // Chromosome variables
        int m_route_fitness;
        std::vector<int> m_route;

        // Constructs chromosome using route
        Chromosome(const Graph* graph, const std::vector<int> &route);

        // has a probability chance of swapping two random vertices in route
        void mutate(double probability);

        // returns the if this chromosome fitness is greater than
        // other_chromosome's fitness
        bool operator> (const Chromosome& other_chromosome) const;
    };

    // Min heap used to store Chromosomes where the top of the heap is the
    // Chromosome that is storing the best route and smallest route length.
    typedef std::priority_queue<Chromosome,
                                std::vector<Chromosome>,
                                std::greater<Chromosome>> ChromosomeHeap;

    // returns the child Chromosome of two parent chromosomes
    // input parent_1 gives child random subroute
    //       parent_1 gives child remaining vertices needed to visit
    Chromosome reproduce(const Chromosome& parent_1,
                         const Chromosome& parent_2) const;

    // Constructor that adds chromosome_size random route chromosomes
    TSP_Algo_Genetic(Graph *t_graph, int &Chromosome_size);

    // Uses current generation contained within m_chromosome_heap to produce
    // a new generation, replacing the old generation with the new one.
    void tick();

    // calls the tick method a number of times equal to num_generations
    void run(const int &num_generations=5000);

    // returns fitness at the top of the heap
    int getCurrentFitness() const;

    // returns mutation probability at this generation
    double getMutationProbability() const;

    // returns the current best route
    std::vector<int> getRoute() const;

 protected:
    // fitness at current generation
    int m_best_fitness;

    // fitness last generation
    int m_last_fitness;

    // starting probability that a new generation will mutate (swap vertices)
    double m_mutation_probability;

    // min heap of route chromosomes with the fittest chromosome at the top
    ChromosomeHeap m_chromosome_heap;

    // pointer to graph the algorithm works on
    const Graph* m_graph;

    // stores vertices of graph
    const std::vector<Vertex>* m_vertices;
};

}  // namespace TSP_Algos

#endif  // TSP_algo_genetic_H_
