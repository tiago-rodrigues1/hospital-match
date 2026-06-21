#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include "./common.hpp"

class Patient {
  private:
    int m_id;
    std::string m_name;
    std::string m_required_specialty;
    int m_priority;
    Location m_loc;
  public :
    Patient(int id, std::string name, std::string specialty, int priority, Location loc);

    // Construtor para o parser da OR-Library
    Patient(int id) 
        : m_id(id),
          m_name("P" + std::to_string(id + 1)), 
          m_required_specialty("Geral"), 
          m_priority(1), 
          m_loc({0.0, 0.0}) {}

    int id() const { return m_id; };
    std::string name() const { return m_name; };
    std::string required_specialty() const { return m_required_specialty; };
    int priority() const { return m_priority; };
    Location loc() const { return m_loc; };
    double lat() const { return m_loc.latitude; };
    double lng() const { return m_loc.longitude; };
    
};

#endif
