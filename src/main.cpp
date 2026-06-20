#include <iostream>

#include "./include/patient.hpp"
#include "./include/hospitalbed.hpp"
#include "./include/graph.hpp"

int main() {
  Patient p1 = Patient("Tiago", "cardiovascular", 2, {-5.842302, -35.245529});
  HospitalBed h1 = HospitalBed("cardiovascular", "HUOL", {-5.8320526, -35.2080847});

  std::cout << "Distância " << p1.name() << " -> " << h1.hospital() << ": ";
  std::cout << p1.loc().getDistanceTo(h1.loc()) << "\n";

  double distance = p1.loc().getDistanceTo(h1.loc());
  double weight = distance / p1.priority();

  Edge e1 = Edge(p1, h1, weight);

  std::cout << "Custo de transferência: " << e1.weight() << "\n";

  return 0;
}