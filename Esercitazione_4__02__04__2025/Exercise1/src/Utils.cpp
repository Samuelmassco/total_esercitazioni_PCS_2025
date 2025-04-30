#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <vector>

bool ImportVectors(const std::string& inputFilePath,
                   size_t& n,
                   unsigned int*& v1,
                   unsigned int*& v2) {
    std::ifstream file(inputFilePath);
    if (!file.is_open()) return false;

    std::string line;
    std::vector<unsigned int> vec1, vec2;
    int lineCount = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        if (lineCount == 0) {
            iss >> n;
        } else if (lineCount == 1) {
            unsigned int val;
            while (iss >> val) vec1.push_back(val);
        } else if (lineCount == 2) {
            unsigned int val;
            while (iss >> val) vec2.push_back(val);
        }
        ++lineCount;
    }

    if (vec1.size() != n || vec2.size() != n) return false;

    v1 = new unsigned int[n];
    v2 = new unsigned int[n];

    for (size_t i = 0; i < n; ++i) {
        v1[i] = vec1[i];
        v2[i] = vec2[i];
    }

    return true;
}

unsigned int DotProduct(const size_t& n,
                        const unsigned int* const& v1,
                        const unsigned int* const& v2) {
    unsigned int result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

std::string ArrayToString(const size_t& n,
                          const unsigned int* const& v) {
    std::ostringstream oss;
    for (size_t i = 0; i < n; ++i) {
        oss << v[i];
        if (i < n - 1) oss << " ";
    }
    return oss.str();
}

bool ExportResult(const std::string& outputFilePath,
                  const size_t& n,
                  const unsigned int* const& v1,
                  const unsigned int* const& v2,
                  const unsigned int& dotProduct) {
    std::ofstream file(outputFilePath);
    if (!file.is_open()) return false;

    file << "# Size of the two vectors\n" << n << "\n";
    file << "# vector 1\n" << ArrayToString(n, v1) << "\n";
    file << "# vector 2\n" << ArrayToString(n, v2) << "\n";
    file << "# dot product\n" << dotProduct << "\n";

    return true;
}
