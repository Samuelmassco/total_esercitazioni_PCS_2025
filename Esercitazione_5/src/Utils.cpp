#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace PolygonalLibrary {

bool ImportMesh(PolygonalMesh& mesh,
                const std::string& cell0DFile,
                const std::string& cell1DFile,
                const std::string& cell2DFile) {
    try {
        std::ifstream file0D(cell0DFile);
        if (!file0D.is_open())
            throw std::runtime_error("Could not open file: " + cell0DFile);

        std::ifstream file1D(cell1DFile);
        if (!file1D.is_open())
            throw std::runtime_error("Could not open file: " + cell1DFile);

        std::ifstream file2D(cell2DFile);
        if (!file2D.is_open())
            throw std::runtime_error("Could not open file: " + cell2DFile);

        std::string line;
        std::string cell_component;

        // Load Cell0Ds
        std::getline(file0D, line); // Skip header
        while (std::getline(file0D, line)) {
            std::stringstream ss(line);
            Cell0D cell;

            std::getline(ss, cell_component, ';');
            cell.id = std::stoi(cell_component);

            std::getline(ss, cell_component, ';');
            cell.marker = std::stoi(cell_component);

            std::getline(ss, cell_component, ';');
            cell.x = std::stod(cell_component);

            std::getline(ss, cell_component, ';');
            cell.y = std::stod(cell_component);

            mesh.cell0Ds.push_back(cell);
        }
        file0D.close();

        // Load Cell1Ds
        std::getline(file1D, line); // Skip header
        while (std::getline(file1D, line)) {
            std::stringstream ss(line);
            Cell1D cell;

            std::getline(ss, cell_component, ';');
            cell.id = std::stoi(cell_component);

            std::getline(ss, cell_component, ';');
            cell.marker = std::stoi(cell_component);

            std::getline(ss, cell_component, ';');
            cell.origin = std::stoi(cell_component);

            std::getline(ss, cell_component, ';');
            cell.end = std::stoi(cell_component);

            mesh.cell1Ds.push_back(cell);
        }
        file1D.close();

        // Load Cell2Ds
        std::getline(file2D, line); // Skip header
        while (std::getline(file2D, line)) {
            std::stringstream ss(line);
            Cell2D cell;

            std::getline(ss, cell_component, ';');
            cell.id = std::stoi(cell_component);

            std::getline(ss, cell_component, ';');
            cell.marker = std::stoi(cell_component);

            std::getline(ss, cell_component, ';');
            std::getline(ss, cell_component, ';'); // Skip NumVertices

            std::getline(ss, cell_component, ';');
            std::stringstream vertices_ss(cell_component);
            std::string vertex_id;
            while (std::getline(vertices_ss, vertex_id, ';')) {
                cell.vertices.push_back(std::stoi(vertex_id));
            }

            std::getline(ss, cell_component, ';');
            std::getline(ss, cell_component, ';'); // Skip NumEdges

            std::getline(ss, cell_component, ';');
            std::stringstream edges_ss(cell_component);
            std::string edge_id;
            while (std::getline(edges_ss, edge_id, ';')) {
                cell.edges.push_back(std::stoi(edge_id));
            }

            mesh.cell2Ds.push_back(cell);
        }
        file2D.close();
        return true;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error importing mesh: " << e.what() << std::endl;
        return false;
    }
}

} // namespace PolygonalLibrary