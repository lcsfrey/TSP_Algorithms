#include <gtest/gtest.h>

#include "graph_test.h"
#include "vertex_test.h"

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
