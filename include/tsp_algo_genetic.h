/************************************************************************************
**                                                                                 **
**  MIT License                                                                    **
**                                                                                 **
**  Copyright (c) 2017 Lucas Frey                                                  **
**                                                                                 **
**  Permission is hereby granted, free of charge, to any person obtaining          **
**  a copy of this software and associated documentation files (the "Software"),   **
**  to deal in the Software without restriction, including without limitation      **
**  the rights to use, copy, modify, merge, publish, distribute, sublicense,       **
**  and/or sell copies of the Software, and to permit persons to whom the          **
**  Software is furnished to do so, subject to the following conditions:           **
**                                                                                 **
**  The above copyright notice and this permission notice shall be included        **
**  in all copies or substantial portions of the Software.                         **
**                                                                                 **
**  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS        **
**  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    **
**  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
**  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
**  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
**  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
**  SOFTWARE.                                                                      **
**                                                                                 **
************************************************************************************/

#ifndef TSP_Algo_Genetic_H_
#define TSP_Algo_Genetic_H_
#include <algorithm>
#include <queue>
#include <thread>

#include "graph.h"

// Traveling Salesperson (TSP) Genetic Algorithm
//  Algorithm that constructs a population of random route solutions,
//  recombining the best solutions to produce improved routes. As the
//  route solutions get more common (e.g. less variation between generations)
//  the probability that each new route will mutate (swap edges) increases.

namespace TSP_Algos {

class TSP_Algo_Genetic {
 public:
  // stores independent TSP route and fitness
  struct Chromosome {
    // Chromosome variables
    std::vector<int> m_route;
    int m_route_fitness;

    // constructs Chromosome using route
    Chromosome(const Graph* graph, const std::vector<int> &route);

    // has a probability chance of swapping two random vertices in route
    void mutate(double probability);

    // returns true if this chromosome fitness is greater than
    // other_chromosome's fitness
    bool operator> (const Chromosome& other_chromosome) const;
  };

  // min heap used to store Chromosomes where the top of the heap is the
  // Chromosome that is storing the best route and smallest route length.
  typedef std::priority_queue<Chromosome,
                              std::vector<Chromosome>,
                              std::greater<Chromosome>> ChromosomeHeap;

  // returns the child Chromosome of two parent chromosomes
  // input parent_1 gives child random subroute
  //     parent_2 gives child remaining vertices needed to visit
  Chromosome reproduce(const Chromosome& parent_1,
                       const Chromosome& parent_2) const;

  // constructor that adds chromosome_size random route chromosomes
  TSP_Algo_Genetic(Graph *t_graph, int population_size = 1000);

  // changes the number of Chromosomes stored in m_chromosome_heap
  void changePopulationSize(int population_size);

  // uses current generation contained within m_chromosome_heap to produce
  // a new generation, replacing the old generation with the new one.
  void tick();

  // calls the tick method a number of times equal to num_generations
  void run(const int num_generations = 5000, bool display_status = true);

  // returns the current best route
  std::vector<int> getRoute() const;

  // returns fitness at the top of the heap
  inline int getCurrentFitness() const { return m_best_fitness; }

  // returns mutation probability at this generation
  inline double getMutationProbability() const;

  // returns the current generation
  inline int getCurrentGenerationCount() const;

  // sends generation number, time taken, fitness, and mutation rate to stdout
  void printStatus(std::chrono::high_resolution_clock::time_point &start_time);

  // Allows threaded class access to member variables
  friend class TSP_Algo_Genetic_Threaded;

 protected:
  // pointer to graph the algorithm works on
  const Graph* m_graph;

  // size of the chromosome heap
  int m_population_size;

  // fitness of the current generation
  int m_best_fitness;

  // fitness of the last generation
  int m_last_fitness;

  // starting probability that a new generation will mutate (swap vertices)
  double m_mutation_probability;

  // number of generations that have passed
  int m_generation_count;

  // min heap of route chromosomes with the fittest chromosome (the shortest
  // length route) at the top
  ChromosomeHeap m_chromosome_heap;
};

class TSP_Algo_Genetic_Threaded {
 public:
  // constructs number of TSP_Algo_Genetic objects equal to thread_count
  // and stores pointers to them in m_populations vector
  TSP_Algo_Genetic_Threaded(Graph* t_graph, int population_size = 1000,
                            int thread_count = 4);

  // inline void tick(TSP_Algo_Genetic* population) { population->tick(); }
  // move route solution from one population to another
  void migrate();

  void tick();

  // create four threads running their own genetic algorithm
  void run(const int num_generations = 5000, bool display_status = true);

  // changes the number of Chromosomes stored in m_chromosome_heap
  void changePopulationSize(int population_size);

  // returns pointer to genetic object at index in m_populations
  const TSP_Algo_Genetic* getPopulation(int &index) const;

  // returns the current best route
  std::vector<int> getRoute() const;

  // returns fitness at the top of the heap
  inline int getCurrentFitness() const { return m_best_fitness; }

  inline int getThreadCount() const { return m_thread_count; }

 private:
  // stores all populations
  std::vector<TSP_Algo_Genetic*> m_populations;

  // number of concurrent threads to be run
  // value corresponds with the size of the m_populations vector
  int m_thread_count;

  // stores the best fitness of all genetic objects in m_populations
  int m_best_fitness;

  // size of the chromosome heap
  int m_population_size;
};

}  // namespace TSP_Algos

#endif  // TSP_algo_genetic_H_
