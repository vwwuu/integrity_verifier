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

    std::error_code ec;
    std::filesystem::remove_all(inputDir, ec);

    EXPECT_FALSE(Writer.run(inputDir, outputDir));
    
    std::filesystem::remove_all(outputDir, ec);

    EXPECT_FALSE(Writer.run(inputDir, outputDir));
}
