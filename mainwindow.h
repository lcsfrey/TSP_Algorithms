#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *e);

private slots:
    void on_button_prim_clicked();

    void on_button_dijkstras_clicked();

    void on_button_nearest_clicked();

    void on_button_two_opt_clicked();

    void on_button_draw_clicked();

    void on_pushButton_7_clicked();


    void on_button_clear_clicked();

    void on_spinBox_editingFinished();

    private:
    int m_label_tour_length = 0;
    Graph* m_graph = nullptr;
    std::vector<Vertex>* m_vertices = nullptr;
    std::vector<int> m_tour;
    int m_line_choice = 0;
    int m_starting_index = 0;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
