#ifndef HPBED_HPP
#define HPBED_HPP

#include <string>
#include "./common.hpp"


class HospitalBed {
  private:
    int m_id;
    std::string m_specialty;
    std::string m_hospital;
    Location m_loc;

  public:
    HospitalBed(int id, std::string specialty, std::string hospital, Location loc);

    // Construtor para o parser da OR-Library
    HospitalBed(int idBed, int idHospital)
        : m_id(idBed), 
          m_specialty("Geral"), 
          m_hospital("H" + std::to_string(idHospital + 1)), 
          m_loc({0.0, 0.0}) {}

    int id() const { return m_id; };
    std::string specialty() const { return m_specialty; };
    std::string hospital() const { return m_hospital; };
    Location loc() const { return m_loc; };
    double lat() const { return m_loc.latitude; };
    double lng() const { return m_loc.longitude; };

};

#endif
