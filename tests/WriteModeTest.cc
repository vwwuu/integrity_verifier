#include "WriteMode.h"

#include <gtest/gtest.h>

class WriteModeTestClass : public testing::Test
{
protected:
  WriteMode writeMode;
};

TEST_F(WriteModeTestClass, ValidateWriteMode) {
  EXPECT_TRUE(false);
}
