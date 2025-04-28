// 1 Develop C++ implementations of both algorithms within a modular `SortLibrary`.
//2 Experiment Design:Create a program main.cpp` to generate diverse test data (random, sorted, reverse-sorted vectors) and control vector size via command-line arguments.
//3 measurement: Use C++'s <chrono> library to precisely measure the execution time of each algorithm under different conditions.
// 4 Employ GoogleTest to write unit tests that rigorously validate the correctness of the sorting implementations.
// 5 Correlate the observed performance with the theoretical time complexities of O(n^2) for BubbleSort and O(n log n) for HeapSort.




#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>  
#include <algorithm>
#include <random>   
#include "src/SortingAlgorithm.hpp" // Include the sorting algorithm implementations

using namespace std;
using namespace std::chrono;
using namespace SortLibrary; // Use the namespace for the sorting functions

//  vector of random integers
vector<int> generateRandomVector(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000); 

    vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = dist(gen);
    }
    return vec;
}

// Function to generate a vector of sorted integers
vector<int> generateSortedVector(int size) {
    vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = i + 1;
    }
    return vec;
}

// Function to generate a vector of reverse sorted integers
vector<int> generateReverseSortedVector(int size) {
    vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = size - i;
    }
    return vec;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <vector_size>" << endl;
        return 1; 
    }

    int vectorSize = atoi(argv[1]); // Convert the command-line argument to an integer

    if (vectorSize <= 0) {
        cerr << "Error: Vector size must be a positive integer." << endl;
        return 1;
    }

    // Generate vectors
    vector<int> randomVector = generateRandomVector(vectorSize);
    vector<int> sortedVector = generateSortedVector(vectorSize);
    vector<int> reverseSortedVector = generateReverseSortedVector(vectorSize);

    // --- BubbleSort ---
    cout << "--- BubbleSort ---" << endl;

    // Random Vector
    vector<int> tempVector = randomVector; // Create a copy to preserve the original
    auto start = high_resolution_clock::now();
    BubbleSort(tempVector);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Random Vector: " << duration.count() << " microseconds" << endl;

    // Sorted Vector
    tempVector = sortedVector;
    start = high_resolution_clock::now();
    BubbleSort(tempVector);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Sorted Vector: " << duration.count() << " microseconds" << endl;

    // Reverse Sorted Vector
    tempVector = reverseSortedVector;
    start = high_resolution_clock::now();
    BubbleSort(tempVector);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Reverse Sorted Vector: " << duration.count() << " microseconds" << endl;


    // --- HeapSort ---
    cout << "\n--- HeapSort ---" << endl;

    // Random Vector
    tempVector = randomVector;
    start = high_resolution_clock::now();
    HeapSort(tempVector);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Random Vector: " << duration.count() << " microseconds" << endl;

    // Sorted Vector
    tempVector = sortedVector;
    start = high_resolution_clock::now();
    HeapSort(tempVector);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Sorted Vector: " << duration.count() << " microseconds" << endl;

    // Reverse Sorted Vector
    tempVector = reverseSortedVector;
    start = high_resolution_clock::now();
    HeapSort(tempVector);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Reverse Sorted Vector: " << duration.count() << " microseconds" << endl;

    return 0;
}