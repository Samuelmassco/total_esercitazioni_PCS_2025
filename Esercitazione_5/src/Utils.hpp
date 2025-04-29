
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "PolygonalMesh.hpp" // Include PolygonalMesh definitions

namespace PolygonalLibrary {

bool ImportMesh(PolygonalMesh& mesh,
                const std::string& cell0DFile,
                const std::string& cell1DFile,
                const std::string& cell2DFile);

} // namespace PolygonalLibrary

#endif