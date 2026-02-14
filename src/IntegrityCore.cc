#include "../include/IntegrityCore.h"
#include <map>

namespace {
  std::string computeHash(std::filesystem::path const& filePath) {
    return ""; // TODO
  }

  FileInfo setFileInfo(std::filesystem::directory_entry const& e) {
    std::filesystem::path const ePath = e.path();
    return FileInfo {
      ePath.stem().string(),
      ePath,
      ePath.extension(),
      computeHash(ePath),
      std::chrono::system_clock::now()
    };
  }
}

bool IntegrityCore::validateDirectory(std::filesystem::path const& targetDirectory) const
{
  try {
    std::filesystem::file_status tDirectory = std::filesystem::status(targetDirectory);
    if (!std::filesystem::is_directory(tDirectory)) {
      return false;
    }
    
    return true;
  }
  catch (std::filesystem::filesystem_error const& e) {
    std::cout << "Filesystem error: " << e.what() << std::endl;
    return false;
  }
}

std::map<std::filesystem::path, std::map<std::filesystem::path, FileInfo>> IntegrityCore::getDirectoryContents(std::filesystem::path const& targetDirectory) const
{
  std::map<std::filesystem::path, FileInfo> directoryPaths;
  if (!this->validateDirectory(targetDirectory)) {
    return directoryPaths;
  }

  for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(targetDirectory)) {
    std::cout << dir_entry << std::endl;
    auto const& fileData = std::filesystem::status(dir_entry);
    if (std::filesystem::is_directory(fileData)) continue;
  }
  return directoryPaths;
}

FileInfo setFile
