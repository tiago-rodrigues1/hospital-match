#include "./include/patient.hpp"

Patient::Patient(int id, std::string name, std::string specialty, int priority, Location loc) 
  : m_id(id), m_name(name), m_required_specialty(specialty), m_priority(priority), m_loc(loc) {}