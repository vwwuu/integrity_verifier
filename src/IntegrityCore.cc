#include "IntegrityCore.h"
#include "ValidateMessage.h"
#include "status_out.h"
#include "Statuses.h"
#include "AcceptedFSType.h"
#include "FileInfo.h"
#include "DirectoryContent.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

#include <openssl/evp.h>

bool IntegrityCore::validatePath(std::filesystem::path const& p, AcceptedFSType fType) const {
  std::error_code ec;
  std::filesystem::file_status s = std::filesystem::symlink_status(p, ec);

  if (ec) { // handles exception
    std::cout << "Filesystem error: " << ec.message() << std::endl;
    return false;
  }
  if (!std::filesystem::exists(s)) return false;
  if (fType == AcceptedFSType::DIRECTORY && std::filesystem::is_directory(s)) return true;
  if (fType == AcceptedFSType::FILE && std::filesystem::is_regular_file(s)) return true;
  return false;
}

DirectoryContent IntegrityCore::scanDirectory(std::filesystem::path const& dPath) {
  DirectoryContent contents;
  if (!validatePath(dPath, AcceptedFSType::DIRECTORY)) { // validate if given path is a directory
    return contents;
  }
  contents.directoryPath = dPath;
  
  std::error_code ec;
  for (auto const& dir_entry : std::filesystem::directory_iterator(dPath, ec)) {
    const auto dirPath = dir_entry.path();
    if (validatePath(dirPath, AcceptedFSType::DIRECTORY)) {
      contents.subdirectories.push_back(scanDirectory(dirPath));
    }
    else if (validatePath(dirPath, AcceptedFSType::FILE)) {
      contents.files.push_back(createFileInfo(dirPath));
    }
  }
  std::sort(contents.subdirectories.begin(), contents.subdirectories.end(),
	    [](auto const& a, auto const& b) {
	      return a.directoryPath.string() < b.directoryPath.string();
	    });
  std::sort(contents.files.begin(), contents.files.end(),
            [](auto const &a, auto const &b) {
              return a.filePath.string() < b.filePath.string();
            });
  return contents;
}

FileInfo IntegrityCore::createFileInfo(std::filesystem::path const& p)
{
  FileInfo fileDetails;
  setFileInfo(fileDetails, p);
  return fileDetails;
}

void IntegrityCore::setFileInfo(FileInfo& fi, std::filesystem::path const& p) {
  fi.fileName = getFileName(p);
  fi.filePath = p.lexically_normal();
  fi.fileExtension = getFileExtension(p);
  fi.fileSize = getFileSize(p);
  fi.permissions = getPermissions(p);
  fi.fileHash = computeHash(p);
  fi.lastModified = getLastModifiedTime(p);
  fi.recordTimestamp = recordTimestamp();
}

std::string IntegrityCore::computeHash(std::filesystem::path const& filePath) {
  std::ifstream file(filePath, std::ios::binary);
  if (!file) {
    std::cout << "Error reading file" << std::endl;
    return "";
  }

  EVP_MD_CTX* ctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);

  std::vector<char> buffer(8192);
  while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
    EVP_DigestUpdate(ctx, buffer.data(), file.gcount());
  }

  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int length = 0;
  EVP_DigestFinal_ex(ctx, hash, &length);
  EVP_MD_CTX_free(ctx);

  std::ostringstream oss;
  oss << std::hex << std::setfill('0');
  
  for (unsigned int i = 0; i < length; ++i) {
    oss << std::setw(2) << static_cast<unsigned int>(hash[i]);
  }
  return oss.str();
}

std::string IntegrityCore::getFileName(std::filesystem::path const& p) const {
  return p.stem().string();
}

std::string IntegrityCore::getFileExtension(std::filesystem::path const& p) const {
  return p.extension().string();
}

u_int64_t IntegrityCore::getFileSize(std::filesystem::path const& p) const {
  return std::filesystem::file_size(p);
}

std::filesystem::perms IntegrityCore::getPermissions(std::filesystem::path const& p) const {
  return std::filesystem::status(p).permissions();
}

std::filesystem::file_time_type IntegrityCore::getLastModifiedTime(std::filesystem::path const& p) const {
  const auto lTime = std::filesystem::last_write_time(p);
  return lTime;
}

std::chrono::time_point<std::chrono::system_clock> IntegrityCore::recordTimestamp() const {
  return std::chrono::system_clock::now();
}
