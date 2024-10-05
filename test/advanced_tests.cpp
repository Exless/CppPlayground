#include <gtest/gtest.h>
#include "../src/Vertex.h"


TEST(AdvancedTests, AddsOnInternal)
{
  auto vertex = std::make_unique<Vertex>(1, 2, 3);
  ASSERT_EQ(vertex->x, 1);
  ASSERT_EQ(vertex->y, 2);
  ASSERT_EQ(vertex->z, 3);
}