#ifndef DIRECTORY_CONTENTS_H
#define DIRECTORY_CONTENTS_H

#include <filesystem>
#include <vector>

#include "FileInfo.h"

struct DirectoryContents {
  std::filesystem::path directoryPath;
  std::vector<std::filesystem::path> subdirectories;
  std::vector<FileInfo> files;
};

#endif
