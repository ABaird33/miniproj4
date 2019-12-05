#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <utility>
#include "Objects.h"

template<class C>
class Utility {
public:
  virtual C readFile(std::string filename) = 0;
  virtual std::pair<std::vector<Client>, std::vector<int>> readInfo(std::string filename, int problem) = 0;
  virtual std::unordered_map<string, std::pair<float, int>> readFines(std::string filename) = 0;
  virtual int readIncrease(std::string filename, int problem) = 0;
  
};

#endif