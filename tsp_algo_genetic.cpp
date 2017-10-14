#include "tsp_algo_genetic.h"
#include "tsp_algo_nearest_neighbors.h"
#include <iostream>
#include <iomanip>
#include <chrono>

class TSP_Algo_Genetic;
using TSP_Algo_G = TSP_Algos::TSP_Algo_Genetic;

// used to access current time
using Time = std::chrono::high_resolution_clock;

TSP_Algo_G::TSP_Algo_Genetic(Graph *t_graph,
                             int population_size) : m_graph(t_graph),
                                                    m_vertices(t_graph->getVertices()) {

    srand(time(0));
    m_best_fitness = INT32_MAX;
    m_last_fitness = 0;
    m_mutation_probability = .25;
    m_population_size = population_size;
    ChromosomeHeap temp_heap;

    // creates random Chromosomes and stores the best Chromosomes in min heap
    std::vector<int> t_route(m_vertices->size());
    std::iota(t_route.begin(), t_route.end(), 0);
    int random_pop_size = m_population_size * 2;
    for(int i = 0; i < random_pop_size; i++) {
        std::shuffle(t_route.begin(), t_route.end(), std::mt19937{std::random_device{}()});
        temp_heap.push(Chromosome(t_graph, t_route));
    }
    for (int i = 0; i < m_population_size; i++) {
        Chromosome candidate = temp_heap.top();
        m_chromosome_heap.push(candidate);
        temp_heap.pop();
    }
}

void TSP_Algo_G::changePopulationSize(int population_size) {
    m_population_size = population_size;
}

int TSP_Algo_G::getCurrentFitness() const{
    return this->m_best_fitness;
}

double TSP_Algo_G::getMutationProbability() const {
    return this->m_mutation_probability;
}

std::vector<int> TSP_Algo_G::getRoute() const {
    return this->m_chromosome_heap.top().m_route;
}

void TSP_Algo_G::tick(){
    ChromosomeHeap temp_chromosome_heap;
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

void TSP_Algo_G::run(const int &num_generations) {
    auto start_time = std::chrono::high_resolution_clock::now();

    auto finish = start_time;
    std::chrono::duration<double> elapsed = finish - start_time;

    for (int i = 0; i < num_generations; i++) {
        tick();
        if (i % 25 == 0) {
            finish = Time::now();
            elapsed = finish - start_time;
            std::cout << std::setprecision(2) << std::fixed
                      << "Gen " << i
                      << " | Time: " << elapsed.count() << " seconds"
                      << " | Fitness: " << getCurrentFitness()
                      << " | Mutation Rate: " << getMutationProbability()
                      << std::endl;
        }
    }
}

TSP_Algo_G::Chromosome TSP_Algo_G::reproduce(const TSP_Algo_G::Chromosome &parent_1,
                                             const TSP_Algo_G::Chromosome &parent_2) const {
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

TSP_Algo_G::Chromosome::Chromosome(const Graph *graph,
                                         const std::vector<int> &route) : m_route(route) {
    m_route_fitness = graph->calcPathLength(m_route);
}

void TSP_Algo_G::Chromosome::mutate(double probability) {
    if((double) rand() / RAND_MAX <= probability) {
        int size = m_route.size();
        std::swap(m_route[rand() % size], m_route[rand() % size]);
        mutate(probability - .005);
    }
}


bool TSP_Algo_G::Chromosome::operator >(const Chromosome& other_chromosome) const{
    return m_route_fitness > other_chromosome.m_route_fitness;
}


TSP_Algos::TSP_Algo_Genetic_Threaded::TSP_Algo_Genetic_Threaded(Graph *t_graph, int population_size) {
    m_populations.push_back(new TSP_Algo_Genetic(t_graph, population_size));
    m_populations.push_back(new TSP_Algo_Genetic(t_graph, population_size));
    m_populations.push_back(new TSP_Algo_Genetic(t_graph, population_size));
    m_populations.push_back(new TSP_Algo_Genetic(t_graph, population_size));
}

void TSP_Algos::TSP_Algo_Genetic_Threaded::run(int num_generations) {
  std::thread t0(&TSP_Algo_Genetic::run, m_populations[0], num_generations);
  std::thread t1(&TSP_Algo_Genetic::run, m_populations[1], num_generations);
  std::thread t2(&TSP_Algo_Genetic::run, m_populations[2], num_generations);
  std::thread t3(&TSP_Algo_Genetic::run, m_populations[3], num_generations);

  t0.join();
  t1.join();
  t2.join();
  t3.join();
  for (int i = 0; i <= 4; i++) {
      if (m_populations[i]->getCurrentFitness() < m_best_fitness) {
        m_best_fitness = m_populations[i]->getCurrentFitness();
      }
  }
}

const TSP_Algos::TSP_Algo_Genetic *TSP_Algos::TSP_Algo_Genetic_Threaded::getPopulation(int &index) const {
    return m_populations[index];
}

int TSP_Algos::TSP_Algo_Genetic_Threaded::getBestFitness() {
    return m_best_fitness;
}
