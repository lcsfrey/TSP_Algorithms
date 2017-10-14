#ifndef TSP_Algo_Genetic_H_
#define TSP_Algo_Genetic_H_
#include <algorithm>
#include <queue>
#include <thread>

#include "graph.h"

// Traveling Salesperson (TSP) Genetic Algorithm
//    Algorithm that constructs a population of random route solutions,
//    recombining the best solutions to produce improved routes. As the
//    route solutions get more common (e.g. less variation between generations)
//    the probability that each new route will mutate (swap edges) increases.

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
    TSP_Algo_Genetic(Graph *t_graph, int population_size = 1000);

    void changePopulationSize(int population_size);

    // Uses current generation contained within m_chromosome_heap to produce
    // a new generation, replacing the old generation with the new one.
    void tick();

    // calls the tick method a number of times equal to num_generations
    void run(const int &num_generations = 5000);

    // returns fitness at the top of the heap
    int getCurrentFitness() const;

    // returns mutation probability at this generation
    double getMutationProbability() const;

    // returns the current best route
    std::vector<int> getRoute() const;

 protected:
    // fitness of the current generation
    int m_best_fitness;

    // fitness of the last generation
    int m_last_fitness;

    // size of the chromosome heap
    int m_population_size;

    // starting probability that a new generation will mutate (swap vertices)
    double m_mutation_probability;

    // min heap of route chromosomes with the fittest chromosome (the shortest
    // length route) at the top
    ChromosomeHeap m_chromosome_heap;

    // pointer to graph the algorithm works on
    const Graph* m_graph;

    // stores vertices of graph
    const std::vector<Vertex>* m_vertices;
};

class TSP_Algo_Genetic_Threaded {
 public:
     TSP_Algo_Genetic_Threaded(Graph* t_graph, int population_size = 1000);

     // inline void tick(TSP_Algo_Genetic* population) { population->tick(); }

     // move route solutions from one population to another
     void migrate(double m_migration_probability = .1);

     // create four threads running their own genetic algorithm
     void run(int num_generations = 5000);

     const TSP_Algo_Genetic* getPopulation(int &index) const;

     int getBestFitness();

 private:
     int m_best_fitness = INT32_MAX;
     std::vector<TSP_Algo_Genetic*> m_populations;
};

}  // namespace TSP_Algos

#endif  // TSP_algo_genetic_H_
