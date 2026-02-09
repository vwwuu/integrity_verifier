#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/IntegrityCore.h"

class IntegrityCoreTestClass : public testing::Test
{
protected:
  IntegrityCore core;
};

TEST_F(IntegrityCoreTestClass, InvalidDirectoryBool) {
  const std::filesystem::path p1 = "sandbox/t1";
  std::filesystem::create_directories(p1);
  const std::filesystem::path p2 = "sandbox/t2";
  EXPECT_FALSE(core.validateDirectory(p2).validateBool);
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidDirectoryBool) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  EXPECT_TRUE(core.validateDirectory(p).validateBool);
  std::filesystem::remove_all("sandbox");
}
