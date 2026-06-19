#include "./include/graph.hpp"

Edge::Edge(Patient& patient, HospitalBed& bed, double weight)
  : m_patient(&patient), m_bed(&bed), m_weight(weight) {}