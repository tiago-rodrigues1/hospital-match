#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "./include/common.hpp"
#include "./include/parser.hpp"
#include "./include/algorithms.hpp"
#include "./include/edge.hpp"

void usage() {
  std::cout << "Usage: hospital-match <parser> <input_file>\n"
    << "Options:\n"
    << "--help/-h Print this help text.\n"
    << "-d <input_file> Use the OR-Library dense matrix instance parser.\n"
    << "-s <input_file> Use the OR-Library sparse matrix instance parser.\n"
    << "-r <input_file> Use the real-world problem parser (non-OR-Library instances).\n";
}

RunningOpt process_arguments(int argc, char* argv[]) {
  RunningOpt runningOpt;

  for (int i = 1; i < argc; i++) {
    std::string currentArg = argv[i];

    if (currentArg == "-h" || currentArg == "--help") {
      usage();
      exit(EXIT_SUCCESS);
    } else if (currentArg == "-d") {
      runningOpt.parser = OR_LIB_DENSE;
    } else if (currentArg == "-s") {
      runningOpt.parser = OR_LIB_SPARSE;
    } else if (currentArg == "-r") {
      runningOpt.parser = NON_OR_LIB_RP;
    } else {
      std::cerr << "Invalid argument. Use -h for help.\n";
      exit(EXIT_FAILURE);
    }

    if (i + 1 >= argc) {
      std::cerr << "A path for input file is required. Use -h for help.\n";
      exit(EXIT_FAILURE);
    }

    runningOpt.inputPath = argv[i + 1];
    i += 1;
  }

  return runningOpt;
}

std::string get_output_filename(const std::string& path) {
  std::string filename = std::filesystem::path(path).filename().string();
  std::string outputPrefix = "output_";

  return outputPrefix + filename;
}

void write_data(
  const RunningOpt& runningOpt,
  const Instance& instance,
  int totalCost,
  int executionTime,
  const std::vector<Edge>& edges
) {
  std::string outputFilename = get_output_filename(runningOpt.inputPath);
  std::ofstream file(outputFilename);

  if (!file.is_open()) {
    std::cerr << "Erro ao criar arquivo de output\n";
    exit(EXIT_FAILURE);
  }

  file << "patients_number, beds_number, total_cost, execution_time\n";
  file << instance.patients().size() << ", ";
  file << instance.beds().size() << ", ";
  file << totalCost << ", ";
  file << executionTime << "\n";

  if (runningOpt.parser == NON_OR_LIB_RP) {
    file << "- allocations\n";

    for (const Edge& edge : edges) {
      Patient p = instance.patients().at(edge.patientIdx());
      HospitalBed h = instance.beds().at(edge.bedIdx());

      file << "[" << p.name() << "; " << p.required_specialty() << "; " << p.priority() << "] -> ";
      file << "[" << h.hospital() << "; " << h.specialty() << "; BED: " << h.id() << "];";
    }
  }

  std::cout << "> Dados gravados em " << outputFilename << "\n";
}

int main(int argc, char* argv[]) {
  RunningOpt userOptions = process_arguments(argc, argv);
  Instance instance = Instance::parse(userOptions);

  if (instance.patients().empty()) {
    std::cerr << "Houve algum erro durante a leitura do arquivo\n";
    exit(EXIT_FAILURE);
  }

  int numPatients = instance.patients().size();
  int numBeds = instance.beds().size();
  std::vector<std::vector<int>> costMatrix = instance.expandedCostMatrix();

  std::vector<int> p = hungarianAlgorithm(instance.expandedCostMatrix(), std::max(numPatients, numBeds));
  std::vector<Edge> validAllocations = extractValid(p, costMatrix, instance.patients(), instance.beds());
  int totalCost = calculateTotalCost(validAllocations);
  int executionTime = 100;

  std::cout << "Arquivo lido com sucesso!" << std::endl;
  std::cout << "Total de Pacientes: " << numPatients << std::endl;
  std::cout << "Total de Leitos: " << numBeds << std::endl;
  std::cout << "Custo do Paciente 0 para Leito 0: " << costMatrix[0][0] << std::endl;
  std::cout << "Custo total: " << totalCost << std::endl;
  std::cout << "Tempo de processamento: " << executionTime << std::endl;

  write_data(userOptions, instance, totalCost, executionTime, validAllocations);

  return 0;
}