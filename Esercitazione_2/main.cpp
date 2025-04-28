#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <numbers>
#include <cstdio>
#include <fstream>
#include <stack>
#include <vector>

//hello my name is samuel coriat



 
double mapValue(double x) {//mapping from [-2,5] to [-1, 2] using basic algebra
    return (x + 1) / 3; // Exemple de transformation pour ajuster l'intervalle
}

//first we take then value from teh file then pass them in mapValue,
// then we are going to store the values in a stack then we compute the average and finally write everythong on the file




int exo__2() {
    std::ifstream inputFile("data.txt");
    std::ofstream outputFile("result.txt");
    
    if (inputFile.fail()) {//verification thath the files are there else stop return error
        std::cerr << "Erreur : Impossible d'ouvrir le fichier data.txt" << std::endl;
        return 1;
    }
    if (outputFile.fail()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier result.txt" << std::endl;
        return 1;
    }
    
    std::stack<double> values__stack;// where we store the values 
    std::vector<double> mappedValues__stack;
    double value;
    
    while (inputFile >> value) {
        double mapped = mapValue(value);//the new value
        values__stack.push(mapped);
        mappedValues__stack.push_back(mapped);
    }
    
    inputFile.close();
    
    
    outputFile << " average value of the n mapped value " << std::endl;
    double sum = 0.0;
    for (size_t i = 0; i < mappedValues__stack.size(); ++i) {
        sum += mappedValues__stack[i];
        double average = sum / (i + 1);
        outputFile << (i + 1) << " " << average << std::endl;
    }
    
    outputFile.close();
    
    return 0;
}



int main()
{
    exo__2();
    return 0;
}
