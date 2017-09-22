/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDraw;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_label_algorithm;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *file_status;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *input_file;
    QPushButton *button_load_vertices;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *m_spinbox_random_vertices_to_add;
    QLabel *label_3;
    QPushButton *m_button_random_add_vertices;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *m_label_tour_length;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_time_taken;
    QLabel *m_value_time_taken;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QSpinBox *spinBox;
    QVBoxLayout *verticalLayout_7;
    QPushButton *button_nearest;
    QPushButton *button_two_opt;
    QVBoxLayout *verticalLayout_5;
    QPushButton *button_dijkstras;
    QPushButton *button_prim;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_8;
    QPushButton *button_draw;
    QPushButton *button_clear;
    QGridLayout *gridLayout;
    QCustomPlot *customPlot;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(900, 677);
        actionDraw = new QAction(MainWindow);
        actionDraw->setObjectName(QStringLiteral("actionDraw"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_label_algorithm = new QLabel(centralWidget);
        m_label_algorithm->setObjectName(QStringLiteral("m_label_algorithm"));
        m_label_algorithm->setMinimumSize(QSize(200, 0));
        m_label_algorithm->setMaximumSize(QSize(280, 16777215));

        horizontalLayout->addWidget(m_label_algorithm);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        file_status = new QLabel(centralWidget);
        file_status->setObjectName(QStringLiteral("file_status"));
        file_status->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_3->addWidget(file_status);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        input_file = new QLineEdit(centralWidget);
        input_file->setObjectName(QStringLiteral("input_file"));
        input_file->setMinimumSize(QSize(250, 0));

        verticalLayout_6->addWidget(input_file);


        horizontalLayout_3->addLayout(verticalLayout_6);

        button_load_vertices = new QPushButton(centralWidget);
        button_load_vertices->setObjectName(QStringLiteral("button_load_vertices"));
        button_load_vertices->setMinimumSize(QSize(150, 0));
        button_load_vertices->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(button_load_vertices);


        horizontalLayout->addLayout(horizontalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        m_spinbox_random_vertices_to_add = new QSpinBox(centralWidget);
        m_spinbox_random_vertices_to_add->setObjectName(QStringLiteral("m_spinbox_random_vertices_to_add"));

        horizontalLayout_6->addWidget(m_spinbox_random_vertices_to_add);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_6->addWidget(label_3);


        verticalLayout_2->addLayout(horizontalLayout_6);

        m_button_random_add_vertices = new QPushButton(centralWidget);
        m_button_random_add_vertices->setObjectName(QStringLiteral("m_button_random_add_vertices"));

        verticalLayout_2->addWidget(m_button_random_add_vertices);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(90, 0));
        label_2->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_2->addWidget(label_2);

        m_label_tour_length = new QLabel(centralWidget);
        m_label_tour_length->setObjectName(QStringLiteral("m_label_tour_length"));

        horizontalLayout_2->addWidget(m_label_tour_length);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        m_time_taken = new QLabel(centralWidget);
        m_time_taken->setObjectName(QStringLiteral("m_time_taken"));
        m_time_taken->setMinimumSize(QSize(90, 0));
        m_time_taken->setMaximumSize(QSize(16777215, 90));

        horizontalLayout_5->addWidget(m_time_taken);

        m_value_time_taken = new QLabel(centralWidget);
        m_value_time_taken->setObjectName(QStringLiteral("m_value_time_taken"));

        horizontalLayout_5->addWidget(m_value_time_taken);


        verticalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout_4->addLayout(verticalLayout_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(150, 16777215));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label);

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximumSize(QSize(150, 16777215));
        spinBox->setMaximum(100);
        spinBox->setSingleStep(5);

        verticalLayout_3->addWidget(spinBox);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        button_nearest = new QPushButton(centralWidget);
        button_nearest->setObjectName(QStringLiteral("button_nearest"));
        button_nearest->setMaximumSize(QSize(150, 16777215));

        verticalLayout_7->addWidget(button_nearest);

        button_two_opt = new QPushButton(centralWidget);
        button_two_opt->setObjectName(QStringLiteral("button_two_opt"));
        button_two_opt->setMaximumSize(QSize(150, 16777215));

        verticalLayout_7->addWidget(button_two_opt);


        horizontalLayout_4->addLayout(verticalLayout_7);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        button_dijkstras = new QPushButton(centralWidget);
        button_dijkstras->setObjectName(QStringLiteral("button_dijkstras"));
        button_dijkstras->setMaximumSize(QSize(150, 16777215));

        verticalLayout_5->addWidget(button_dijkstras);

        button_prim = new QPushButton(centralWidget);
        button_prim->setObjectName(QStringLiteral("button_prim"));
        button_prim->setMaximumSize(QSize(150, 16777215));

        verticalLayout_5->addWidget(button_prim);


        horizontalLayout_4->addLayout(verticalLayout_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        button_draw = new QPushButton(centralWidget);
        button_draw->setObjectName(QStringLiteral("button_draw"));
        button_draw->setMinimumSize(QSize(150, 0));
        button_draw->setMaximumSize(QSize(200, 16777215));

        verticalLayout_8->addWidget(button_draw);

        button_clear = new QPushButton(centralWidget);
        button_clear->setObjectName(QStringLiteral("button_clear"));
        button_clear->setMinimumSize(QSize(0, 0));
        button_clear->setMaximumSize(QSize(150, 16777215));

        verticalLayout_8->addWidget(button_clear);


        horizontalLayout_4->addLayout(verticalLayout_8);


        verticalLayout->addLayout(horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setMinimumSize(QSize(700, 500));

        gridLayout->addWidget(customPlot, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QCustomPlot plot examples", Q_NULLPTR));
        actionDraw->setText(QApplication::translate("MainWindow", "Draw", Q_NULLPTR));
        m_label_algorithm->setText(QApplication::translate("MainWindow", "No algorithm selected", Q_NULLPTR));
        file_status->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        input_file->setText(QApplication::translate("MainWindow", "test-input-1.txt", Q_NULLPTR));
        button_load_vertices->setText(QApplication::translate("MainWindow", "Load Vertices", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Total", Q_NULLPTR));
        m_button_random_add_vertices->setText(QApplication::translate("MainWindow", "Add Random Vertices", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Tour length: ", Q_NULLPTR));
        m_label_tour_length->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        m_time_taken->setText(QApplication::translate("MainWindow", "Time taken:", Q_NULLPTR));
        m_value_time_taken->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Starting Index", Q_NULLPTR));
        button_nearest->setText(QApplication::translate("MainWindow", "Nearest Neighbors", Q_NULLPTR));
        button_two_opt->setText(QApplication::translate("MainWindow", "2-Opt", Q_NULLPTR));
        button_dijkstras->setText(QApplication::translate("MainWindow", "Dijkstras", Q_NULLPTR));
        button_prim->setText(QApplication::translate("MainWindow", "Prim MST", Q_NULLPTR));
        button_draw->setText(QApplication::translate("MainWindow", "Draw Lines", Q_NULLPTR));
        button_clear->setText(QApplication::translate("MainWindow", "Clear Lines", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
