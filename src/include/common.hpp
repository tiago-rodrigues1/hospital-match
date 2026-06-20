#ifndef COMMON_HPP
#define COMMON_HPP

#include <cmath>

struct Location {
  double latitude;
  double longitude;

  double getDistanceTo(Location loc) {
    return std::sqrt(std::pow(loc.latitude - latitude, 2) + std::pow(loc.longitude - longitude, 2));
  }
};

#endif
