#ifndef COMMON_HPP
#define COMMON_HPP

#include <cmath>
#include <cstdint>
#include <filesystem>

struct Location {
  double latitude;
  double longitude;

  double getDistanceTo(Location loc) {
    return std::sqrt(std::pow(loc.latitude - latitude, 2) + std::pow(loc.longitude - longitude, 2));
  }
};

enum parserType_e : std::uint8_t {
  OR_LIB_DENSE = 0,
  OR_LIB_SPARSE,
  NON_OR_LIB_RP 
};

struct RunningOpt {
  parserType_e parser;
  std::string inputPath;
};

#endif
