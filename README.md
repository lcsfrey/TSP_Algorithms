# TSP_Algorithms
Traveling Salesman Approximation with GUI. This is a project I developed for my analysis of algorithms class. The objective was to research solutions to the traveling salesman problem and implement an approximation algorithm that could come up with near-optimal solutions in a fixed time frame.

# Features
  * Read test set from file
      * Reads lines of vertices from input file in the form "id x y"
  * Nearest Neighbor Approximation O(N^2)
  * 2-Optimal Tour Approximation O(N^3)
    * Supports multithreaded execution for improved performance
  * Genetic Algorithm O(M*NlogN)
    * Algorithm that constructs random population of routes, recombining the best solutions to produce improved route
  * Route Trie O(N*N)
    * Stores route solutions in trie data structure. Routes can be accessed by traversing the trie backwards
  * Prim's Minimum Spanning Tree O(E logV)
  * Dijkstra's Single Source Shortest Path O(V^2)  
  * GUI
      * Load tours from GUI
      * Displays algorithms mentioned above
      * Displays length of tour
      * Select starting vertex for nearest neighbor and dijkstra algorithms
      * Algorithms not supported by GUI
         * Graph Trie
         * Genetic
   

  ### Prim's Minimum Spanning Tree
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_mst.png "Graph Plot MST")
  ### Nearest Neighbor Tour
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_nn.png "Graph Plot Nearest Neighbor")
  ### 2-Optimal Tour
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_two_opt.png "Graph Plot 2-Optimal")
  
# Todo List
  * Add custom time-delayed tour animation
