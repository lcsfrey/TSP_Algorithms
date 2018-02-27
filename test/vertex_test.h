#ifndef VERTEX_TEST_H_
#define VERTEX_TEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../include/vertex.h"

// Test Vertex class

TEST(SimpleVertexTest, TestSimpleVertexGetID) {
  Vertex v1(0);
  EXPECT_EQ(0, v1.getID());

  Vertex v2(1);
  EXPECT_EQ(1, v2.getID());
}

TEST(SimpleVertexTest, TestSimpleVertexEquality) {
  Vertex v1(0);
  Vertex v2(0);
  EXPECT_EQ(v1, v2);
}

TEST(SimpleVertexTest, TestSimpleVertexAssignment) {
  Vertex v1(0);
  Vertex v2(1);
  ASSERT_FALSE(v1 == v2);
  v2 = v1;
  EXPECT_EQ(v1, v2);
}

TEST(SimpleVertexTest, TestSimpleVertexAddEdge) {
  Vertex v1(0);
  Vertex v2(1);
  ASSERT_FALSE(v1.hasEdge(1));
  ASSERT_FALSE(v2.hasEdge(0));
  v1.addEdge(v2);
  ASSERT_TRUE(v1.hasEdge(1));
  ASSERT_FALSE(v2.hasEdge(0));
}

TEST(SimpleVertexTest, TestSimpleVertexGetEdgeWeight) {
  Vertex v1(0);
  Vertex v2(1);
  v1.addEdge(v2, 5);
  ASSERT_EQ(5, v1.getEdgeWeight(1));
  ASSERT_EQ(INT32_MAX, v2.getEdgeWeight(0));
}

// Test VertexEuclid class

TEST(VertexEuclidTest, TestVertexEuclidEquality) {
  VertexEuclid v1(1, 2, 3);
  VertexEuclid v2(0, 2, 3);
  VertexEuclid v3(1, 3, 3);
  VertexEuclid v4(1, 2, 4);
  VertexEuclid v5(1, 2, 3);

  EXPECT_FALSE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
  EXPECT_FALSE(v1 == v4);
  EXPECT_EQ(v1, v5);
}

TEST(VertexEuclidTest, TestVertexEuclidAssignment) {
  VertexEuclid v1(1, 2, 3);
  VertexEuclid v2(0, 2, 3);
  EXPECT_FALSE(v1 == v2);
  v1 = v2;
  EXPECT_EQ(v1, v2);
}

TEST(VertexEuclidTest, TestVertexEuclidGetMethods) {
  VertexEuclid v1(0, 1, 2);
  ASSERT_EQ(0, v1.getID());
  ASSERT_EQ(1, v1.getX());
  ASSERT_EQ(2, v1.getY());

  VertexEuclid v2(1, 3, 4);
  ASSERT_EQ(1, v2.getID());
  ASSERT_EQ(3, v2.getX());
  ASSERT_EQ(4, v2.getY());
}

TEST(VertexEuclidTest, TestVertexEuclidAddEdge) {
  VertexEuclid v1(0, 1, 2);
  VertexEuclid v2(1, 3, 4);
  ASSERT_FALSE(v1.hasEdge(1));
  ASSERT_FALSE(v2.hasEdge(0));
  v1.addEdge(v2);
  ASSERT_TRUE(v1.hasEdge(1));
  ASSERT_FALSE(v2.hasEdge(0));
}

TEST(VertexEuclidTest, TestVertexEuclidGetEdgeWeight) {
  VertexEuclid v1(0, 0, 0);
  VertexEuclid v2(1, 3, 4);
  v1.addEdge(v2);
  ASSERT_EQ(5, v1.getEdgeWeight(1));
  ASSERT_EQ(INT32_MAX, v2.getEdgeWeight(0));
}

#endif  // VERTEX_TEST_H_
