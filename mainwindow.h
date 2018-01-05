#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <chrono>
#include "graph.h"
#include "tsp_algo_genetic.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 protected:
    // draws traveling salesman approximation lines
    void drawTourLines(QCustomPlot* customPlot,
                       const std::vector<VertexEuclid>* vertices,
                       const std::vector<int> &connections);

    // draws minimum spanning tree lines
    void drawPrimLines(QCustomPlot* customPlot,
                       const std::vector<VertexEuclid>* vertices,
                       const std::vector<int> &connections);

    // draws vertices on graph
    void drawPoints(QCustomPlot* customPlot,
                    const std::vector<VertexEuclid>* vertices);

    // deletes all drawn lines and vertices from graph
    // reinitializes drawing properties
    void resetGraph(QCustomPlot* customPlot);


    void displayGenetic(int num_generations);
    void displayPrim();
    void displayDijkstras();
    void displayNearestNeighbor();
    void displayTwoOpt();

private slots:
    void on_button_prim_clicked();

    void on_button_dijkstras_clicked();

    void on_button_nearest_clicked();

    void on_button_two_opt_clicked();

    void on_button_draw_clicked();

    void on_button_load_vertices_clicked();

    void on_button_clear_clicked();

    void on_spinBox_editingFinished();

    void on_m_button_random_add_vertices_clicked();

    void on_Genetic_clicked();

  private:
    Graph* m_graph = nullptr;
    const std::vector<VertexEuclid>* m_vertices = nullptr;
    std::vector<int> m_tour;
    int m_line_choice = 0;
    int m_starting_index = 0;
    int m_label_tour_length = 0;
    int m_max_y = 0;
    int m_max_x = 0;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
