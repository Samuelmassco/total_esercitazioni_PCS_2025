#include <iostream>
#include "src/utils.hpp"

int main() {
    size_t n;
    unsigned int* v1 = nullptr;
    unsigned int* v2 = nullptr;

    if (!ImportVectors("vectors.txt", n, v1, v2)) {
        std::cerr << "Erreur : lecture des vecteurs impossible." << std::endl;
        return 1;
    }

    unsigned int result = DotProduct(n, v1, v2);

    if (!ExportResult("dotProduct.txt", n, v1, v2, result)) {
        std::cerr << "Erreur : écriture du résultat impossible." << std::endl;
        delete[] v1;
        delete[] v2;
        return 1;
    }

    std::cout << "Produit scalaire : " << result << std::endl;

    delete[] v1;
    delete[] v2;
    return 0;
}
