#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include "./common.hpp"

class Patient {
  private:
    std::string m_name;
    std::string m_required_specialty;
    int m_priority;
    Location m_loc;
  public :
    Patient(std::string name, std::string specialty, int priority, Location loc);

    std::string name() const { return m_name; };
    std::string required_specialty() const { return m_required_specialty; };
    int priority() const { return m_priority; };
    Location loc() const { return m_loc; };
    double lat() const { return m_loc.latitude; };
    double lng() const { return m_loc.longitude; };

};

#endif
