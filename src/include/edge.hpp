#ifndef EDGE_HPP
#define EDGE_HPP

#include "./patient.hpp"
#include "./hospitalbed.hpp"

class Edge {
  private:
    size_t m_patientIndex;
    size_t m_bedIndex;
    double m_weight;

  public:
    Edge(size_t patientIdx, size_t bedIdx, double weight);

    double weight() const { return m_weight; }
    size_t patientIdx() const { return m_patientIndex; }
    size_t bedIdx() const { return m_bedIndex; }
};

#endif