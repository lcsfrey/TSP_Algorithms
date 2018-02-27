include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS +=     \
    ../include/graph.h \
    ../include/vertex.h \
    vertex_test.h \
    graph_test.h

SOURCES +=     main.cpp \
    ../src/graph.cpp
