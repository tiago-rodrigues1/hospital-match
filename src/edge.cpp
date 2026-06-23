#include "./include/edge.hpp"
#include "edge.hpp"

Edge::Edge(size_t patientIdx, size_t bedIdx, double weight) :
  m_patientIndex(patientIdx), m_bedIndex(bedIdx), m_weight(weight) {}