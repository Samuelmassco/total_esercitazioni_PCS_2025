#ifndef POLYGONALMESH_HPP
#define POLYGONALMESH_HPP

#include <vector>
#include <string>
#include "include.hpp"

class PolygonalMesh {
public:
    PolygonalMesh(const std::string& cell0DFilePath,
                  const std::string& cell1DFilePath,
                  const std::string& cell2DFilePath);

    // Mesh property verification methods
    void verifyMarkers() const;
    void verifyEdgeLengths() const;
    void verifyPolygonAreas() const;
    void verifyMeshIntegrity() const; 

    // Added these functions:
    int getNumCell0Ds() const { return cell0Ds.size(); }
    int getNumCell1Ds() const { return cell1Ds.size(); }
    int getNumCell2Ds() const { return cell2Ds.size(); }

private:
    std::vector<Cell0D> cell0Ds;
    std::vector<Cell1D> cell1Ds;
    std::vector<Cell2D> cell2Ds;

    // Helper functions for calculations
    double calculateEdgeLength(int originId, int endId) const;
    double calculatePolygonArea(const std::vector<int>& vertexIds) const;

    std::vector<Cell1D> loadCell1DData(const std::string& cell1DFilePath);
    std::vector<Cell2D> loadCell2DData(const std::string& cell2DFilePath);
    void printPolygonCoordinates(int polygonId) const;
};

#endif // POLYGONALMESH_HPP