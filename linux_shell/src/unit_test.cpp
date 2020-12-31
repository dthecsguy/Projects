#include <iostream>
#include "../unit_tests/com_tests.hpp"
#include "../unit_tests/parse_tests.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
