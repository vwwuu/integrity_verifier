#ifndef INTEGRITY_CORE_H
#define INTEGRITY_CORE_H

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "ValidateMessage.h"
#include "FileInfo.h"

class IntegrityCore
{
 public:
  bool validateDirectory(std::filesystem::path const& targetDirectory) const;
  std::map<std::filesystem::path, std::map<std::filesystem::path, FileInfo>> getDirectoryContents(std::filesystem::path const& targetDirectory) const;
  bool readRecord(std::string const& recordFile) const;
};

#endif
