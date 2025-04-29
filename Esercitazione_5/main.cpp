/**
 * This program reads polygonal mesh data from CSV files, stores it using STL containers,
 * and performs several validation tests. The mesh data consists of 0D cells (points),
 * 1D cells (edges), and 2D cells (polygons).
 *
 * Project Plan:
 *
 * 1.  Data Structures:
 * -   Define structs for Cell0D, Cell1D, and Cell2D to represent the data
 * from the CSV files. These structs will hold information such as IDs,
 * markers, coordinates, vertex/edge connections, etc.
 *
 * 2.  PolygonalMesh Class:
 * -   Create a PolygonalMesh class to encapsulate the mesh data and provide
 * methods for loading, storing, and validating the mesh.
 * -   The class will contain STL containers (e.g., vectors, maps) to store
 * Cell0D, Cell1D, and Cell2D objects.
 *
 * 3.  CSV Data Loading:
 * -   Implement functions to read data from the CSV files (Cell0Ds.csv,
 * Cell1Ds.csv, Cell2Ds.csv).
 * -   These functions will parse each line of the CSV files, create the
 * appropriate Cell objects, and store them in the PolygonalMesh object.
 *
 * 4.  Mesh Validation Tests (implemented as PolygonalMesh methods):
 * -   Marker Test: Verify that all markers are stored correctly.
 * -   Edge Length Test: Ensure that the length of each edge is non-zero.
 * -   Polygon Area Test: Confirm that the area of each polygon is non-zero.
 * -   Mesh Integrity Test:  Validate that the loaded mesh matches the expected
 * configuration (comparison with provided images or specific geometric checks).
 *
 * 5.  Main Function:
 * -   Instantiate the PolygonalMesh object.
 * -   Call the CSV data loading functions to populate the mesh.
 * -   Execute the validation tests using the PolygonalMesh methods.
 * -   Output the results of the validation tests to the console.
 * -   Handle any errors or exceptions that may occur during the process.
 *
 * 6.  Error Handling:
 * -   Implement robust error handling to manage file I/O exceptions,
 * data parsing errors, and logical errors during mesh validation.
 * -   Provide informative error messages to the user.
 *
 * 7.  Output:
 * -   Display clear and concise results of the mesh validation tests.
 * -   Indicate whether each test passed or failed, and provide details
 * about any errors or inconsistencies found in the mesh data.
 */


 #include <iostream>
 #include "src/PolygonalMesh.hpp"
 #include "src/Utils.hpp"
 
 using namespace std;
 using namespace PolygonalLibrary;
 
 int main() {
     PolygonalMesh mesh;
     if (!ImportMesh(mesh, "Cell0Ds.csv", "Cell1Ds.csv", "Cell2Ds.csv")) {
         cerr << "Failed to import mesh. Aborting." << endl;
         return 1;
     }
 
     cout << "Cell0Ds size: " << mesh.cell0Ds.size() << endl;
     cout << "Cell1Ds size: " << mesh.cell1Ds.size() << endl;
     cout << "Cell2Ds size: " << mesh.cell2Ds.size() << endl;
 
     cout << endl << "Verifying mesh properties..." << endl;
 
     mesh.verifyMarkers();
     mesh.verifyEdgeLengths();
     mesh.verifyPolygonAreas();
     mesh.verifyMeshIntegrity();
     Cell2D testPolygon = mesh.cell2Ds[0];
     std::cout << "Testing polygon " << testPolygon.id << " with vertices: ";
     for (int vid : testPolygon.vertices) {
        Cell0D v = mesh.findCell0D(vid);
        std::cout << "(" << v.x << "," << v.y << ") ";
     }
     std::cout << std::endl;

 
     cout << endl << "Mesh verification complete." << endl;
 
     return 0;
 }