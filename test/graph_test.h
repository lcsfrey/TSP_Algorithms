#ifndef GRAPH_TEST_H_
#define GRAPH_TEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../include/graph.h"

using namespace testing;

TEST(GraphTest, TestEmptyGraph) {
  Graph g;
  EXPECT_EQ(0, g.getNumVertices());
}

TEST(GraphTest, TestAddVertices) {
  Graph g;
  g.addVertex(0);
  g.addVertex(1);
  g.addVertex(2, 0, 0);
  EXPECT_EQ(3, g.getNumVertices());
  g.addVertex(3, 1, 2);
  EXPECT_EQ(4, g.getNumVertices());
}

TEST(GraphTest, TestGetVertex) {
  Graph g;
  g.addVertex(0, 0, 0);
  g.addVertex(1, 3, 4);
  const VertexEuclid* v =  g.getVertex(1);
  EXPECT_EQ(VertexEuclid(1, 3, 4), *v);
}

TEST(GraphTest, TestGraphGetEdgeWeight) {
  Graph g;
  g.addVertex(0, 0, 0);
  g.addVertex(1, 3, 4);
  g.addEdge(0, 1);
  EXPECT_EQ(5, g.getEdgeWeight(0,1));
  EXPECT_EQ(5, g.getEdgeWeight(1, 0));

  g.addVertex(2, 0, 0);
  g.addEdge(0, 2);
  EXPECT_EQ(0, g.getEdgeWeight(0, 2));

  g.addVertex(3, -3, -4);
  g.addEdge(1, 3);
  EXPECT_EQ(10, g.getEdgeWeight(1, 3));
}

TEST(GraphTest, TestMakeGraphComplete) {
  Graph g;
  for (int n = 0; n < 100; n++) {
    g.addVertex(n, 0, 0);
  }
  g.makeGraphComplete();
  for (int u = 0; u < 100; u++) {
    for (int v = 0; v < 100; v++) {
      ASSERT_TRUE(g.hasEdge(u, v));
    }
  }
}

#endif  // GRAPH_TEST_H_
