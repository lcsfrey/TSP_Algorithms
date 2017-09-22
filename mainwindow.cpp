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

#include <string>
#include <vector>
#include <ctime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tsp_algo_nearest_neighbors.h"

// initializes main window
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->file_status->setText(QString("Current file: None"));
    m_vertices = nullptr;
    srand(time(0));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resetGraph(QCustomPlot *customPlot) {
    if (customPlot->graphCount() > 0) {
        customPlot->clearGraphs();
    }
    if (customPlot->itemCount() > 0) {
        customPlot->clearItems();
    }
    if (customPlot->plottableCount() > 0) {
        customPlot->clearPlottables();
    }
    customPlot->addGraph();
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    QCPScatterStyle scatter_style;
    scatter_style.setShape(QCPScatterStyle::ssCircle);
    scatter_style.setPen(QPen(Qt::green));
    scatter_style.setBrush(Qt::green);
    scatter_style.setSize(15);
    customPlot->graph(0)->setScatterStyle(scatter_style);
}

// prim's minimum spanning tree button
void MainWindow::on_button_prim_clicked() {
    m_line_choice = 0;
    QString status_label("Selected Prim's Minimum Spanning Tree");
    ui->m_label_algorithm->setText(status_label);
    ui->customPlot->replot();
}

// dijkstra's shortest path button
void MainWindow::on_button_dijkstras_clicked() {
    m_line_choice = 1;
    QString status_label("Selected Dijkstra's Shortest Path");
    ui->m_label_algorithm->setText(status_label);
    ui->customPlot->replot();
}

// nearest neighbor button
void MainWindow::on_button_nearest_clicked() {
    m_line_choice = 2;
    QString status_label("Selected Nearest Neighbor Tour");
    ui->m_label_algorithm->setText(status_label);
    ui->customPlot->replot();
}

// 2-optimal tour button
void MainWindow::on_button_two_opt_clicked() {
    m_line_choice = 3;
    QString status_label("Selected 2-Opt Tour");
    ui->m_label_algorithm->setText(status_label);
    ui->customPlot->replot();
}

// draws the selected algorithm on the screen
void MainWindow::on_button_draw_clicked() {
    if (m_vertices->size() == 0) return;
    resetGraph(ui->customPlot);
    drawPoints(ui->customPlot, m_vertices);
    switch (m_line_choice) {
        case 0: {  // Prim's Minimum Spanning
            displayPrim();
            break;
        }
        case 1: {  // Dijsktra's Shortest Path
            displayDijkstras();
            break;
        }
        case 2: {  // Nearest Neighbor Tour
            displayNearestNeighbor();
            break;
        }
        case 3: {  // 2-Optimal Tour
            displayTwoOpt();
            break;
        }
    }
    ui->customPlot->replot();
}

void MainWindow::displayPrim() {
    QString status_label("Calculating Prim's Minimum Spanning Tree...");
    ui->m_label_algorithm->setText(status_label);
    ui->customPlot->replot();

    std::vector<int> mst = m_graph->getPrimMST();
    drawPrimLines(ui->customPlot, *m_vertices, mst);

    status_label = "Showing Prim's Minimum Spanning Tree";
    ui->m_label_algorithm->setText(status_label);
}

void MainWindow::displayDijkstras() {
    QString status_label("Calculating Dijktra's Shortest Path...");
    ui->m_label_algorithm->setText(status_label);
    ui->customPlot->replot();

    std::vector<int> dijkstra_path = m_graph->getDijkstraPath(m_starting_index);
    drawPrimLines(ui->customPlot, *m_vertices, dijkstra_path);

    status_label = "Showing Dijkstra's Shortest Path";
    ui->m_label_algorithm->setText(status_label);
}

void MainWindow::displayNearestNeighbor() {
    QString status_label("Calculating Nearest Neighbors Tour...");
    ui->m_label_algorithm->setText(status_label);
    ui->customPlot->replot();

    TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(m_graph);
    algo_nn.findPath(m_starting_index);
    m_tour = algo_nn.getRoute();
    drawTourLines(ui->customPlot, *m_vertices, m_tour);

    std::string str_tour_length(std::to_string(algo_nn.getRouteLength()));
    QString q_str_tour_length(str_tour_length.c_str());
    ui->m_label_tour_length->setText(q_str_tour_length);
    status_label = "Showing Nearest Neighbors Tour";
    ui->m_label_algorithm->setText(status_label);
}

void MainWindow::displayTwoOpt() {
    QString status_label("Calculating 2-Optimal Tour...");
    ui->m_label_algorithm->setText(status_label);
    ui->customPlot->replot();

    TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(m_graph);
    algo_nn.findPath(m_starting_index);
    algo_nn.twoOpt();
    m_tour = algo_nn.getRoute();
    drawTourLines(ui->customPlot, *m_vertices, m_tour);

    ui->m_label_tour_length->setText(QString(algo_nn.getRouteLength()));
    std::string str_tour(std::to_string(algo_nn.getRouteLength()));
    QString t_q_string(str_tour.c_str());
    ui->m_label_tour_length->setText(t_q_string);
    status_label = "Showing 2-Optimal Tour";
    ui->m_label_algorithm->setText(status_label);
}

void MainWindow::drawTourLines(QCustomPlot *customPlot,
                   std::vector<Vertex> vertices,
                   std::vector<int> connections) {
    int size = connections.size() - 1;
    for (int i = 0; i < size; i++) {
        int parent_x = vertices[connections[i]].getX();
        int parent_y = vertices[connections[i]].getY();

        int child_x = vertices[connections[i+1]].getX();
        int child_y = vertices[connections[i+1]].getY();
        QCPItemLine *line = new QCPItemLine(customPlot);
        line->setPen(QPen(Qt::blue));
        line->start->setCoords(parent_x, parent_y + 20);
        line->end->setCoords(child_x, child_y + 20);
    }
    int parent_x = vertices[connections[size]].getX();
    int parent_y = vertices[connections[size]].getY();

    int child_x = vertices[connections[0]].getX();
    int child_y = vertices[connections[0]].getY();
    QCPItemLine *line = new QCPItemLine(customPlot);
    line->setPen(QPen(Qt::blue));
    line->start->setCoords(parent_x, parent_y + 20);
    line->end->setCoords(child_x, child_y + 20);
}

void MainWindow::drawPrimLines(QCustomPlot *customPlot,
                   std::vector<Vertex> vertices,
                   std::vector<int> connections) {
    for (auto vertex : vertices) {
        int parent_x = vertices[connections[vertex.getID()]].getX();
        int parent_y = vertices[connections[vertex.getID()]].getY();

        int child_x = vertex.getX();
        int child_y = vertex.getY();
        QCPItemLine *line = new QCPItemLine(customPlot);
        line->setPen(QPen(Qt::blue));
        line->start->setCoords(parent_x, parent_y + 20);
        line->end->setCoords(child_x, child_y + 20);
    }
}

void MainWindow::drawPoints(QCustomPlot *customPlot, std::vector<Vertex> *vertices) {
    if (vertices == nullptr) return;

    for (auto vertex : *vertices) {
        int x = vertex.getX();
        int y = vertex.getY() + 20;
        customPlot->graph(0)->addData(x, y);
        QCPItemText *text = new QCPItemText(customPlot);
        // text->setTextColor(Qt::green);
        text->setColor(Qt::red);
        QFont font;
        font.setPointSize(8);
        text->setFont(font);
        QString str = QString::number(vertex.getID());
        text->setText(QString(str));
        text->position->setCoords(x,  y);
    }
}

void MainWindow::on_button_load_vertices_clicked() {
    resetGraph(ui->customPlot);
    QString q_file_name(ui->input_file->text());
    std::string file_name(q_file_name.toStdString());
    if (m_graph != nullptr) {
        delete m_graph;
    }
    m_graph = new Graph(file_name);
    m_vertices = &m_graph->getVertices();

    m_max_x = 0;
    m_max_y = 0;
    for (auto vertex : *m_vertices) {
        int x = vertex.getX();
        int y = vertex.getY();
        if (m_max_x < x)
            m_max_x = x;
        if (m_max_y < y)
            m_max_y = y;
    }

    ui->customPlot->xAxis->setRange(0, m_max_x+50);
    ui->customPlot->yAxis->setRange(0, m_max_y+50);
    drawPoints(ui->customPlot, m_vertices);

    QString t_q_string("");
    ui->m_label_tour_length->setText(t_q_string);
    QString t_q_file(file_name.c_str());
    ui->file_status->setText(QString("Current file: ") + t_q_file);

    ui->customPlot->replot();
}

// button to clear lines from screen
void MainWindow::on_button_clear_clicked() {
    resetGraph(ui->customPlot);
    drawPoints(ui->customPlot, m_vertices);
    QString t_q_string("");
    ui->m_label_tour_length->setText(t_q_string);
    ui->customPlot->replot();
}

void MainWindow::on_spinBox_editingFinished() {
    m_starting_index = ui->spinBox->value();
}

void MainWindow::on_m_button_random_add_vertices_clicked() {
    int current_size = m_graph->getNumVertices();
    int total = current_size + ui->m_spinbox_random_vertices_to_add->value();
    for (int i = current_size; i < total; i++) {
        m_graph->addVertex(i, rand() % m_max_x, rand() % m_max_y);
    }
    m_vertices = &m_graph->getVertices();
    drawPoints(ui->customPlot, m_vertices);
    ui->customPlot->replot();
}
