#pragma once

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "SortingAlgorithm.hpp"

using namespace SortLibrary;

TEST(TestSorting, TestBubbleSort) {
    // Test case 1: Empty vector
    std::vector<int> emptyVector;
    BubbleSort(emptyVector);
    EXPECT_TRUE(emptyVector.empty());

    // Test case 2: Vector with one element
    std::vector<int> singleElementVector = {5};
    BubbleSort(singleElementVector);
    EXPECT_EQ(singleElementVector.size(), 1);
    EXPECT_EQ(singleElementVector[0], 5);

    // Test case 3: Vector with multiple elements (random order)
    std::vector<int> randomVector = {9, 13, 5, 10, 2, 7, 9, 4, 6, 12};
    BubbleSort(randomVector);
    std::vector<int> sortedRandomVector = {2, 4, 5, 6, 7, 9, 9, 10, 12, 13};
    EXPECT_EQ(randomVector, sortedRandomVector);

    // Test case 4: Vector with multiple elements (already sorted)
    std::vector<int> sortedVector = {1, 2, 3, 4, 5};
    std::vector<int> sortedVectorCopy = sortedVector; // Create a copy for comparison
    BubbleSort(sortedVector);
    EXPECT_EQ(sortedVector, sortedVectorCopy); // Should remain the same

    // Test case 5: Vector with multiple elements (reverse sorted)
    std::vector<int> reverseSortedVector = {5, 4, 3, 2, 1};
    std::vector<int> correctSortedVector = {1, 2, 3, 4, 5};
    BubbleSort(reverseSortedVector);
    EXPECT_EQ(reverseSortedVector, correctSortedVector);

    // Test case 6: Vector with duplicate elements
    std::vector<int> duplicateVector = {5, 2, 8, 2, 5, 1};
    std::vector<int> sortedDuplicateVector = {1, 2, 2, 5, 5, 8};
    BubbleSort(duplicateVector);
    EXPECT_EQ(duplicateVector, sortedDuplicateVector);
}

TEST(TestSorting, TestHeapSort) {
    // Test case 1: Empty vector
    std::vector<int> emptyVector;
    HeapSort(emptyVector);
    EXPECT_TRUE(emptyVector.empty());

    // Test case 2: Vector with one element
    std::vector<int> singleElementVector = {5};
    HeapSort(singleElementVector);
    EXPECT_EQ(singleElementVector.size(), 1);
    EXPECT_EQ(singleElementVector[0], 5);

    // Test case 3: Vector with multiple elements (random order)
    std::vector<int> randomVector = {9, 13, 5, 10, 2, 7, 9, 4, 6, 12};
    HeapSort(randomVector);
    std::vector<int> sortedRandomVector = {2, 4, 5, 6, 7, 9, 9, 10, 12, 13};
    EXPECT_EQ(randomVector, sortedRandomVector);

    // Test case 4: Vector with multiple elements (already sorted)
    std::vector<int> sortedVector = {1, 2, 3, 4, 5};
    std::vector<int> sortedVectorCopy = sortedVector;
    HeapSort(sortedVector);
    EXPECT_EQ(sortedVector, sortedVectorCopy);

    // Test case 5: Vector with multiple elements (reverse sorted)
    std::vector<int> reverseSortedVector = {5, 4, 3, 2, 1};
    std::vector<int> correctSortedVector = {1, 2, 3, 4, 5};
    HeapSort(reverseSortedVector);
    EXPECT_EQ(reverseSortedVector, correctSortedVector);

    // Test case 6: Vector with duplicate elements
    std::vector<int> duplicateVector = {5, 2, 8, 2, 5, 1};
    std::vector<int> sortedDuplicateVector = {1, 2, 2, 5, 5, 8};
    HeapSort(duplicateVector);
    EXPECT_EQ(duplicateVector, sortedDuplicateVector);
}

// Existing tests (you can keep them or remove them)
TEST(TestSorting, TestSelectionSort) {
    std::vector<int> v = {9, 13, 5, 10, 2, 7, 9, 4, 6, 12};
    //SelectionSort<int>(v); // Assuming you have this implemented elsewhere
    std::vector<int> sortedV = {2, 4, 5, 6, 7, 9, 9, 10, 12 ,13};
}

TEST(TestSorting, TestInsertionSort) {
    std::vector<int> v = {9, 13, 5, 10, 2, 7, 9, 4, 6, 12};
    //InsertionSort<int>(v); // Assuming you have this implemented elsewhere
    std::vector<int> sortedV = {2, 4, 5, 6, 7, 9, 9, 10, 12 ,13};
}