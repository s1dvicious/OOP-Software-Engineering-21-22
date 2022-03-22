// [15.03] Task 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>

const int MAX_BUFFER = 128;

int main()
{
	std::ifstream file("[15.03] Task 1.cpp");

	if (!file.is_open()) {
		std::cout << "Error while opening the file.";
		return -1;
	}

	while (!file.eof()) {
		char line[MAX_BUFFER];
		file.getline(line, MAX_BUFFER);
		std::cout << line<<std::endl;
	}

	file.close();

	return 0;
}

