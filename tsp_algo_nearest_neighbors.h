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

#ifndef TSP_ALGO_NEAREST_NEIGHBORS_H_
#define TSP_ALGO_NEAREST_NEIGHBORS_H_
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>

#include "graph.h"

namespace TSP_Algos {

class TSP_Algo_Nearest_Neighbors {
 public:
    explicit TSP_Algo_Nearest_Neighbors(Graph* t_graph);

    // calculates the nearest neighbor tour starting at starting_index
    void findPath(int starting_index = 0);

    // calculates the 2-optimal tour
    // m_simple_tour must already have an initial route
    void twoOpt();

    // calculates the 2-optimal tour
    // m_simple_tour must already have an initial route
    // work done by method is divided between four threads
    void threadedTwoOpt();

    inline std::vector<int> getRoute() const { return m_simple_route; }
    inline int getRouteLength() const { return m_route_length; }

    // outputs file with the same name as the input file appended with ".tour"
    // first line is the length of the tour
    // subsequent lines the IDs of the vertices in the order they are visited
    void writeToFile(std::string file_name);

 private:
    // returns the difference between the sum of the weights of two pairs of edges
    // first pair of edges connect i to i+1 and k to k+1 in the route
    // second pair of edges connect i to k and i+1 to k+1 in the route
    int calcChangeOfEdges(const std::vector<int> &current_route,
                          const int &i,
                          const int &k,
                          const int &size) const;
    // findBestChange is used by twoOpt and threadedTwoOpt methods to find the best
    // improvement over an interval. The result is stored as a tuple in
    // change_list[list_position] where the first int is the best improvement,
    // (the smallest value of change found) the second and third ints are the indeces
    // in current_route that will be manipulated by twoOpt and threadedTwoOpt.
    void findBestChange(const std::vector<int> &current_route,
                        std::vector<std::tuple<int, int, int> > &change_list,
                        const int &list_position,
                        const int &starting_index,
                        const int &size,
                        const int &interval) const;
    int m_route_length;
    const std::vector<Vertex>* m_vertices;
    std::vector<int> m_simple_route;
    const Graph* m_graph;
};

}  // namespace TSP_Algos

#endif  // TSP_ALGO_NEAREST_NEIGHBORS_H_
