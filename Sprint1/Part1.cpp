#include <iostream>
#include "Part1.h"

int main() {
    int size;
    
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    
    // Create a dynamic array
    int* array = createArray(size);
    
    // Initialize the array
    initializeArray(array, size);
    
    // Print the array
    printArray(array, size);
    
    // Delete the array
    deleteArray(array);

    std::cout << "Array Deleted!";
    
    return 0;
}

// Function implementations
int* createArray(int size) {
    int* array = new int[size];
    return array;
}

void initializeArray(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = i;
    }
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void deleteArray(int* array) {
    delete[] array;
    array = nullptr;
}

