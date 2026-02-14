#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <map>
#include "../include/FileInfo.h"

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
  
  bool getDirectoryTestHelper(
			      const std::map<std::filesystem::path, FileInfo>& m1,
			      const std::map<std::filesystem::path, FileInfo>& m2
			      ) {
    if (m1.size() != m2.size()) {
      return false;
    }
    
    for (const auto& [path, m1Info] : m1) {
      auto m2Path = m2.find(path);
      if (m2Path == m2.end()) return false;
      
      const FileInfo m2Info = m2Path->second;
      if (!compareFileInfo(m1Info, m2Info)) {
	return false;
      }
    }
    return true;
  }
}

#endif
