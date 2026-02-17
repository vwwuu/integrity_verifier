#ifndef INTEGRITY_CORE_H
#define INTEGRITY_CORE_H

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>

#include "ValidateMessage.h"
#include "AcceptedFSType.h"
#include "FileInfo.h"
#include "DirectoryContent.h"

class IntegrityCore
{
 public:
  bool validatePath(std::filesystem::path const& p, AcceptedFSType fType) const;
  DirectoryContent scanDirectory(std::filesystem::path const& dPath);
  std::string computeHash(std::filesystem::path const& filePath) const;
  FileInfo createFileInfo(std::filesystem::path const& directory_entry);
  bool readRecord(std::string const& recordFile) const;

private:
  void setFileInfo(FileInfo& fi, std::filesystem::path const& p);
  std::string getFileName(std::filesystem::path const& p) const;
  std::string getFileExtension(std::filesystem::path const& p) const;
  u_int64_t getFileSize(std::filesystem::path const& p) const;
  std::filesystem::perms getPermissions(std::filesystem::path const& p) const;
  std::filesystem::file_time_type getLastModifiedTime(std::filesystem::path const& p) const;
  std::chrono::time_point<std::chrono::system_clock> recordTimestamp() const;
};

#endif
