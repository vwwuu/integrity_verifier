#ifndef DIRECTORY_CONTENT_H
#define DIRECTORY_CONTENT_H

#include <filesystem>
#include <vector>

#include "FileInfo.h"

struct DirectoryContent {
  std::filesystem::path directoryPath;
  std::vector<FileInfo> files;
  std::vector<DirectoryContent> subdirectories;
};

#endif
