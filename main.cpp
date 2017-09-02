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
#include "graph_path_trie.h"

int showWindow();
void printLicense();
int displayGUI(int argc, char *argv[]);
int main(int argc, char *argv[]) {
    Graph* my_graph = new Graph("test-input-1.txt");
    int population_size = 1000;


    //Graph_path_trie my_path(my_graph, my_graph->getNumVertices());

    printLicense();
    int choice = -1;

    TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(my_graph);
    //TSP_Algos::TSP_Algo_Genetic algo_g(my_graph, population_size);

    return displayGUI(argc, argv);
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

