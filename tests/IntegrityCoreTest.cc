#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/IntegrityCore.h"

class IntegrityCoreTestClass : public testing::Test
{
protected:
  IntegrityCore core;
};

TEST_F(IntegrityCoreTestClass, InvalidDirectory) {
  std::filesystem::path testDirectory = "/home/mintvoyager/GitHub/projects/integrity_verifier/tests/testing_directories/tset";
  EXPECT_FALSE(core.validateDirectory(testDirectory));
}

TEST_F(IntegrityCoreTestClass, ValidDirectory) {
  std::filesystem::path testDirectory = "/home/mintvoyager/GitHub/projects/integrity_verifier/tests/testing_directories/test";
  EXPECT_FALSE(core.validateDirectory(testDirectory));
}
