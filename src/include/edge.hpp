#ifndef EDGE_HPP
#define EDGE_HPP

#include "./patient.hpp"
#include "./hospitalbed.hpp"

class Edge {
  private:
    Patient* m_patient;
    HospitalBed* m_bed;
    double m_weight;

  public:
    Edge(Patient& patient, HospitalBed& bed, double weight);

    double weight() const { return m_weight; }
    const Patient& patient() const { return *m_patient; }
    const HospitalBed& bed() const { return *m_bed; }

    void setWeight(double weight) { m_weight = weight; }
    void setPatient(Patient& patient) { m_patient = &patient; }
    void setBed(HospitalBed& bed) { m_bed = &bed; }
};

#endif