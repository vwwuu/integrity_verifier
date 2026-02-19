#include "include/TestHelpers.h"
#include <iostream>
#include <system_error>

namespace TestHelpers {
  void createFile(std::filesystem::path const& p, std::string_view pContents) {
    std::ofstream newFile(p);
    newFile << pContents;
  }

  bool compareFileInfo (FileInfo const& f1, FileInfo const& f2) {
    if (f1.fileName != f2.fileName) return false;
    if (f1.filePath != f2.filePath) return false;
    if (f1.fileExtension != f2.fileExtension) return false;
    return true;
  }

  void contentsOut(DirectoryContent const& dc, int _indent) {
    std::string indent(_indent, ' ');

    if (_indent==0) {
      std::cout << "Root Directory: " << dc.directoryPath.string() << "\n";
    } else {
      std::cout << indent << "Directory: " << dc.directoryPath.string() << "\n";
    }
    
    // Files
    std::cout << indent << "[Files]\n";
    if (dc.files.size() == 0) {
      std::cout << indent << "NO FILES\n";
    } else {
      std::cout << indent << "Num of files: " << dc.files.size() << '\n';
      for (auto const &fi : dc.files) {
        TestHelpers::fiOut(std::cout, fi, _indent);
      }
    }
    std::cout << '\n';
    
    // Subdirectories
    std::cout << indent << "[Subdirectories]\n";
    if (dc.subdirectories.size() == 0) {
      std::cout << indent << "NO SUBDIRECTORIES\n";
    } else {
      std::cout << indent << "Num of subdirectories: " << dc.subdirectories.size() << '\n';
      for (auto &sd : dc.subdirectories) {
	contentsOut(sd, _indent+4);
	std::cout << "\n";
      }
    }
  }
  
  std::ostream& fiOut(std::ostream& os, const FileInfo& fi, int _indent) {
    std::string indent(_indent, ' ');
    os << indent << "Name: " << fi.fileName << "\n"
       << indent << "Path: " << fi.filePath.string() << "\n"
       << indent << "Extension: " << fi.fileExtension << "\n"
       << indent << "Size: " << fi.fileSize << "\n"
       << indent << "Permissions: " << permsToString(fi.permissions) << "\n"
       << indent << "Hash: " << fi.fileHash << "\n";
      //       << " Last Modified: " << fi.lastModified << "\n"
      //       << " Timestamp: " << fi.recordTimestamp << "\n";
    return os;
  }

  std::string permsToString(std::filesystem::perms p) {
    std::string s;
    s += (p & std::filesystem::perms::owner_read)  != std::filesystem::perms::none ? 'r' : '-';
    s += (p & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? 'w' : '-';
    s += (p & std::filesystem::perms::owner_exec)  != std::filesystem::perms::none ? 'x' : '-';

    s += (p & std::filesystem::perms::group_read)  != std::filesystem::perms::none ? 'r' : '-';
    s += (p & std::filesystem::perms::group_write) != std::filesystem::perms::none ? 'w' : '-';
    s += (p & std::filesystem::perms::group_exec)  != std::filesystem::perms::none ? 'x' : '-';

    s += (p & std::filesystem::perms::others_read)  != std::filesystem::perms::none ? 'r' : '-';
    s += (p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? 'w' : '-';
    s += (p & std::filesystem::perms::others_exec)  != std::filesystem::perms::none ? 'x' : '-';

    return s;
  }
}
