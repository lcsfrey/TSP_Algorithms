#ifndef TSP_ALGO_NEAREST_NEIGHBORS_H
#define TSP_ALGO_NEAREST_NEIGHBORS_H
#include "graph.h"
#include <algorithm>
#include <string>


class TSP_Algo_Nearest_Neighbors
{
public:
    TSP_Algo_Nearest_Neighbors(Graph* t_graph) : m_graph(t_graph){
        m_min_spanning_tree = m_graph->primMST();
        m_vertices =vector<Vertex>(m_graph->getVertices());
    }

    void findPath();
    void storePath();
    std::vector<int> getRoute();
    void twoOpt();
    int getRouteLength();

private:
    vector<int> twoOptSwap(vector<int> &t_route, int start, int end, int &size);
    int calcPathLength(vector<int>& t_path, int size);
    int m_route_length = 0;
    vector<Vertex> m_vertices;
    vector<Edge> m_route;
    vector<int> m_simple_path;
    vector<int> m_min_spanning_tree;
    Graph *m_graph;

};
#endif // TSP_ALGO_NEAREST_NEIGHBORS_H
