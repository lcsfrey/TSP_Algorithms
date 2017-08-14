#include "tsp_algo_nearest_neighbors.h"
#include <cassert>

void TSP_Algo_Nearest_Neighbors::findPath(){
    printf("Finding nearest neighbor route...\n");
    auto start = std::chrono::high_resolution_clock::now();

    m_route.clear();
    vector<Vertex> t_vertices(m_graph->getVertices());
    vector<bool> inMST(t_vertices.size(), false);
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>* t_heap;
    int size = t_vertices.size();
    vector<int> parent(size);

    t_heap = &(t_vertices.front().getEdgeHeap());
    Edge current_edge = t_heap->top();
    m_route.push_back(current_edge);

    t_heap->pop();
    t_heap = &t_vertices[current_edge.getTo()].getEdgeHeap();


    inMST[current_edge.getFrom()] = true;
    inMST[current_edge.getTo()] = true;

    parent[0] = current_edge.getFrom();
    parent[1] = current_edge.getTo();
    int num_in_tour = 1;
    int t_total_path_length = current_edge.getWeight();



    while(num_in_tour < size){
        current_edge = t_heap->top();
        // empties heap of current vertex until an edge to
        // an untraversed vertex is at the top
        while(inMST[current_edge.getTo()] == true){
            t_heap->pop();
            current_edge = t_heap->top();
        }
        t_heap->pop();
        m_route.push_back(current_edge);
        parent[++num_in_tour] = current_edge.getTo();
        assert(inMST[current_edge.getTo()] ==false);
        inMST[current_edge.getTo()] = true;

        t_heap = &t_vertices[current_edge.getTo()].getEdgeHeap();
        t_total_path_length += current_edge.getWeight();
    }

    Edge last_edge(t_vertices[current_edge.getFrom()], t_vertices.front());
    t_total_path_length += last_edge.getWeight();
    m_route.push_back(last_edge);


    for(int i = 0; i < size; i++){
        parent[m_route.at(i).getFrom()] = m_route.at(i).getTo();
    }

    m_simple_path = parent;
    m_route_length = t_total_path_length;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    printf("Nearest Neighbor took: %f\n", elapsed.count());
}

vector<int> TSP_Algo_Nearest_Neighbors::getRoute(){
    return m_simple_path;
}

int TSP_Algo_Nearest_Neighbors::getRouteLength(){
    return m_route_length;
}

void TSP_Algo_Nearest_Neighbors::twoOpt(){
    printf("Finding 2-optimal route...\n");
    auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();

    int old_length = this->m_route_length;
    int current_length = this->m_route_length;
    vector<int> current_route(this->m_simple_path);

    Edge *old_edge_1;
    Edge *old_edge_2;
    Edge *new_edge_1;
    Edge *new_edge_2;
    int old_edge_1_weight;
    int old_edge_2_weight;
    int new_edge_1_weight;
    int new_edge_2_weight;

    int size = m_route.size();
    int iterations = 0;
    int min_i, min_k;
    int min_change = 0;


    do{
        min_change = 0;
        min_i = -1;
        //min_k = -1;
        old_length = current_length;
        iterations++;
        for(int i = 0; i < size-2; i++){
            for(int k = i+2; k < size; k++){

                old_edge_1 = &(m_vertices[current_route[i]].getEdge(current_route[i+1]));
                new_edge_1 = &(m_vertices[current_route[i]].getEdge(current_route[k]));
                if(k < size-1){
                    old_edge_2 = &(m_vertices[current_route[k]].getEdge(current_route[k+1]));
                    new_edge_2 = &(m_vertices[current_route[i+1]].getEdge(current_route[k+1]));
                }
                else{
                    old_edge_2 = &(m_vertices[current_route[k]].getEdge(current_route[0]));
                    new_edge_2 = &(m_vertices[current_route[i+1]].getEdge(current_route[0]));
                }
                old_edge_1_weight = old_edge_1->getWeight();
                old_edge_2_weight= old_edge_2->getWeight();
                new_edge_1_weight= new_edge_1->getWeight();
                new_edge_2_weight= new_edge_2->getWeight();
                int change = new_edge_1_weight + new_edge_2_weight - old_edge_1_weight - old_edge_2_weight;

                if(min_change > change){
                    min_change = change;
                    min_i = i+1;
                    min_k = k+1;
                }
            }
        }

        if(min_i != -1){
            current_length += min_change;
            vector<int>::iterator t_end = current_route.begin() + min_k;
            std::reverse(current_route.begin() + min_i, t_end);
        }
        finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        printf("Iteration %d took: %f\n",iterations, elapsed.count());

    }while(iterations <= 200 && old_length != current_length);

    this->m_simple_path = current_route;
    this->m_route_length = current_length;

    finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    printf("2-optimal took: %f\n", elapsed.count());
}

int TSP_Algo_Nearest_Neighbors::calcPathLength(vector<int>& t_path, int num_vertices){
    int t_total_length = 0;
    Edge* current_edge;
    std::vector<int>::iterator t_current_node = t_path.begin();
    for(int i = 0; i < num_vertices; i++){
       current_edge = &(m_vertices[i].getEdge(*t_current_node));
       t_current_node++;
       t_total_length += current_edge->getWeight();
    }
    return t_total_length;
}

void TSP_Algo_Nearest_Neighbors::storePath(){

}

//std::vector<int> TSP_Algo_Nearest_Neighbors::bruteForce(vector<<vector<int>*> stacks, int size){
//    stacks
//    for(int i = 0; i < size; i++){

//    }
//}
