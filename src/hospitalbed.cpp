#include "./include/hospitalbed.hpp"

HospitalBed::HospitalBed(std::string specialty, std::string hospital, Location loc) 
  : m_specialty(specialty), m_hospital(hospital), m_loc(loc) {}
