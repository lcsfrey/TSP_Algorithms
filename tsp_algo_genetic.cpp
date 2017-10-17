#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#include "tsp_algo_genetic.h"

class TSP_Algo_Genetic;
using TSP_Algo_G = TSP_Algos::TSP_Algo_Genetic;

// used to access current time
using Time = std::chrono::high_resolution_clock;

TSP_Algo_G::TSP_Algo_Genetic(Graph *t_graph,
                             int population_size) : m_graph(t_graph),
                                                    m_vertices(t_graph->getVertices()) {

    srand(time(0));
    m_generation_count = 0;
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
    ChromosomeHeap temp_heap;
    for (int i = 0; i < population_size; i++) {
        if (i < m_population_size) {
            Chromosome candidate = m_chromosome_heap.top();
            temp_heap.push(candidate);
            m_chromosome_heap.pop();
        } else {
            std::vector<int> t_route(m_vertices->size());
            std::iota(t_route.begin(), t_route.end(), 0);
            std::shuffle(t_route.begin(), t_route.end(), std::mt19937{std::random_device{}()});
            temp_heap.push(Chromosome(m_graph, t_route));
        }
    }
    m_chromosome_heap = temp_heap;
    m_population_size = population_size;
}

int TSP_Algo_G::getCurrentFitness() const{
    return m_best_fitness;
}

double TSP_Algo_G::getMutationProbability() const {
    return m_mutation_probability;
}

int TSP_Algos::TSP_Algo_Genetic::getCurrentGenerationCount() const {
  return m_generation_count;
}

void TSP_Algos::TSP_Algo_Genetic::printStatus(Time::time_point &start_time) {
    Time::time_point finish = Time::now();
    std::chrono::duration<double> elapsed = finish - start_time;
    std::cout << std::setprecision(2) << std::fixed
              << "Gen " << getCurrentGenerationCount()
              << " | Time: " << elapsed.count() << " seconds"
              << " | Fitness: " << getCurrentFitness()
              << " | Mutation Rate: " << getMutationProbability()
              << std::endl;
}

std::vector<int> TSP_Algo_G::getRoute() const {
    return m_chromosome_heap.top().m_route;
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

    m_generation_count++;
}

void TSP_Algo_G::run(const int &num_generations, bool display_status) {
    Time::time_point start_time = Time::now();
    for (int i = 0; i < num_generations; i++) {
        if (display_status && i % 25 == 0) {
            printStatus(start_time);
        }
        tick();
    }
}

TSP_Algo_G::Chromosome TSP_Algo_G::reproduce(const TSP_Algo_G::Chromosome &parent_1,
                                             const TSP_Algo_G::Chromosome &parent_2) const {
    int size = m_vertices->size();
    int size_from_parent_1 = rand() % size;
    int offset_from_parent_1 = rand() % (size - size_from_parent_1);
    std::vector<int> t_child(parent_1.m_route.size());
    std::vector<bool> in_path(size, false);
    int index = 0;
    // pick a random sequence of vertices from parent_1 and add that sequence to the child route
    for (int i = offset_from_parent_1; i < size_from_parent_1 + offset_from_parent_1; i++) {
        t_child[index++] = parent_1.m_route[i];
        in_path[parent_1.m_route[i]] = true;
    }
    // get all remaining vertices that are not in the route from parent_2
    for (int i = 0; i < size; i++) {
        if (!in_path[parent_2.m_route[i]]) {
            t_child[index++] = parent_2.m_route[i];
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

// random chance to move top route from one population to another
TSP_Algos::TSP_Algo_Genetic_Threaded::TSP_Algo_Genetic_Threaded(Graph *t_graph,
                                                                int population_size,
                                                                int thread_count) {
    m_best_fitness = INT32_MAX;
    m_thread_count = thread_count;
    for(int i = 0; i < thread_count; i++) {
        m_populations.push_back(new TSP_Algo_Genetic(t_graph, population_size));
    }
}

void TSP_Algos::TSP_Algo_Genetic_Threaded::migrate() {
    int from = rand() % m_thread_count;
    int to = rand() % m_thread_count;
    while (to == from) {
        to = rand() % m_thread_count;
    }
    TSP_Algo_G::Chromosome migrant_chromosome = m_populations[from]->m_chromosome_heap.top();
    m_populations[from]->m_chromosome_heap.pop();
    m_populations[to]->m_chromosome_heap.push(migrant_chromosome);
}

void TSP_Algos::TSP_Algo_Genetic_Threaded::run(const int &num_generations) {
    Time::time_point start_time = Time::now();
    std::vector<std::thread> threads(m_thread_count);

    // initialize all threads in thread pool
    for (int i = 0; i < m_thread_count; i++) {
        threads[i] = std::thread(&TSP_Algo_Genetic::run, m_populations[i], num_generations, false);
    }
    for (std::thread &current_thread : threads) {
        current_thread.join();
    }

    // determine the shortest route length
    for (int i = 0; i < m_thread_count; i++) {
        if (m_populations[i]->getCurrentFitness() < m_best_fitness) {
            m_best_fitness = m_populations[i]->getCurrentFitness();
        }
        m_populations[i]->printStatus(start_time);
    }
}

void TSP_Algos::TSP_Algo_Genetic_Threaded::changePopulationSize(int population_size) {
    for (int i = 0; i < m_thread_count; i++) {
        m_populations[i]->changePopulationSize(population_size);
    }
    m_population_size = population_size;
}

const TSP_Algos::TSP_Algo_Genetic* TSP_Algos::TSP_Algo_Genetic_Threaded::getPopulation(int &index) const {
    return m_populations[index];
}

int TSP_Algos::TSP_Algo_Genetic_Threaded::getCurrentFitness() const {
    return m_best_fitness;
}
