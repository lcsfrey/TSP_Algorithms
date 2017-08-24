#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tsp_algo_nearest_neighbors.h"

void drawTourLines(QCustomPlot *customPlot, std::vector<Vertex> vertices, std::vector<int> connections);
void drawPrimLines(QCustomPlot *customPlot, std::vector<Vertex> vertices, std::vector<int> connections);
void drawPoints(QCustomPlot *customPlot, std::vector<Vertex> vertices);
void resetGraph(QCustomPlot *customPlot);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //MainWindow::makePlot();
    resetGraph(ui->customPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e){

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

void MainWindow::on_button_prim_clicked()
{
    m_line_choice = 0;
}

void MainWindow::on_button_dijkstras_clicked()
{
    m_line_choice = 1;
}

void MainWindow::on_button_nearest_clicked()
{
    m_line_choice = 2;
}

void MainWindow::on_button_two_opt_clicked()
{
    m_line_choice = 3;
}

void MainWindow::on_button_draw_clicked()
{

    //ui->m_label_algorithm->setText();
    resetGraph(ui->customPlot);
    drawPoints(ui->customPlot, *m_vertices);

    switch(m_line_choice){
        case 0: { // Prim Minimum Spanning
            QString t__qstring("Showing Prim Minimum Spanning Tree");
            ui->m_label_algorithm->setText(t__qstring);
            std::vector<int> mst = m_graph->getPrimMST();
            drawPrimLines(ui->customPlot, *m_vertices, mst);
            break;
            }
        case 1:  // Dijsktra's Shortest Path
            break;
        case 2:  { // Nearest Neighbor Tour
            QString t__qstring("Showing Nearest Neighbors Tour");
            ui->m_label_algorithm->setText(t__qstring);
            TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(m_graph);
            algo_nn.findPath();
            std::vector<int> nn = algo_nn.getRoute();
            drawTourLines(ui->customPlot, *m_vertices, nn);
            break;
            }
        case 3: { // 2-Optimum Tour
            QString t__qstring("Showing 2-Optimum Tour");
            ui->m_label_algorithm->setText(t__qstring);
            TSP_Algos::TSP_Algo_Nearest_Neighbors algo_nn(m_graph);
            algo_nn.findPath();
            algo_nn.twoOpt();
            std::vector<int> two_opt = algo_nn.getRoute();
            drawTourLines(ui->customPlot, *m_vertices, two_opt);
            break;
            }
    }
    ui->customPlot->replot();
}

void drawTourLines(QCustomPlot *customPlot, std::vector<Vertex> vertices, std::vector<int> connections){
    int size = connections.size() - 1;
    for (int i = 0; i < size; i++) {
        int parent_x = vertices[connections[i]].getX();
        int parent_y = vertices[connections[i]].getY();

        int child_x = vertices[connections[i+1]].getX();
        int child_y = vertices[connections[i+1]].getY();
        QCPItemLine *line = new QCPItemLine(customPlot);
        line->setPen(QPen(Qt::blue));
        line->start->setCoords(parent_x, parent_y);
        line->end->setCoords(child_x, child_y);
    }
    int parent_x = vertices[connections[size]].getX();
    int parent_y = vertices[connections[size]].getY();

    int child_x = vertices[connections[0]].getX();
    int child_y = vertices[connections[0]].getY();
    QCPItemLine *line = new QCPItemLine(customPlot);
    line->setPen(QPen(Qt::blue));
    line->start->setCoords(parent_x, parent_y);
    line->end->setCoords(child_x, child_y);
}

void drawPrimLines(QCustomPlot *customPlot, std::vector<Vertex> vertices, std::vector<int> connections) {
    for(auto vertex : vertices){
        int parent_x = vertices[connections[vertex.getID()]].getX();
        int parent_y = vertices[connections[vertex.getID()]].getY();

        int child_x = vertex.getX();
        int child_y = vertex.getY();
        QCPItemLine *line = new QCPItemLine(customPlot);
        line->setPen(QPen(Qt::blue));
        line->start->setCoords(parent_x, parent_y);
        line->end->setCoords(child_x, child_y);
    }
}

void drawPoints(QCustomPlot *customPlot, std::vector<Vertex> vertices){

    for(auto vertex : vertices){
        int x = vertex.getX();
        int y = vertex.getY();
        customPlot->graph(0)->addData(x,y);
        QCPItemText *text = new QCPItemText(customPlot);
        //text->setTextColor(Qt::green);
        text->setColor(Qt::red);
        QFont font;
        font.setPointSize(8);
        text->setFont(font);
        QString str = QString::number(vertex.getID());
        text->setText(QString(str));
        text->position->setCoords(x,y);
    }
}

void MainWindow::on_pushButton_7_clicked()
{

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
    for(auto vertex : *m_vertices){
        int x = vertex.getX();
        int y = vertex.getY();
        if(max_x < x){
            max_x = x;
        }
        if(max_y < y){
            max_y = y;
        }
    }

    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, max_x+50);
    ui->customPlot->yAxis->setRange(0, max_y+50);
    drawPoints(ui->customPlot, *m_vertices);

    ui->customPlot->replot();
}

void MainWindow::on_button_clear_clicked()
{
    resetGraph(ui->customPlot);
    drawPoints(ui->customPlot, *m_vertices);
    ui->customPlot->replot();
}
