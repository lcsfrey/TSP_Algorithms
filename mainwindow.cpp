#include "mainwindow.h"
#include "ui_mainwindow.h"

void drawLines(QCustomPlot *customPlot, std::vector<Vertex> vertices, vector<int> connections);
void drawPoints(QCustomPlot *customPlot, std::vector<Vertex> vertices);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e){

}

void MainWindow::makePlot(){
    Graph my_graph("tsp_example_1.txt");
    std::vector<int> mst = my_graph.primMST();
    std::vector<Vertex> vertices = my_graph.getVertices();


    ui->customPlot->addGraph();
    ui->customPlot->addGraph();

    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    QCPScatterStyle scatter_style;
    scatter_style.setShape(QCPScatterStyle::ssCircle);
    scatter_style.setPen(QPen(Qt::green));
    scatter_style.setBrush(Qt::green);
    scatter_style.setSize(15);
    ui->customPlot->graph(0)->setScatterStyle(scatter_style);


    int max_x = 0;
    int max_y = 0;
    for(auto vertex : vertices){
        int x = vertex.getX();
        int y = vertex.getY();
        if(max_x < x){
            max_x = x;
        }
        if(max_y < y){
            max_y = y;
        }
    }
    drawLines(ui->customPlot, vertices, mst);
    drawPoints(ui->customPlot, vertices);

    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, max_x);
    ui->customPlot->yAxis->setRange(0, max_y);
    ui->customPlot->replot();
}

void drawLines(QCustomPlot *customPlot, std::vector<Vertex> vertices, vector<int> connections){
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
