#include "./include/patient.hpp"

Patient::Patient(std::string name, std::string specialty, int priority, Location loc) 
  : m_name(name), m_required_specialty(specialty), m_priority(priority), m_loc(loc) {}