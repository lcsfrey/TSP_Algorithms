#ifndef TSP_Algo_Genetic_H
#define TSP_Algo_Genetic_H
#include "graph.h"
#include <algorithm>
#include <queue>

namespace TSP_Algos{

}

class TSP_Algo_Genetic
{
public:
    TSP_Algo_Genetic(Graph* t_graph, int &population_size, int max_generations=1000, int max_species=500) : m_graph(t_graph){
        m_vertices = new std::vector<Vertex>(m_graph->getVertices());

        // creates all populations and stores them in min heap
        for(int i = 0; i < population_size; i++) {
            std::vector<int> t_route(m_vertices->size());

            std::iota(t_route.begin(), t_route.end(), 1);

            std::vector<std::vector<int>::iterator> t_vert_iterators(t_route.size());
            std::iota(t_vert_iterators.begin(), t_vert_iterators.end(), t_route.begin());

            std::shuffle(t_vert_iterators.begin(), t_vert_iterators.end(), std::mt19937{std::random_device{}()});

            //m_populations.push_back(Population(t_route));
            m_pop_heap.push(Population(t_graph, t_route));

            std::cout << "Contents of the list: ";
            for(auto n: t_route) std::cout << n << ' ';
            std::cout << '\n';

            std::cout << "Contents of the list, shuffled: ";
            for(auto i: t_vert_iterators) std::cout << *i << ' ';
            std::cout << '\n';
        }

    }

    int getCurrentFitness() const;
    struct Population {
            Population(Graph* t_graph, const std::vector<int> &t_route) {
                m_route = t_route;
                m_population_fitness = t_graph->calcPathLength(t_graph, t_route);
            }
            void mutate(int t_probability);
            Population reproduceWith(const Population& other_population) {
                std::vector<int> t_child;
                //std::vector<int> t_child;
            }
            bool operator> (const Population& other_pop) const {
                return m_population_fitness > other_pop.m_population_fitness;
            }
            int m_population_fitness;
            std::vector<int> m_route;
    };

    std::vector<int> getRoute() const;
    void tick();

    friend class Population;
protected:
    void calcFitness();
    int m_best_fitness = INT32_MAX;
    int m_last_fitness = 0;
    const std::vector<Vertex>* m_vertices;
    std::vector<int> m_best_route;
    std::priority_queue<Population, std::vector<Population>, std::greater<Population>> m_pop_heap;
    std::vector<Population> m_populations;
    Graph* m_graph;

};

#endif // TSP_algo_genetic_H
