#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Graph my_graph("tsp_example_1.txt");
    vector<int> mst = my_graph.primMST();
    std::vector<Vertex> vertices = my_graph.getVertices();

    MainWindow w;
    w.show();
    return a.exec();
}
