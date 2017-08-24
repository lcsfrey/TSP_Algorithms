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

#ifndef TSP_ALGO_NEAREST_NEIGHBORS_H
#define TSP_ALGO_NEAREST_NEIGHBORS_H
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

#include "graph.h"

namespace TSP_Algos {

class TSP_Algo_Nearest_Neighbors
{
 public:
    TSP_Algo_Nearest_Neighbors(Graph* t_graph) : m_graph(t_graph) {
        m_vertices = &(m_graph->getVertices());
    }
    void findPath(int starting_index = 0);
    void twoOpt(std::chrono::system_clock::time_point time_overall_start = std::chrono::high_resolution_clock::now());

    inline std::vector<int> getRoute() const { return m_simple_route; }
    inline int getRouteLength() const { return m_route_length; }

    void writeToFile(std::string file_name);

 private:
    int calcPathLength(const std::vector<int> &t_route);

    int m_route_length = 0;
    std::vector<Vertex>* m_vertices;
    std::vector<int> m_simple_route;
    Graph* m_graph;

};

}
#endif // TSP_ALGO_NEAREST_NEIGHBORS_H
