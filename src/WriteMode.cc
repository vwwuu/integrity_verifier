#include "WriteMode.h"
#include "AcceptedFSType.h"

bool WriteMode::run(std::filesystem::path const& directoryPath,
		    std::filesystem::path const& outputPath) {
  // validate ouput path
  if (!_core.validatePath(outputPath, AcceptedFSType::DIRECTORY)) {
    return false;
  }
  
  // validate input path
  if (!_core.validatePath(directoryPath, AcceptedFSType::DIRECTORY)) {
    return false;
  }

  DirectoryContent directoryContent = _core.scanDirectory(directoryPath);
  return writeRecord(directoryContent, outputPath);
}

bool WriteMode::writeRecord(DirectoryContent const& directoryContent,
			    std::filesystem::path const& outputPath) {
  return true;
}
