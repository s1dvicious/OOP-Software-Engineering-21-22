// [15.03] Task 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

const int MAX_BUFFER = 128;

bool copyContents(const char* source, const char* dest) {
    std::ifstream inputFile(source);
    std::ofstream outputFile(dest);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error while opening the files";
        return false;
    }

    while (!inputFile.eof()) {
        char line[MAX_BUFFER];
        inputFile.getline(line, MAX_BUFFER);
        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();
    return true;
}


int main()
{  
    if (!copyContents("myFile.txt","myNewFile.txt")) {
        std::cout << "Error copying the contents.";
        return -1;
    }
    if (copyContents("myFile.txt", "myNewFile.txt")) {
        std::cout << "Content succesfully copied";
    }

    return 0;
}


