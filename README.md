# TSP_Algorithms
Traveling Salesman Approximation with GUI. This is a project I developed for my analysis of algorithms class. The objective was to research solutions to the traveling salesman problem and implement an approximation algorithm that could come up with near-optimal solutions in a fixed time frame.

# Features
  * Read test set from file
      * Reads lines of vertices from input file in the form "id x y"
  * Nearest Neighbor Approximation O(n^2)
  * 2-Optimal Tour Approximation O(n^3)
  * Prim's Minimum Spanning Tree O(E logV)
  * Dijkstra's Single Source Shortest Path O(V^2)  
  * GUI
      * Load tours from GUI
      * Displays algorithms mentioned above
      * Displays length of tour
      * Select starting vertex for nearest neighbor and dijkstra algorithms

  ### Prim's Minimum Spanning Tree
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_mst.png "Graph Plot MST")
  ### Nearest Neighbor Tour
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_nn.png "Graph Plot Nearest Neighbor")
  ### 2-Optimal Tour
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_two_opt.png "Graph Plot 2-Optimal")
  
# Todo List
  * Implement genetic evolution tour algorithm
  * Add custom time-delayed tour animation
