#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "./include/patient.hpp"
#include "./include/hospitalbed.hpp"
#include "./include/parser.hpp"
#include "parser.hpp"

std::vector<InstanceGAP> parserORLibraryGAP(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<InstanceGAP> instances;

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        exit(1);
    }

    int numProblems;
    file >> numProblems;

    for (int p = 0; p < numProblems; p++) {
        int m, n;
        file >> m >> n;

        InstanceGAP instance;

        for (int i = 0; i < n; i++) {
            instance.addPatient(Patient(i));
        }

        std::vector<std::vector<int>> costs(m, std::vector<int>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                file >> costs[i][j];
            }
        }

        // Ignora a matriz de Recursos Consumidos
        int garbage;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                file >> garbage;
            }
        }

        int currentId = 0;
        std::vector<int> capacities(m);
        std::vector<int> bedToHospitalIndex;

        for (int i = 0; i < m; i++) {
            file >> capacities[i];

            for (int j = 0; j < capacities[i]; j++) {
                instance.addBed(HospitalBed(currentId++, i));
                bedToHospitalIndex.push_back(i);
            }
        }

        int totalBeds = instance.beds().size();
        std::vector<std::vector<int>> localMatrix(n, std::vector<int>(totalBeds));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < totalBeds; j++) {
                int hospitalIndex = bedToHospitalIndex[j];
                localMatrix[i][j] = costs[hospitalIndex][i]; 
            }
        }

        instance.setExpandedCostMatrix(localMatrix);

        instances.push_back(instance);
    }

    file.close();
    
    return instances;
}

void InstanceGAP::calculateEdgeWeights() {
    for (size_t i = 0; i < m_patients.size(); i++) {
        for (size_t j = 0; j < m_patients.size(); j++) {
            auto patient = m_patients[i];
            auto bed = m_beds[j];

            if (patient.required_specialty() == bed.specialty()) {
                double distance = patient.loc().getDistanceTo(bed.loc());
                double weight = distance / patient.priority();

                addEdge(Edge(i, j, weight));
            }
        }
    }
}

int main() {
    std::string arquivoTeste = "./instances/gapa.txt"; 
    
    std::vector<InstanceGAP> meusTestes = parserORLibraryGAP(arquivoTeste);

    if (!meusTestes.empty()) {
        std::cout << "Leitura concluída com sucesso!" << std::endl;
        std::cout << "O arquivo continha " << meusTestes.size() << " instâncias de teste." << std::endl;
        
        InstanceGAP& primeira = meusTestes[0];
        std::cout << "--- Primeira Instância ---" << std::endl;
        std::cout << "Total de Pacientes: " << primeira.patients().size() << std::endl;
        std::cout << "Total de Hospitais (Agentes): " << primeira.beds().back().id() + 1 << std::endl;
        std::cout << "Total de Leitos Expandidos: " << primeira.beds().size() << std::endl;
        std::cout << "Total de arestas: " << primeira.edges().size() << std::endl;
    }

    return 0;
}