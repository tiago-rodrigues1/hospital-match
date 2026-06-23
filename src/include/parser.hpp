#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include "./patient.hpp"
#include "./hospitalbed.hpp"
#include "./edge.hpp"

class InstanceGAP {
    private:
        std::vector<Patient> m_patients;
        std::vector<HospitalBed> m_beds;
        std::vector<Edge> m_edges;
        std::vector<std::vector<int>> m_expandedCostMatrix;

    public:
        InstanceGAP(const std::vector<Patient>& patients, 
                    const std::vector<HospitalBed>& beds, 
                    const std::vector<std::vector<int>>& expandedCostMatrix);
        
        InstanceGAP() = default;

        void addPatient(const Patient& patient) { m_patients.push_back(patient); }
        void addBed(const HospitalBed& bed) { m_beds.push_back(bed); }
        void addEdge(const Edge& edge) { m_edges.push_back(edge); }
        void setExpandedCostMatrix(const std::vector<std::vector<int>>& matrix) { m_expandedCostMatrix = matrix; }
        void calculateEdgeWeights();

        const std::vector<Patient>& patients() const { return m_patients; }
        const std::vector<HospitalBed>& beds() const { return m_beds; }
        const std::vector<Edge>& edges() const { return m_edges; }
        const std::vector<std::vector<int>>& expandedCostMatrix() const { return m_expandedCostMatrix; }
};

#endif