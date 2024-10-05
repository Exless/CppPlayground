#include <fmt/format.h>
#include <gtest/gtest.h>

using fmt::format;

TEST(BasicTest, BasicTest1)
{
  auto ll = [] (int n) -> int
  {
    const int max_range = 1000;
    if (n > max_range)
    {
      throw std::runtime_error(format("n exceeds max_range = {}", max_range));
    }

    int j = 0;
    for (int i = 0; i < n; i++)
    {
      j = i;
    }
    return j;
  };

  ASSERT_THROW(ll(1001), std::runtime_error)
    << "Should throw with arg passed above 1000";
  ASSERT_NO_THROW(ll(900));
}
