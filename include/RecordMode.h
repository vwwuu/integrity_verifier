#ifndef RECORDMODE_H
#define RECORDMODE_H

#include <iostream>
#include <string>

class RecordMode
{
 public:
  bool verifyDirectory(const std::string& targetDirectory) const;
};

#endif
