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

#include "mainwindow_copy.h"
#include "ui_mainwindow.h"
#include "tsp_algo_nearest_neighbors.h"

// draws traveling salesman approximation lines
void drawTourLines(QCustomPlot *customPlot,
                   std::vector<Vertex> vertices,
                   std::vector<int> connections);

// draws minimum spanning tree lines
void drawPrimLines(QCustomPlot *customPlot,
                   std::vector<Vertex> vertices,
                   std::vector<int> connections);

// draws vertices on graph
void drawPoints(QCustomPlot *customPlot,
                std::vector<Vertex> *vertices);

// deletes all drawn lines and vertices from graph
// reinitializes drawing properties
void resetGraph(QCustomPlot *customPlot);

// initializes main window
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    resetGraph(ui->customPlot);
    ui->file_status->setText(QString("Current file: None"));
    m_vertices = nullptr;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e) {
}

void resetGraph(QCustomPlot *customPlot) {
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

// prim button function
void MainWindow::on_button_prim_clicked() {
    m_line_choice = 0;
    QString t__qstring("Selected Prim Minimum Spanning Tree");
    ui->m_label_algorithm->setText(t__qstring);
    ui->customPlot->replot();
}

// dijkstra button function
void MainWindow::on_button_dijkstras_clicked() {
    m_line_choice = 1;
    QString t__qstring("Selected Dijkstra's Shortest Path");
    ui->m_label_algorithm->setText(t__qstring);
    ui->customPlot->replot();
}

void MainWindow::on_button_nearest_clicked() {
    m_line_choice = 2;
    QString t__qstring("Selected Nearest Neighbor Tour");
    ui->m_label_algorithm->setText(t__qstring);
    ui->customPlot->replot();
}

void MainWindow::on_button_two_opt_clicked() {
    m_line_choice = 3;
    QString t__qstring("Selected 2-Opt Tour");
    ui->m_label_algorithm->setText(t__qstring);
    ui->customPlot->replot();
}


void MainWindow::on_button_draw_clicked() {
    if (m_vertices->size() == 0) return;
    // ui->m_label_algorithm->setText();
    resetGraph(ui->customPlot);
    drawPoints(ui->customPlot, m_vertices);
    switch (m_line_choice) {
        case 0: {  // Prim Minimum Spanning
            QString t__qstring("Showing Prim Minimum Spanning Tree");
            ui->m_label_algorithm->setText(t__qstring);
            std::vector<int> mst = m_graph->getPrimMST();
            drawPrimLines(ui->customPlot, *m_vertices, mst);
            break;
            }
        case 1:  // Dijsktra's Shortest Path
            break;
        case 2:  {  // Nearest Neighbor Tour
            QString t__qstring("Showing Nearest Neighbors Tour");
            ui->m_label_algorithm->setText(t__qstring);
            TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(m_graph);
            algo_nn.findPath();
            m_tour = algo_nn.getRoute();
            drawTourLines(ui->customPlot, *m_vertices, m_tour);
            std::string str_tour(std::to_string(algo_nn.getRouteLength()));
            QString t_q_string(str_tour.c_str());
            ui->m_label_tour_length->setText(t_q_string);
            break;
            }
        case 3: {  // 2-Optimum Tour
            QString t__qstring("Showing 2-Optimum Tour");
            ui->m_label_algorithm->setText(t__qstring);
            TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(m_graph);
            if (m_tour.size() == 0){
                            algo_nn.findPath();
                            m_tour = algo_nn.getRoute();
            }
            algo_nn.setTour(m_tour);
            algo_nn.twoOpt();
            ui->m_label_tour_length->setText(QString(algo_nn.getRouteLength()));
            m_tour = algo_nn.getRoute();
            drawTourLines(ui->customPlot, *m_vertices, m_tour);
            std::string str_tour(std::to_string(algo_nn.getRouteLength()));
            QString t_q_string(str_tour.c_str());
            ui->m_label_tour_length->setText(t_q_string);
            break;
            }
    }
    ui->customPlot->replot();
}

void drawTourLines(QCustomPlot *customPlot,
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

void drawPrimLines(QCustomPlot *customPlot,
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

void drawPoints(QCustomPlot *customPlot, std::vector<Vertex> *vertices) {
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

void MainWindow::on_pushButton_7_clicked() {
    resetGraph(ui->customPlot);
    QString q_file_name(ui->input_file->text());
    std::string file_name(q_file_name.toStdString());
    if (m_graph != nullptr) {
        delete m_graph;
    }
    m_graph = new Graph(file_name);
    m_vertices = &m_graph->getVertices();

    int max_x = 0;
    int max_y = 0;
    for (auto vertex : *m_vertices) {
        int x = vertex.getX();
        int y = vertex.getY();
        if (max_x < x) {
            max_x = x;
        }
        if (max_y < y) {
            max_y = y;
        }
    }

    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, max_x+50);
    ui->customPlot->yAxis->setRange(0, max_y+50);
    drawPoints(ui->customPlot, m_vertices);

    QString t_q_string("");
    ui->m_label_tour_length->setText(t_q_string);
    QString t_q_file(file_name.c_str());
    ui->file_status->setText(QString("Current file: ") + t_q_file);

    ui->customPlot->replot();
}

void MainWindow::on_button_clear_clicked() {
    resetGraph(ui->customPlot);
    drawPoints(ui->customPlot, m_vertices);
    QString t_q_string("");
    ui->m_label_tour_length->setText(t_q_string);
    ui->customPlot->replot();
}
