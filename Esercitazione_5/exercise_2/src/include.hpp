#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// include/Cell0D.hpp
struct Cell0D {
    int id;
    int marker;
    double x;
    double y;
};

// include/Cell1D.hpp
struct Cell1D {
    int id;
    int marker;
    int origin;
    int end;
};

// include/Cell2D.hpp
struct Cell2D {
    int id;
    int marker;
    int numVertices;
    std::vector<int> vertices;
    int numEdges;
    std::vector<int> edges;
};

std::vector<Cell0D> loadCell0DData(const std::string& filePath); // Function declaration

#endif // INCLUDE_HPP