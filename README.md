# TSP_Algorithms
Traveling Salesman Approximation with GUI
This is a project I developed for my analysis of algorithms class. The objective was to research solutions to the traveling salesman problem and implement an approximation algorithm that could come up with near-optimal solutions in a fixed time frame.

# Features
  * Read test set from file
      * Reads lines of vertices from input file in the form "id x y"
  * Prim's Minimum Spanning Tree O(E logV)
  * Nearest Neighbor Approximation O(n^2)
  * 2-Optimal Tour Approximation O(n^3)
  * GUI
      * Load tours from GUI
      * Displays algorithms mentioned above
      * Displays length of tour

  ### Prim's Minimum Spanning Tree
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_mst.png "Graph Plot MST")
  ### Nearest Neighbor Tour
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_nn.png "Graph Plot Nearest Neighbor")
  ### 2-Optimal Tour
  ![picture alt](https://raw.githubusercontent.com/lcsfrey/TSP_Algorithms/master/readme_images/img_gplot_two_opt.png "Graph Plot 2-Optimal")
  
# Todo List
  * Implement and display Dijsktra's Shortest Path Algorithm
  * Add ability to choose the starting point of Nearest Neighbor Algorithm and Dijkstra's Algorithm
  * Implement genetic evolution tour algorithm
  * Add custom time-delayed tour animation
  
