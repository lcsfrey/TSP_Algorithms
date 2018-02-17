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
#include <iostream>

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
  if (customPlot->graphCount() > 0)
    customPlot->clearGraphs();
  if (customPlot->itemCount() > 0)
    customPlot->clearItems();
  if (customPlot->plottableCount() > 0)
    customPlot->clearPlottables();

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


void MainWindow::on_Genetic_clicked() {
  m_line_choice = 4;
  QString status_label("Selected Genetic Tour");
  ui->m_label_algorithm->setText(status_label);
}

// draws the selected algorithm on the screen
void MainWindow::on_button_draw_clicked() {
  if (m_vertices->size() == 0) return;
  resetGraph(ui->customPlot);
  drawPoints(ui->customPlot, m_vertices);
  switch (m_line_choice) {
    case 0: displayPrim(); break; // Prim's Minimum Spanning
    case 1: displayDijkstras(); break;  // Dijsktra's Shortest Path
    case 2: displayNearestNeighbor(); break; // Nearest Neighbor Tour
    case 3: displayTwoOpt(); break; // 2-Optimal Tour
    case 4: displayGenetic(100); break; // Genetic Tour
  }
  ui->customPlot->replot();
}

void MainWindow::displayPrim() {
  ui->m_label_algorithm->setText("Calculating Prim's Minimum Spanning Tree...");
  ui->customPlot->replot();

  std::vector<int> mst = m_graph->getPrimMST();
  drawPrimLines(ui->customPlot, m_vertices, mst);

  ui->m_label_algorithm->setText("Showing Prim's Minimum Spanning Tree");
}

void MainWindow::displayDijkstras() {
  ui->m_label_algorithm->setText("Calculating Dijktra's Shortest Path...");
  ui->customPlot->replot();

  std::vector<int> dijkstra_path = m_graph->getDijkstraPath(m_starting_index);
  drawPrimLines(ui->customPlot, m_vertices, dijkstra_path);

  ui->m_label_algorithm->setText("Showing Dijkstra's Shortest Path");
}

void MainWindow::displayNearestNeighbor() {
  ui->m_label_algorithm->setText("Calculating Nearest Neighbors Tour...");
  ui->customPlot->replot();

  TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(m_graph);
  algo_nn.findPath(m_starting_index);
  m_tour = algo_nn.getRoute();
  drawTourLines(ui->customPlot, m_vertices, m_tour);

  ui->m_label_tour_length->setText(QString::number(algo_nn.getRouteLength()));
  ui->m_label_algorithm->setText("Showing Nearest Neighbors Tour");
}

void MainWindow::displayTwoOpt() {
  ui->m_label_algorithm->setText("Calculating 2-Optimal Tour...");
  ui->customPlot->replot();

  TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(m_graph);
  algo_nn.findPath(m_starting_index);
  algo_nn.twoOpt();
  m_tour = algo_nn.getRoute();
  drawTourLines(ui->customPlot, m_vertices, m_tour);

  ui->m_label_tour_length->setText(QString::number(algo_nn.getRouteLength()));
  ui->m_label_algorithm->setText("Showing 2-Optimal Tour");
}

void MainWindow::displayGenetic(int num_generations) {
  ui->m_label_algorithm->setText("Calculating Genetic Tour...");
  TSP_Algos::TSP_Algo_Genetic algo_g(m_graph);
  for (int i = 0; i < num_generations; i++) {
     algo_g.run(10);
     std::this_thread::sleep_for(std::chrono::milliseconds(100));
     m_tour = algo_g.getRoute();
     resetGraph(ui->customPlot);
     drawPoints(ui->customPlot, m_vertices);
     drawTourLines(ui->customPlot, m_vertices, m_tour);
     ui->customPlot->replot();
  }
  ui->m_label_tour_length->setText(QString::number(algo_g.getCurrentFitness()));
  ui->m_label_algorithm->setText("Showing Genetic Tour");
}

void MainWindow::drawTourLines(QCustomPlot* customPlot,
                 const std::vector<VertexEuclid>* vertices,
                 const std::vector<int> &connections) {
  int size = connections.size() - 1;
  for (int i = 0; i < size; i++) {
    int parent_x = vertices->at(connections[i]).getX();
    int parent_y = vertices->at(connections[i]).getY();

    int child_x = vertices->at(connections[i+1]).getX();
    int child_y = vertices->at(connections[i+1]).getY();
    QCPItemLine *line = new QCPItemLine(customPlot);
    line->setPen(QPen(Qt::blue));
    line->start->setCoords(parent_x, parent_y);
    line->end->setCoords(child_x, child_y);
  }
  int parent_x = vertices->at(connections[size]).getX();
  int parent_y = vertices->at(connections[size]).getY();

  int child_x = vertices->at(connections[0]).getX();
  int child_y = vertices->at(connections[0]).getY();
  QCPItemLine *line = new QCPItemLine(customPlot);
  line->setPen(QPen(Qt::blue));
  line->start->setCoords(parent_x, parent_y);
  line->end->setCoords(child_x, child_y);
}

void MainWindow::drawPrimLines(QCustomPlot *customPlot,
           const std::vector<VertexEuclid>* vertices,
           const std::vector<int> &connections) {
  for (auto VertexEuclid : *vertices) {
    int parent_x = vertices->at(connections[VertexEuclid.getID()]).getX();
    int parent_y = vertices->at(connections[VertexEuclid.getID()]).getY();

    int child_x = VertexEuclid.getX();
    int child_y = VertexEuclid.getY();
    QCPItemLine *line = new QCPItemLine(customPlot);
    line->setPen(QPen(Qt::blue));
    line->start->setCoords(parent_x, parent_y + 20);
    line->end->setCoords(child_x, child_y + 20);
  }
}

void MainWindow::drawPoints(QCustomPlot *customPlot,
              const std::vector<VertexEuclid>* vertices) {
  if (vertices == nullptr) return;

  for (VertexEuclid VertexEuclid : *vertices) {
    int x = VertexEuclid.getX();
    int y = VertexEuclid.getY();
    customPlot->graph(0)->addData(x, y);
    QCPItemText *text = new QCPItemText(customPlot);
    text->setColor(Qt::red);
    QFont font;
    font.setPointSize(8);
    text->setFont(font);
    text->setText(QString::number(VertexEuclid.getID()));
    text->position->setCoords(x,  y);
  }
}

void MainWindow::on_button_load_vertices_clicked() {
  resetGraph(ui->customPlot);
  std::string file_name("tsp_test_cases/" + ui->input_file->text().toStdString());

  if (m_graph != nullptr)
    delete m_graph;

  m_graph = new Graph(file_name);
  m_vertices = m_graph->getVertices();

  m_max_x = 0;
  m_max_y = 0;
  for (auto VertexEuclid : *m_vertices) {
    int x = VertexEuclid.getX();
    int y = VertexEuclid.getY();
    if (m_max_x < x)
      m_max_x = x;
    if (m_max_y < y)
      m_max_y = y;
  }

  ui->customPlot->xAxis->setRange(-20, m_max_x+50);
  ui->customPlot->yAxis->setRange(-20, m_max_y+50);
  drawPoints(ui->customPlot, m_vertices);

  ui->m_label_tour_length->setText("");
  ui->file_status->setText("Current file: " + QString(file_name.c_str()));

  ui->customPlot->replot();
}

// button to clear lines from screen
void MainWindow::on_button_clear_clicked() {
  resetGraph(ui->customPlot);
  drawPoints(ui->customPlot, m_vertices);
  ui->m_label_tour_length->setText("");
  ui->customPlot->replot();
}

void MainWindow::on_spinBox_editingFinished() {
  m_starting_index = ui->spinBox->value();
}

void MainWindow::on_m_button_random_add_vertices_clicked() {
  int current_size = m_graph->getNumVertices();
  int total = current_size + ui->m_spinbox_random_vertices_to_add->value();
  for (int i = current_size; i < total; i++)
    m_graph->addVertex(i, rand() % m_max_x, rand() % m_max_y);

  m_graph->makeGraphComplete();
  m_vertices = m_graph->getVertices();
  resetGraph(ui->customPlot);
  drawPoints(ui->customPlot, m_vertices);
  ui->customPlot->replot();
}
