/************************************************************************************
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

#include "tsp_algo_nearest_neighbors.h"

namespace TSP_Algos {

void TSP_Algo_Nearest_Neighbors::findPath(int starting_index) {
    printf("Finding nearest neighbor route...\n");
    auto start = std::chrono::high_resolution_clock::now();
    int size = m_vertices->size();
    int t_total_route_length = 0;
    Vertex* current_node = &m_vertices->at(starting_index);

    // record of which vertices are in the route
    std::vector<bool> inRoute(m_vertices->size(), false);

    // record of current route
    std::vector<int> t_simple_route(size);
    t_simple_route[0] = starting_index;

    inRoute[starting_index] = true;

    int num_in_tour = 0;
    int min_index;
    int min_weight;
    int weight = 0;
    while (num_in_tour < size-1) {
        min_index = -1;
        min_weight = INT32_MAX;
        for (int i = 0; i < size; i++) {
            if(i != current_node->getID()) {
                weight = m_graph->getEdgeWeight(current_node->getID(), i);
                if (!inRoute[i] && weight < min_weight) {
                    min_index = i;
                    min_weight = weight;
                }
            }
        }
        inRoute[min_index] = true;
        t_simple_route[++num_in_tour] = min_index;
        t_total_route_length += min_weight;
        current_node = &m_vertices->at(min_index);
    }

    // Add the final edge connecting the end to the beginning
    t_total_route_length += current_node->getEdge(starting_index)->getWeight();

    m_simple_route = t_simple_route;
    m_route_length = t_total_route_length;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    printf("Nearest Neighbor took: %f seconds\n", elapsed.count());
    printf("Route length: %d\n----------------------------------------\n", m_route_length);
}

void TSP_Algo_Nearest_Neighbors::twoOpt(std::chrono::high_resolution_clock::time_point time_overall_start) {
    printf("Finding 2-optimal route...\n");
    auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_overall;
    std::chrono::duration<double> elapsed;

    int old_length = this->m_route_length;
    int current_length = this->m_route_length;
    std::vector<int> current_route(this->m_simple_route);
    int size = m_simple_route.size();
    int old_edge_1_weight;
    int old_edge_2_weight;
    int new_edge_1_weight;
    int new_edge_2_weight;

    // indices of vertices in the route to reverse
    int min_i = 0, min_k = 0;
    int min_change = 0;
    int change = 0;
    int iterations = 0;

    do {
        // initialize loop variables
        min_change = 0;
        min_i = -1;
        old_length = current_length;
        iterations++;

        // loop through every pair of edges in the current path
        for (int i = 0; i < size-2; i++) {
            for (int k = i+2; k < size; k++) {
                old_edge_1_weight = this->m_graph->getEdgeWeight(current_route[i], current_route[i+1]);
                new_edge_1_weight = this->m_graph->getEdgeWeight(current_route[i], current_route[k]);

                if (k < size-1) {
                    old_edge_2_weight = this->m_graph->getEdgeWeight(current_route[k], current_route[k+1]);
                    new_edge_2_weight = this->m_graph->getEdgeWeight(current_route[i+1], current_route[k+1]);
                } else {
                    old_edge_2_weight = this->m_graph->getEdgeWeight(current_route[k], current_route[0]);
                    new_edge_2_weight = this->m_graph->getEdgeWeight(current_route[i+1], current_route[0]);
                }

                // check if the weight of the new edges is less than the weight of the old edges
                change = new_edge_1_weight + new_edge_2_weight - old_edge_1_weight - old_edge_2_weight;
                if (min_change > change) {
                    min_change = change;
                    min_i = i+1;
                    min_k = k+1;
                }
            }
        }
        // reverse order of route between two indices
        if (min_i != -1) {
            current_length += min_change;
            std::vector<int>::iterator t_end = current_route.begin() + min_k;
            std::reverse(current_route.begin() + min_i, t_end);
        }

        // report time and length of every 25th iteration
        finish = std::chrono::high_resolution_clock::now();
        time_overall = finish - time_overall_start;
        if (iterations % 25 == 0) {
            elapsed = finish - start;
            printf("%d iterations took: %f seconds\n", iterations, elapsed.count());
            printf("Current route length: %d\n----------------------------------------\n", current_length);
        }
    // repeat for 1500 iterations or until the length hasn't changed between iterations
    } while (iterations <= 1500 && old_length != current_length);


    this->m_simple_route = current_route;
    this->m_route_length = calcPathLength(m_simple_route);

    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    printf("2-optimal took: %f seconds\n", elapsed.count());
    printf("Final length: %d\n", m_route_length);
    printf("Total time taken: %f seconds\n----------------------------------------\n", time_overall.count());
}

int TSP_Algo_Nearest_Neighbors::calcPathLength(const std::vector<int> &t_route) {
    int t_total_length = 0;
    int size = t_route.size() - 1;
    const Edge* current_edge;
    for (int i = 0; i < size; i++) {
       current_edge = m_vertices->at(t_route[i]).getEdge(t_route[i+1]);
       t_total_length += current_edge->getWeight();
    }
    current_edge = m_vertices->at(t_route[size]).getEdge(t_route[0]);
    t_total_length += current_edge->getWeight();
    return t_total_length;
}

// outputs file with the same name as the input file
// first line is the length of the tour
// subsequent lines the IDs of the vertices in the order they are visited
void TSP_Algo_Nearest_Neighbors::writeToFile(std::string file_name) {
    file_name += ".tour";
    std::ofstream file(file_name);
    std::cout << "Writing tour to file: " << file_name <<
                 "\n----------------------------------------\n";

    file << m_route_length << std::endl;
    for (auto current_node_id : this->m_simple_route) {
        file << current_node_id << std::endl;
    }
    file.close();
}

}
