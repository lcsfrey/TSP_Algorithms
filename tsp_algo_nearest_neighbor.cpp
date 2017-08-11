#include "tsp_algo_nearest_neighbor.h"

int TSP_Algo_Nearest_Neighbor::getCurrentFitness() const{
    return this->m_fitness;
}

vector<Vertex>* TSP_Algo_Nearest_Neighbor::getRoute(){
    return this->m_vertices;
}

void TSP_Algo_Nearest_Neighbor::tick(){
    calcFitness();
}

void TSP_Algo_Nearest_Neighbor::calcFitness(){
    m_last_fitness = m_fitness;
    int t_total_fitness = 0, t_current_fitness = 0;
    for(int i = 0; i < this->m_min_spanning_tree.size(); i++){
        std::vector<Edge> edges = m_graph.getVertex(i).getEdges();
        t_current_fitness = edges.at(m_min_spanning_tree[i]).getWeight();
        t_total_fitness += t_current_fitness;
    }
    m_fitness = t_total_fitness;

}
