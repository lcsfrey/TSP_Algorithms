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
#include <thread>
#include <vector>
#include <tuple>

class TSP_Algo_Nearest_Neighbors;
using TSP_Algo_NN = TSP_Algos::TSP_Algo_Nearest_Neighbors;


TSP_Algo_NN::TSP_Algo_Nearest_Neighbors(Graph *t_graph)
    : m_graph(t_graph),
      m_vertices(t_graph->getVertices()),
      m_route_length(0),
      m_simple_route(t_graph->getNumVertices()){}

// calculates the nearest neighbor tour starting at starting_index
void TSP_Algo_NN::findPath(int starting_index) {
    printf("Finding nearest neighbor route...\n");
    auto start = std::chrono::high_resolution_clock::now();
    int size = m_vertices->size();
    int t_total_route_length = 0;

    // record of which vertices are in the route
    std::vector<bool> inRoute(size, false);

    // record of current route
    std::vector<int> t_simple_route(size);
    t_simple_route[0] = starting_index;

    inRoute[starting_index] = true;

    int num_in_tour = 0;
    int weight = 0;
    int current_id = starting_index;

    while (num_in_tour < size-1) {
        int min_id = -1;
        int min_weight = INT32_MAX;
        for (int next_id = 0; next_id < size; next_id++) {
            if(next_id != current_id) {
                weight = m_graph->getEdgeWeight(current_id, next_id);
                if (!inRoute[next_id] && weight < min_weight) {
                    min_id = next_id;
                    min_weight = weight;
                }
            }
        }
        inRoute[min_id] = true;
        t_simple_route[++num_in_tour] = min_id;
        t_total_route_length += min_weight;
        current_id = min_id;
    }

    // Add the final edge connecting the end to the beginning
    t_total_route_length += m_graph->getEdgeWeight(current_id, starting_index);
    m_simple_route = t_simple_route;
    m_route_length = t_total_route_length;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    printf("Nearest Neighbor took: %f seconds\n", elapsed.count());
    printf("Route length: %d\n----------------------------------------\n", m_route_length);
}

// calculates the 2-Optimal tour
void TSP_Algo_NN::twoOpt() {
    printf("Finding 2-optimal route...\n");
    auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_overall;
    std::chrono::duration<double> elapsed;

    int old_length = this->m_route_length;
    int current_length = this->m_route_length;
    std::vector<int> current_route(this->m_simple_route);
    int size = m_simple_route.size();
    int iterations = 0;
    do {
        // initialize loop variables
        int min_i = -1;
        int min_k = -1;
        std::vector<std::tuple<int, int, int>> change_list{std::tuple<int, int, int>(0, -1, -1)};
        old_length = current_length;
        
        findBestChange(current_route, change_list, 0, 0, size, size - 2);
        // reverse order of route between two indices if an improvement is found
        if (std::get<0>(change_list.front()) != 0) {
            current_length += std::get<0>(change_list.front());
            min_i = std::get<1>(change_list.front());
            min_k = std::get<2>(change_list.front());
            std::vector<int>::iterator t_end = current_route.begin() + min_k;
            std::reverse(current_route.begin() + min_i, t_end);
        }

        iterations++;
        // report time and length of every 25th iteration
        finish = std::chrono::high_resolution_clock::now();
        if (iterations % 25 == 0) {
            elapsed = finish - start;
            printf("%d iterations took: %f seconds\n", iterations, elapsed.count());
            printf("Current route length: %d\n", current_length);
            printf("----------------------------------------\n");
        }
    // repeat for 1500 iterations or until the length hasn't changed between iterations
    } while (iterations <= 1500 && old_length != current_length);

    this->m_simple_route = current_route;
    this->m_route_length = current_length;

    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    printf("2-optimal took: %f seconds\n", elapsed.count());
    printf("Final length: %d\n", m_route_length);
    printf("----------------------------------------\n");
}

void TSP_Algo_NN::threadedTwoOpt() {
    printf("Finding 2-optimal route...\n");
    auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed;

    int old_length = this->m_route_length;
    int current_length = this->m_route_length;
    std::vector<int> current_route(this->m_simple_route);
    int size = m_simple_route.size();
    int interval = size / 4;
    int iterations = 0;

    do {
        // initialize loop variables
        int min_change = INT32_MAX;
        int min_i = -1;
        int min_k = -1;
        std::vector<std::tuple<int, int, int>> change_list(4, std::tuple<int, int, int>(0, -1, -1));
        old_length = current_length;

        // start thread 1 to calculate the best improvement within the first quarter of the route
        std::thread t1(&TSP_Algo_NN::findBestChange, this, current_route,
                       std::ref(change_list), 0, 0, size, interval);

        // start thread 2 to calculate the best improvement within the second quarter of the route
        std::thread t2(&TSP_Algo_NN::findBestChange, this, current_route,
                       std::ref(change_list), 1, interval, size, 2*interval);

        // start thread 3 to calculate the best improvement within the third quarter of the route
        std::thread t3(&TSP_Algo_NN::findBestChange, this, current_route,
                       std::ref(change_list), 2, 2*interval, size, 3*interval);

        // start thread 4 to calculate the best improvement within the fourth quarter of the route
        std::thread t4(&TSP_Algo_NN::findBestChange, this, current_route,
                       std::ref(change_list), 3, 3*interval, size, size-2);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        // determine the best improvement (the smallest min_change)
        for (int i = 0; i < 4; i++) {
            if (std::get<0>(change_list.at(i)) < min_change) {
                min_change = std::get<0>(change_list.at(i));
                min_i = std::get<1>(change_list.at(i));
                min_k = std::get<2>(change_list.at(i));
            }
        }

        // reverse order of route between two indices if an improvement is found
        if (min_i != -1) {
            current_length += min_change;
            std::vector<int>::iterator t_end = current_route.begin() + min_k;
            std::reverse(current_route.begin() + min_i, t_end);
        }

        iterations++;
        // report time and length of every 25th iteration
        finish = std::chrono::high_resolution_clock::now();
        if (iterations % 25 == 0) {
            elapsed = finish - start;
            printf("%d iterations took: %f seconds\n", iterations, elapsed.count());
            printf("Current route length: %d\n", current_length);
            printf("----------------------------------------\n");
        }
    // repeat for 1500 iterations or until the length hasn't changed between iterations
    } while (iterations <= 1500 && old_length != current_length);

    this->m_simple_route = current_route;
    this->m_route_length = current_length;

    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    printf("2-optimal took: %f seconds\n", elapsed.count());
    printf("Final length: %d\n", m_route_length);
    printf("----------------------------------------\n");
}

//
void TSP_Algo_NN::findBestChange(const std::vector<int> &current_route,
                                 std::vector<std::tuple<int, int, int>> &change_list,
                                 const int &list_position,
                                 const int &starting_index,
                                 const int &size,
                                 const int &interval) const {
    int min_k = -1;
    int min_i = -1;
    int change = 0;
    int min_change = 0;
    for (int i = starting_index; i < interval; i++) {
        for (int k = i+2; k < size; k++) {
            change = calcChangeOfEdges(current_route, i, k, size);
            // check if the weight of the new edges is less than the weight of
            // the best improvement found so far
            if (change < min_change) {
                min_change = change;
                min_k = k + 1;
                min_i = i + 1;
            }
        }
    }
    if (min_k != -1) {
      std::tuple<int, int, int> best_change(min_change, min_i, min_k);
      change_list[list_position] = best_change;
    }
}

// returns the difference between the sum of the weights of two pairs of edges
// first pair of edges connect i to i+1 and k to k+1 in the route
// second pair of edges connect i to k and i+1 to k+1 in the route
int TSP_Algo_NN::calcChangeOfEdges(const std::vector<int> &current_route,
                                   const int &i,
                                   const int &k,
                                   const int &size) const {
    int old_edge_1_weight = m_graph->getEdgeWeight(current_route[i], current_route[i+1]);
    int new_edge_1_weight = m_graph->getEdgeWeight(current_route[i], current_route[k]);
    int old_edge_2_weight = 0;
    int new_edge_2_weight = 0;
    if (k < size - 1) {
        old_edge_2_weight = m_graph->getEdgeWeight(current_route[k], current_route[k+1]);
        new_edge_2_weight = m_graph->getEdgeWeight(current_route[i+1], current_route[k+1]);
    } else {
        old_edge_2_weight = m_graph->getEdgeWeight(current_route[k], current_route[0]);
        new_edge_2_weight = m_graph->getEdgeWeight(current_route[i+1], current_route[0]);
    }
    return new_edge_1_weight + new_edge_2_weight - old_edge_1_weight - old_edge_2_weight;;
}

// outputs file with the same name as the input file appended with ".tour"
// first line is the length of the tour
// subsequent lines the IDs of the vertices in the order they are visited
void TSP_Algo_NN::writeToFile(std::string file_name) {
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
