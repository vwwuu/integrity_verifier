#ifndef RECORDMODE_H
#define RECORDMODE_H

#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <string>

class RecordMode
{
public:
  explicit RecordMode (const std::filesystem::path& targetDirectory);

  private:
  bool validateDirectoryPath(const std::filesystem::path& targetDirectory);
  std::filesystem::path tDirectory;
};

#endif
