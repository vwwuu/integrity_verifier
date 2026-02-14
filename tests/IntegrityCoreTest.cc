#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/IntegrityCore.h"
#include "TestHelpers.h"

class IntegrityCoreTestClass : public testing::Test
{
protected:
  IntegrityCore core;
};

// validateDirectory Tests
TEST_F(IntegrityCoreTestClass, InvalidDirectoryBool) {
  const std::filesystem::path p1 = "sandbox/t1";
  std::filesystem::create_directories(p1);
  const std::filesystem::path p2 = "sandbox/t2";
  EXPECT_FALSE(core.validateDirectory(p2));
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidDirectoryBool) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  EXPECT_TRUE(core.validateDirectory(p));
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidateThrow) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  std::filesystem::permissions(
			       "sandbox",
			       std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec | std::filesystem::perms::others_exec,
			       std::filesystem::perm_options::remove
			      );
  EXPECT_FALSE(core.validateDirectory(p));
  std::filesystem::permissions(
			       "sandbox",
			       std::filesystem::perms::owner_all,
			       std::filesystem::perm_options::add
			      ); 
  std::filesystem::remove_all("sandbox");
}

// createFileInfo tests
TEST_F(IntegrityCoreTestClass, createFileInfo) {
  const std::filesystem::path root = "sandbox";
  const std::filesystem::path p1 = root/"c1";
  std::filesystem::create_directories(p1);
  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");
  
  FileInfo actualFileInfo = core.createFileInfo(p1);
  FileInfo expectedFileInfo;
  expectedFileInfo.fileName = "fileP1";
  expectedFileInfo.filePath = p1;
  expectedFileInfo.fileExtension = ".txt";
  EXPECT_TRUE(TestHelpers::compareFileInfo(expectedFileInfo, actualFileInfo));

  std::filesystem::remove_all("sandbox");
}

// getDirectoryContents Tests
TEST_F(IntegrityCoreTestClass, getEmptyDirectory) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  std::map<std::filesystem::path, FileInfo> actualMap = core.getDirectoryContents(p);
  std::map<std::filesystem::path, FileInfo> expectedMap{};

  EXPECT_TRUE(TestHelpers::getDirectoryTestHelper(actualMap, expectedMap));

  std::filesystem::remove_all("sandbox");
}


TEST_F(IntegrityCoreTestClass, getDirectoryContentsOutput) {
  auto createFile = [](const std::filesystem::path& p, std::string_view pContents){
    std::ofstream newFile(p);
    newFile << pContents;
  };
  
  const std::filesystem::path root = "sandbox";
  const std::filesystem::path p1 = root/"c1";
  const std::filesystem::path p2 = root/"c2";
  std::filesystem::create_directories(p1);
  std::filesystem::create_directories(p2);

  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");
  TestHelpers::createFile(p1/"config.json", "{ \"key\": 1 }");
  TestHelpers::createFile(p1/"image.png", "png");
  TestHelpers::createFile(p1/"fileP2.txt", "Hello c2");
  TestHelpers::createFile(p2/"script.py", "print('Hello World!')");
  TestHelpers::createFile(p2/"archive.zip", "dummy zip");
 
  std::map<std::filesystem::path, FileInfo> actualMap = core.getDirectoryContents(root);
  std::map<std::filesystem::path, FileInfo> expectedMap{
    {p1/"fileP1.txt", FileInfo{}}
  };
  EXPECT_TRUE(TestHelpers::getDirectoryTestHelper(actualMap, expectedMap));
  std::filesystem::remove_all("sandbox");
}
