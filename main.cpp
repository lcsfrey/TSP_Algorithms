/************************************************************************************
**                                                                                 **
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


#include "mainwindow.h"
#include <QApplication>

#include "graph.h"
#include "tsp_algo_nearest_neighbors.h"
#include "tsp_algo_genetic.h"
//#include "graph_path_trie.h"

using namespace std;
int testMenu(int argc, char *argv[]);
void testGenetic(Graph *t_graph);
int showWindow();
void printLicense();
int displayGUI(int argc, char *argv[]);


int main(int argc, char *argv[]) {
    printLicense();
    //testMenu(argc, argv);
    Graph* my_graph = new Graph("tsp_test_cases/test-input-1.txt");
    //Graph_path_trie my_path(my_graph, my_graph->getNumVertices());
//    TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn1(my_graph);
    //algo_nn1.findPath();
    //algo_nn1.twoOpt();
//    TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn2(my_graph);
//    algo_nn2.findPath();
//    algo_nn2.threadedTwoOpt();

//    int population_size = 500;
//    TSP_Algos::TSP_Algo_Genetic algo_g(my_graph, population_size);
//    algo_g.run(10000);
    TSP_Algos::TSP_Algo_Genetic_Threaded algo_tg(my_graph);
    algo_tg.run();
    return 0;
}

int testMenu(int argc, char *argv[]) {
    Graph* my_graph = new Graph("tsp_test_cases/test-input-2.txt");
    TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(my_graph);
    int choice = -1;
    while (choice != 0) {
        cout << "Select method:\n"
             << "0 - Exit\n"
             << "1 - Nearest Neighbor\n"
             << "2 - Two Optimal\n"
             << "3 - Threaded Two Optimal\n"
             << "4 - Genetic\n"
             << "5 - Launch GUI\n"
             << "\n";
        cin >> choice;
        cout << endl;
        switch (choice) {
            case 0:
                break;
            case 1:
                algo_nn.findPath();
                break;
            case 2:
                algo_nn.findPath();
                algo_nn.twoOpt();
                break;
            case 3:
                algo_nn.findPath();
                algo_nn.threadedTwoOpt();
                break;
            case 4:
                testGenetic(my_graph);
                break;
            case 5:
                return displayGUI(argc, argv);
                break;
            break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    }
    return 0;
}

void testGenetic(Graph* t_graph) {
    int choice = -1;
    int num_runs = 5000;
    int pop_size = 1000;
    TSP_Algos::TSP_Algo_Genetic algo_g(t_graph);
    do {
        cout << "Select options:\n"
             << "0 - Exit\n"
             << "1 - Run algorithm\n"
             << "2 - Next generation\n"
             << "3 - Change population size\n"
             << "4 - Change number of generations\n";
        cin >> choice;
        switch(choice) {
            case 0:
                break;
            case 1:
                algo_g.run(num_runs);
            case 2:
                algo_g.tick();
            case 3:
                cout << "Enter size:\n";
                cin >> pop_size;
                algo_g.changePopulationSize(pop_size);
            case 4:
                cout << "Enter number of gens:\n";
                cin >> num_runs;
            default:
                cout << "Invalid choice!\n";
            }
    } while (choice != -1);
}

int displayGUI(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

void printLicense() {
    std::cout <<
    " ******************************************************************************\n"
    "*                                                                              *\n"
    "*                                    MIT License                               *\n"
    "*                                                                              *\n"
    "*  Copyright (c) 2017 Lucas Frey                                               *\n"
    "*                                                                              *\n"
    "*  Permission is hereby granted, free of charge, to any person obtaining       *\n"
    "*  a copy of this software and associated documentation files (the             *\n"
    "*  \"Software\"), to deal in the Software without restriction, including         *\n"
    "*  without limitation the rights to use, copy, modify, merge, publish,         *\n"
    "*  distribute, sublicense, and/or sell copies of the Software, and to permit   *\n"
    "*  persons to whom the Software is furnished to do so, subject to the          *\n"
    "*  following conditions:                                                       *\n"
    "*                                                                              *\n"
    "*  The above copyright notice and this permission notice shall be included     *\n"
    "*  in all copies or substantial portions of the Software.                      *\n"
    "*                                                                              *\n"
    "*  THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,             *\n"
    "*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF          *\n"
    "*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.      *\n"
    "*  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY        *\n"
    "*  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,        *\n"
    "*  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE           *\n"
    "*  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                      *\n"
    "*                                                                              *\n"
    "*  Scroll up for license...                                                    *\n"
    "*                                                                              *\n"
    "********************************************************************************\n"
    "*                                                                              *\n"
    "*                                 GraphPlot                                    *\n"
    "*  Author: Lucas Frey                                                          *\n"
    "*  Version: 1.1                                                                *\n"
    "*  Date Last Modified: 8/26/2017                                               *\n"
    "*                                                                              *\n"
    " ******************************************************************************\n\n\n";
}

