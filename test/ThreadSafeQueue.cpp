#include "gtest/gtest.h"
#include "Queue.hpp"
#include <array>

TEST(THREADSAFE_QUEUE, PushAndPop) {
  constexpr std::array<int, 5> TEST_SEQUENCE{1, 2, 3, 4, 5};

  Queue<int> queue;

  for(const auto& val: TEST_SEQUENCE){
    queue.push(val);
  }

  int num{0};
  for(const auto& val: TEST_SEQUENCE){
    ASSERT_TRUE(queue.pop(num));
    ASSERT_EQ(val, num);
  }
};