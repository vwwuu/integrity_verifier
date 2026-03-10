#ifndef INTEGRITY_CORE_H
#define INTEGRITY_CORE_H

#include <filesystem>
#include <string>
#include <chrono>

#include "AcceptedFSType.h"
#include "FileInfo.h"
#include "DirectoryContent.h"

class IntegrityCore
{
 public:
  bool validatePath(std::filesystem::path const& p, AcceptedFSType fType) const;
  DirectoryContent scanDirectory(std::filesystem::path const& dPath);
  FileInfo createFileInfo(std::filesystem::path const& directory_entry);

private:
  void setFileInfo(FileInfo& fi, std::filesystem::path const& p);
  static std::string computeHash(std::filesystem::path const& filePath);
  static std::string getFileName(std::filesystem::path const& p);
  static std::string getFileExtension(std::filesystem::path const& p);
  static u_int64_t getFileSize(std::filesystem::path const& p);
  static std::filesystem::perms getPermissions(std::filesystem::path const& p);
  static std::filesystem::file_time_type getLastModifiedTime(std::filesystem::path const& p);
  static std::chrono::time_point<std::chrono::system_clock> recordTimestamp();
};

#endif
