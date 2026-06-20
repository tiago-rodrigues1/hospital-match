#include "./include/hospitalbed.hpp"

HospitalBed::HospitalBed(int id, std::string specialty, std::string hospital, Location loc) 
  : m_id(id), m_specialty(specialty), m_hospital(hospital), m_loc(loc) {}
