#include "../include/RecordMode.h"

RecordMode::RecordMode(const std::filesystem::path& targetDirectory)
{
  if (!validateDirectoryPath(targetDirectory)) {
    throw std::runtime_error{
      "Invalid directory, given: "+targetDirectory.string()
    };
  }
  tDirectory = targetDirectory;
}

bool RecordMode::validateDirectoryPath(const std::filesystem::path& targetDirectory)
{
  std::filesystem::file_status tDirectory = std::filesystem::status(targetDirectory);
  return std::filesystem::is_directory(tDirectory);
}
