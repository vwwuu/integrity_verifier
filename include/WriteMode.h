X #ifndef WRITEMODE_H
#define WRITEMODE_H

#include "IntegrityCore.h"
    
#include <filesystem>

#include "DirectoryContent.h"

class WriteMode
{
public:
  explicit WriteMode (IntegrityCore& core);

  public:
  bool run(std::filesystem::path const& directoryPath, std::filesystem::path const& outputPath); // calls writeRecord
  
  private:
  IntegrityCore& _core;
  bool writeRecord(DirectoryContent const& directoryContent, std::filesystem::path const& outputPath); // produce JSON file
};

#endif
