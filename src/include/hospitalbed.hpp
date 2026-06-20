#ifndef HPBED_HPP
#define HPBED_HPP

#include <string>
#include "./common.hpp"


class HospitalBed {
  private:
    std::string m_specialty;
    std::string m_hospital;
    Location m_loc;

  public:
    HospitalBed(std::string specialty, std::string hospital, Location loc);

    std::string specialty() const { return m_specialty; };
    std::string hospital() const { return m_hospital; };
    Location loc() const { return m_loc; };
    double lat() const { return m_loc.latitude; };
    double lng() const { return m_loc.longitude; };
    
};

#endif
