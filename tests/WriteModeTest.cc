#include "IntegrityCore.h"
#include "WriteMode.h"

#include <gtest/gtest.h>

class WriteModeTestClass : public testing::Test
{
protected:
  IntegrityCore Core;
  WriteMode Writer{Core};
};

TEST_F(WriteModeTestClass, ValidateWriteMode) {
  EXPECT_TRUE(false);
}
