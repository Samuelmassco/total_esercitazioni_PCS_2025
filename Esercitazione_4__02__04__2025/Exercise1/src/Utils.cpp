#include "Utils.hpp"

#include "iostream"
#include "fstream"
#include "sstream"

using namespace std;

int foo(ClassObj obj)
{
    return obj.a;
}

bool ImportVectors(const string& inputFilePath,
                   size_t& n,
                   unsigned int*& v1,
                   unsigned int*& v2)
{
    return false;
}


unsigned int DotProduct(const size_t& n,
                        const unsigned int* const& v1,
                        const unsigned int* const& v2)
{
    return 0;
}


bool ExportResult(const string& outputFilePath,
                  const size_t& n,
                  const unsigned int* const& v1,
                  const unsigned int* const& v2,
                  const unsigned int& dotProduct)
{
    // Open File
    ofstream file;
    file.open(outputFilePath);

    if (file.fail())
    {
        cerr<< "file open failed"<< endl;
        return false;
    }

    file << "# Size of the two vectors"<< endl;
    file << n << endl;

    file << "# vector 1"<< endl;
    for (unsigned int i = 0; i < n; i++)
        file << (i != 0 ? " " : "") << v1[i];
    file << endl;

    file << "# vector 2 "<< endl;
    for (unsigned int i = 0; i < n; i++)
        file << (i != 0 ? " " : "") << v2[i];
    file << endl;

    file << "# dot product"<< endl;
    file << dotProduct<< endl;

    // Close File
    file.close();

    return true;
}

string ArrayToString(const size_t& n,
                     const unsigned int* const& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();
}
