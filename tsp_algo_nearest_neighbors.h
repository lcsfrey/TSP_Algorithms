#ifndef TSP_ALGO_NEAREST_NEIGHBORS_H
#define TSP_ALGO_NEAREST_NEIGHBORS_H
#include "graph.h"
#include <algorithm>
#include <string>
#include <fstream>


class TSP_Algo_Nearest_Neighbors
{
public:
    TSP_Algo_Nearest_Neighbors(Graph* t_graph) : m_graph(t_graph){
        m_vertices = m_graph->getVertices();
    }

    void findPath();
    void twoOpt(chrono::system_clock::time_point time_overall_start = std::chrono::high_resolution_clock::now());
    std::vector<int> getRoute();
    int getRouteLength();
    void writeToFile(std::string file_name);


private:
    int calcPathLength(vector<int>& t_route);
    int m_route_length = 0;
    vector<Vertex> m_vertices;
    vector<Edge> m_route;
    vector<int> m_simple_route;
    Graph *m_graph;

};
#endif // TSP_ALGO_NEAREST_NEIGHBORS_H
