#include "IntegrityCore.h"
#include "WriteMode.h"

#include <gtest/gtest.h>

class WriteModeTestClass : public testing::Test
{
protected:
  IntegrityCore Core;
  WriteMode Writer{Core};
};

TEST_F(WriteModeTestClass, ValidateWriteModePaths) {
    const std::filesystem::path inputDir  = std::filesystem::temp_directory_path() / "ValidateInput";
    const std::filesystem::path outputDir = std::filesystem::temp_directory_path() / "ValidateOutput";

    std::filesystem::create_directory(inputDir);
    std::filesystem::create_directory(outputDir);

    EXPECT_TRUE(Writer.run(inputDir, outputDir));
}
