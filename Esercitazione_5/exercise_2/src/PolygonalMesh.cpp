#include "PolygonalMesh.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdexcept> // For exceptions

// --- Computational Geometry Helpers ---

// Function to calculate the signed area of a triangle
double signedTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3) {
    return 0.5 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
}

// Function to determine if three points are collinear (or nearly collinear)
bool isCollinear(double x1, double y1, double x2, double y2, double x3, double y3, double tolerance = 1e-10) {
    return std::abs(signedTriangleArea(x1, y1, x2, y2, x3, y3)) < tolerance;
}

PolygonalMesh::PolygonalMesh(const std::string& cell0DFilePath,
                             const std::string& cell1DFilePath,
                             const std::string& cell2DFilePath) :
    cell0Ds(loadCell0DData(cell0DFilePath)),
    cell1Ds(PolygonalMesh::loadCell1DData(cell1DFilePath)),
    cell2Ds(PolygonalMesh::loadCell2DData(cell2DFilePath)) {
    // Initialization of member variables
}

std::vector<Cell1D> PolygonalMesh::loadCell1DData(const std::string& cell1DFilePath) {
    std::vector<Cell1D> cell1Ds;
    std::ifstream file1D(cell1DFilePath);
    if (!file1D.is_open()) {
        throw std::runtime_error("Error: Unable to open file: " + cell1DFilePath);
    }

    std::string line;
    std::getline(file1D, line); // Skip header

    while (std::getline(file1D, line)) {
        std::stringstream ss(line);
        std::string value;
        Cell1D cell;

        std::getline(ss, value, ';');
        cell.id = std::stoi(value);

        std::getline(ss, value, ';');
        cell.marker = std::stoi(value);

        std::getline(ss, value, ';');
        cell.origin = std::stoi(value);

        std::getline(ss, value, ';');
        cell.end = std::stoi(value);

        cell1Ds.push_back(cell);
    }

    file1D.close();
    return cell1Ds;
}

std::vector<Cell2D> PolygonalMesh::loadCell2DData(const std::string& cell2DFilePath) {
    std::vector<Cell2D> cell2Ds;
    std::ifstream file2D(cell2DFilePath);
    if (!file2D.is_open()) {
        throw std::runtime_error("Error: Unable to open file: " + cell2DFilePath);
    }

    std::string line;
    std::getline(file2D, line); // Skip header

    while (std::getline(file2D, line)) {
        std::stringstream ss(line);
        std::string value;
        Cell2D cell;

        std::getline(ss, value, ';');
        cell.id = std::stoi(value);

        std::getline(ss, value, ';');
        cell.marker = std::stoi(value);

        std::getline(ss, value, ';');
        cell.numVertices = std::stoi(value);

        std::string verticesStr;
        std::getline(ss, verticesStr, ';');
        std::stringstream verticesSS(verticesStr);
        cell.vertices.clear();
        while (std::getline(verticesSS, value, ' ')) {
            int vertexId = std::stoi(value);
            cell.vertices.push_back(vertexId);
        }

        std::getline(ss, value, ';');
        cell.numEdges = std::stoi(value);

        std::string edgesStr;
        std::getline(ss, edgesStr, ';');
        std::stringstream edgesSS(edgesStr);
        cell.edges.clear();
        while (std::getline(edgesSS, value, ' ')) {
            cell.edges.push_back(std::stoi(value));
        }

        cell2Ds.push_back(cell);
    }

    file2D.close();
    return cell2Ds;
}

void PolygonalMesh::verifyMarkers() const {
    std::cout << "Verifying markers..." << std::endl;
    for (const auto& cell0D : cell0Ds) {
        if (cell0D.marker < 0 || cell0D.marker > 10) {
            std::cerr << "Warning: Invalid marker " << cell0D.marker << " in Cell0D " << cell0D.id << std::endl;
        }
    }
    for (const auto& cell1D : cell1Ds) {
        if (cell1D.marker < 0 || cell1D.marker > 10) {
            std::cerr << "Warning: Invalid marker " << cell1D.marker << " in Cell1D " << cell1D.id << std::endl;
        }
    }
    for (const auto& cell2D : cell2Ds) {
        if (cell2D.marker < 0 || cell2D.marker > 10) {
            std::cerr << "Warning: Invalid marker " << cell2D.marker << " in Cell2D " << cell2D.id << std::endl;
        }
    }
    std::cout << "Markers verified." << std::endl;
}

double PolygonalMesh::calculateEdgeLength(int originId, int endId) const {
    const Cell0D& origin = cell0Ds[originId];
    const Cell0D& end = cell0Ds[endId];
    return std::sqrt(std::pow(end.x - origin.x, 2) + std::pow(end.y - origin.y, 2));
}

void PolygonalMesh::verifyEdgeLengths() const {
    std::cout << "Verifying edge lengths..." << std::endl;
    for (const auto& cell1D : cell1Ds) {
        double length = calculateEdgeLength(cell1D.origin, cell1D.end);
        if (length == 0.0) {
            std::cerr << "Error: Edge " << cell1D.id << " has zero length." << std::endl;
        }
    }
    std::cout << "Edge lengths verified." << std::endl;
}

void PolygonalMesh::printPolygonCoordinates(int polygonId) const {
    if (polygonId < 0 || polygonId >= cell2Ds.size()) {
        std::cerr << "Error: Invalid polygon ID." << std::endl;
        return;
    }

    const Cell2D& polygon = cell2Ds[polygonId];
    std::cout << "Polygon " << polygonId << " Vertices Coordinates:\n";
    for (int vertexId : polygon.vertices) {
        if (vertexId > 0 && vertexId <= cell0Ds.size()) {
            const Cell0D& vertex = cell0Ds[vertexId - 1];
            std::cout << "(" << vertex.x << ", " << vertex.y << ") ";
        } else {
            std::cout << "(Invalid Vertex ID) ";
        }
    }
    std::cout << std::endl;
}

double PolygonalMesh::calculatePolygonArea(const std::vector<int>& vertexIds) const {
    if (vertexIds.size() < 3) return 0.0;

    double area = 0.0;
    int n = vertexIds.size();

    std::cout << "Calculating area for polygon with vertices:\n";

    std::vector<std::pair<double, double>> polygon_points;

    for (int i = 0; i < n; ++i) {
        int vertex_index = vertexIds[i] - 1; // Adjust for 1-based indexing

        // Robust bounds checking with exception:
        if (vertex_index < 0 || vertex_index >= cell0Ds.size()) {
            throw std::runtime_error("Error: Invalid vertex ID " + std::to_string(vertexIds[i]) +
                                     " in polygon " + std::to_string(i) + ". Aborting area calculation.");
        }

        const Cell0D& vertex = cell0Ds[vertex_index];
        polygon_points.push_back({vertex.x, vertex.y});
        std::cout << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    std::cout << std::endl;

    // Robust collinearity check and area calculation
    if (polygon_points.size() == 3 &&
        isCollinear(polygon_points[0].first, polygon_points[0].second,
                    polygon_points[1].first, polygon_points[1].second,
                    polygon_points[2].first, polygon_points[2].second)) {
        std::cerr << "Warning: Triangular polygon is collinear, area is zero.\n";
        return 0.0;
    } else if (polygon_points.size() > 2) {
        for (int i = 0; i < n; ++i) {
            area += (polygon_points[i].first * polygon_points[(i + 1) % n].second -
                     polygon_points[(i + 1) % n].first * polygon_points[i].second);
        }
        area = 0.5 * std::abs(area);
    }

    std::cout << "Calculated Area: " << std::fixed << std::setprecision(10) << area << std::endl;

    return area;
}

void PolygonalMesh::verifyPolygonAreas() const {
    std::cout << "Verifying polygon areas..." << std::endl;
    for (int i = 0; i < cell2Ds.size(); ++i) {
        const Cell2D& cell2D = cell2Ds[i];

        // Pre-calculation validation: Check vertex IDs
        bool valid = true;
        for (int vertexId : cell2D.vertices) {
            if (vertexId <= 0 || vertexId > cell0Ds.size()) {
                std::cerr << "Error: Invalid vertex ID " << vertexId
                          << " in polygon " << cell2D.id << ". Skipping area calculation.\n";
                printPolygonCoordinates(i);
                valid = false;
                break;
            }
        }

        if (valid) {
            try {
                double calculatedArea = calculatePolygonArea(cell2D.vertices);
                if (calculatedArea < 1e-10) {
                    std::cerr << "Error: Polygon " << cell2D.id << " has zero area." << std::endl;
                    printPolygonCoordinates(i);
                }
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << " (Polygon ID: " << i << ")\n";
            }
        }
    }
    std::cout << "Polygon areas verified." << std::endl;
}

void PolygonalMesh::verifyMeshIntegrity() const {
    std::cout << "Verifying mesh integrity..." << std::endl;
    // Placeholder - requires more specific integrity criteria
    std::cout << "Mesh integrity verification not fully implemented." << std::endl;
}