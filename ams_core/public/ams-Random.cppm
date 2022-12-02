module;
#include "ams/ams_core_export.h"

#ifndef AMS_MODULES_STD
#include <cstdint>
#endif

export module ams:Random;
#ifndef AMS_MODULES_STD
import <random>;
import <memory>;
#else
import std;
#endif


namespace ams {
  
class Random {
  struct Random_impl;
  std::unique_ptr<Random_impl> pImpl;

public:
  
};
  
}

