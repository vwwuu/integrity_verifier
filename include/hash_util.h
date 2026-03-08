#ifndef HASH_UTIL
#define HASH_UTIL

#include "openssl/sha.h"

int sha256_file(char* path, char outputBuffer[65]);

#endif
