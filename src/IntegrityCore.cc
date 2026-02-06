#include "../include/IntegrityCore.h"

bool IntegrityCore::validateDirectory(const std::filesystem::path& targetDirectory)
{
  try {
    std::filesystem::file_status tDirectory = std::filesystem::status(targetDirectory);
    return std::filesystem::is_directory(tDirectory);
  }
  catch (const std::runtime_error& e) {
    std::cout << "Filesystem error: " << e.what() << std::endl;
    return false;
  }
}
