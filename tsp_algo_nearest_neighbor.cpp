#include "tsp_algo_nearest_neighbor.h"

int TSP_Algo_Nearest_Neighbor::getCurrentFitness() const{
    return this->fitness;
}

vector<Vertex> TSP_Algo_Nearest_Neighbor::getRoute() const{
    return this->m_route;
}

void tick(){

}
