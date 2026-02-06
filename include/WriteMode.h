#ifndef WRITEMODE_H
#define WRITEMODE_H

#include "IntegrityCore.h"

class WriteMode
{
public:
  explicit WriteMode (IntegrityCore& core);

  private:
  IntegrityCore& core;
};

#endif
