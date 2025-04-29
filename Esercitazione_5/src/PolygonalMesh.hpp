#ifndef POLYGONALMESH_HPP
#define POLYGONALMESH_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <limits> 
namespace PolygonalLibrary {

constexpr double GEOMETRY_EPSILON = 1e-12;

struct Cell0D {
    int id;
    int marker;
    double x;
    double y;
};

struct Cell1D {
    int id;
    int marker;
    int origin;
    int end;
};

struct Cell2D {
    int id;
    int marker;
    std::vector<int> vertices;
    std::vector<int> edges;
};

class PolygonalMesh {
public:
    std::vector<Cell0D> cell0Ds;
    std::vector<Cell1D> cell1Ds;
    std::vector<Cell2D> cell2Ds;

    PolygonalMesh() {}
    ~PolygonalMesh() {}

    void verifyMarkers() {}
    void verifyEdgeLengths() {}

    void verifyPolygonAreas() {//there is a probleme idk what but this doesn't work yeah .... 
        std::cout << "Polygon Area Test:" << std::endl;
        bool polygons_ok = true;
        for (const auto& polygon : cell2Ds) {
            std::cout << "  Polygon ID: " << polygon.id << ", Vertices: ";
            for (int vertexId : polygon.vertices) {
                std::cout << vertexId << " ";
            }
            std::cout << std::endl;

            std::vector<Cell0D> polygon_points;
            try {
                for (int vertexId : polygon.vertices) {
                    Cell0D vertex = findCell0D(vertexId);
                    polygon_points.push_back(vertex);
                }
            } catch (const std::runtime_error& e) {
                std::cerr << "  Error: " << e.what() << std::endl;
                polygons_ok = false;
                continue; 
            }

            double area = calculatePolygonArea(polygon_points);
            std::cout << "  Area: " << std::setprecision(15) << area << std::endl;

            if (std::isnan(area) || std::isinf(area) || area < GEOMETRY_EPSILON) {
                std::cout << "  Polygon with ID: " << polygon.id << " has an invalid or near-zero area." << std::endl;
                polygons_ok = false;
            }
        }
        if (polygons_ok)
            std::cout << "All polygons have valid and non-zero area." << std::endl;
        else
            std::cout << "Some polygons have invalid or near-zero area." << std::endl;
    }

    void verifyMeshIntegrity() {}

private:
    Cell0D findCell0D(int id) const {
        for (const auto& cell : cell0Ds) {
            if (cell.id == id) {
                return cell;
            }
        }
        throw std::runtime_error("Cell0D with ID " + std::to_string(id) + " not found.");
    }


    double calculatePolygonArea(const std::vector<Cell0D>& points) const {
        double area = 0.0;
        int n = points.size();
        if (n < 3) return 0.0;

        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            area += (points[i].x * points[j].y) - (points[j].x * points[i].y);
        }
        return 0.5 * std::abs(area);
    }

    // Test collinearity of 3 points (useful for degenerate triangles)
    bool isCollinear(double x1, double y1, double x2, double y2, double x3, double y3, double tolerance = GEOMETRY_EPSILON) const {
        return std::abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) < tolerance;
    }

};

}

#endif