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

  return false;
}

bool WriteMode::writeRecord(DirectoryContent const& directoryContent,
			    std::filesystem::path const& outputPath) {
  return false;
}
