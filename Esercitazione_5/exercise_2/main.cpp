#include <iostream>
#include "PolygonalMesh.hpp"
// #include "src/Utils.hpp" // Not needed in main.cpp

int main() {
    try {
        PolygonalMesh mesh("Cell0Ds.csv", "Cell1Ds.csv", "Cell2Ds.csv");

        std::cout << "Cell0Ds size: " << mesh.getNumCell0Ds() << std::endl;
        std::cout << "Cell1Ds size: " << mesh.getNumCell1Ds() << std::endl;
        std::cout << "Cell2Ds size: " << mesh.getNumCell2Ds() << std::endl;

      
        std::cout << "Verifying mesh properties..." << std::endl;

        mesh.verifyMarkers();
        mesh.verifyEdgeLengths();
        mesh.verifyPolygonAreas();
        mesh.verifyMeshIntegrity();

        std::cout << "Mesh verification complete." << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}