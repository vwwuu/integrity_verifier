#ifndef WRITEMODE_H
#define WRITEMODE_H

#include "IntegrityCore.h"
#include "DirectoryContent.h"

#include <filesystem>

class WriteMode
{
public:
  explicit WriteMode (IntegrityCore& core) : _core(core){}

  public:
  bool run(std::filesystem::path const& directoryPath,
	   std::filesystem::path const& outputPath); // calls writeRecord
  
  private:
  IntegrityCore& _core;
  
  static bool writeRecord(DirectoryContent const& directoryContent,
		   std::filesystem::path const& outputPath); // produce JSON file
};

#endif
