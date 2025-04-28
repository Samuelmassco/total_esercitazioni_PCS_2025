#include "include.hpp" // Or #include "src/Utils.hpp" if you move the declaration
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Utils.hpp"

std::vector<Cell0D> loadCell0DData(const std::string& filePath) {
    std::vector<Cell0D> cell0Ds;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        return cell0Ds;
    }

    std::string line;
    std::getline(file, line);
    Cell0D cell;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;

        std::getline(ss, value, ';');
        cell.id = std::stoi(value);

        std::getline(ss, value, ';');
        cell.marker = std::stoi(value);

        std::getline(ss, value, ';');
        cell.x = std::stod(value);

        std::getline(ss, value, ';');
        cell.y = std::stod(value);

        cell0Ds.push_back(cell);
    }

    file.close();
    return cell0Ds;
}