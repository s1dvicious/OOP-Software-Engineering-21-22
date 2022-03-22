// [15.03] Task 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#pragma warning(disable:4996)
const int MAX_FIELD_LENGTH = 50;
const int MAX_BUFFER_SIZE = 128;

struct studentOOP {
	char firstName[MAX_FIELD_LENGTH];
	char secondName[MAX_FIELD_LENGTH];
	char email[MAX_FIELD_LENGTH];
	int fn;
};

size_t getStudentsNumber(const char* fileName) {
	size_t counter = 0;
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Error while opening the file.";
		return -1;
	}

	while (!file.eof()) {
		char line[MAX_BUFFER_SIZE];
		file.getline(line, MAX_BUFFER_SIZE);
		counter++;
	}

	file.close();
	return counter;
}


void readStudent(const char* line, studentOOP& student) {
	size_t index = 0;

	while (line[index] != ',') {
		student.firstName[index] = line[index];
		index++;
	}
	student.firstName[index] = '\0';
	index++;

	size_t secondNameCounter = 0;
	while (line[index] != ',') {
		student.secondName[secondNameCounter++] = line[index++];
	}
	student.secondName[secondNameCounter] = '\0';
	index++;

	size_t emailCounter = 0;
	while (line[index] != ',') {
		student.email[emailCounter++] = line[index++];
	}
	student.email[emailCounter] = '\0';
	index++;

	size_t fnCounter = 0;
	char fnStr[MAX_FIELD_LENGTH];
	while (line[index] != '\0') {
		fnStr[fnCounter++] = line[index++];
	}
	fnStr[fnCounter] = '\0';
	student.fn = atoi(fnStr);
}

size_t indexUntilFirstSpaceOrTerminatingNull(const char* input) {
	size_t counter = 0;
	while (*input != ' ' && *input != '\t' && *input != '\0') {
		++counter;
		++input;
	}
	return counter;
}

bool printStudentInfo(studentOOP* students, size_t stCount, int fn) {

	for (int i = 0; i < stCount; ++i) {
		if (students[i].fn == fn) {
			std::cout << "Name = " << students[i].firstName
				<< " " << students[i].secondName
				<< ", email = " << students[i].email
				<< ", FN = " << students[i].fn << std::endl;

			return true;
		}
	}
	return false;
}

bool saveStudentsToFile(studentOOP* students, size_t stCount, const char* fileName) {

	std::ofstream file(fileName);

	if (!file.is_open()) {
		return false;
	}

	file << "First Name, Second Name, Email, FN" << std::endl;

	for (int i = 0; i < stCount; ++i) {
		file<< students[i].firstName
			<< "," << students[i].secondName
			<< "," << students[i].email
			<< "," << students[i].fn;
		if (i != stCount - 1) {
			file << std::endl;
		}
	}
	return true;
}

bool editStudent(studentOOP* students, size_t stCount, int fn, const char* newName) {

	for (int i = 0; i < stCount-1; ++i) {
		if (students[i].fn == fn) {
			strcpy(students[i].firstName, newName);
			return true;
		}
	}
	return false;
}

int main()
{   
	std::cout << "Open file." << std::endl << ">";
	char fileName[MAX_FIELD_LENGTH];
	std::cin.getline(fileName, MAX_FIELD_LENGTH);


	size_t studentsCount = getStudentsNumber(fileName) - 1;

	if (studentsCount == 0) {
		std::cout << "Error while reading data.";
		return -1;
	}

	studentOOP* students = new studentOOP[studentsCount];

	std::ifstream file(fileName);
	
	if (!file.is_open()) {
		std::cout << "Error while opening the file.";
		return -1;
	}
	

	int counter = 1;
	while (!file.eof()) {
		char line[MAX_BUFFER_SIZE];
		file.getline(line, MAX_BUFFER_SIZE);

		if (counter == 1) {
			counter++;
			continue;
		}

		readStudent(line, students[counter - 2]);
		counter++;
	}
	std::cout << "File has been opened successfully." << std::endl;
	file.close();

	char commandLine[MAX_FIELD_LENGTH];

	do {
		std::cout << ">";

		std::cin.getline(commandLine, MAX_FIELD_LENGTH);

		size_t lineLength = strlen(commandLine);

		size_t firstArgSize = indexUntilFirstSpaceOrTerminatingNull(commandLine);
		char* firstArgument = new char[firstArgSize + 1];

		for (size_t i = 0; i < firstArgSize; i++) {
			firstArgument[i] = commandLine[i];
		}
		firstArgument[firstArgSize] = '\0';

		if (lineLength==strlen(firstArgument)) {
			continue;
		}

		size_t secondArgSize = lineLength - firstArgSize-1;
		char* secondArgument = new char[secondArgSize+1];

		for (size_t i = 0; i < secondArgSize; ++i) {
			secondArgument[i] = commandLine[firstArgSize + i + 1];
		}
		secondArgument[secondArgSize] = '\0';

		if (strcmp(firstArgument, "edit")==0) {

			size_t separator = indexUntilFirstSpaceOrTerminatingNull(secondArgument);

			size_t thirdArgSize = secondArgSize - separator;
			char* thirdArgument = new char[thirdArgSize + 1];

			for (int i = 0; i < thirdArgSize; ++i) {
				thirdArgument[i] = secondArgument[separator + 1 + i];
			}
			thirdArgument[thirdArgSize] = '\0';

			int fn = atoi(secondArgument);

			bool res = editStudent(students, studentsCount, fn, thirdArgument);

			if (!res) {
				std::cout << "Student with " << fn << " cannot be found!";
			}

			delete[] thirdArgument;
		}
		else if (strcmp(firstArgument, "print") == 0) {
			int fn = atoi(secondArgument);

			bool res=printStudentInfo(students, studentsCount, fn);

			if (!res) {
				std::cout << "Student with FN " << fn << " cannot be found."
					<<std::endl;
			}

		}
		else if (strcmp(firstArgument, "save") == 0) {
			bool res = saveStudentsToFile(students, studentsCount, secondArgument);

			if (!res) {
				std::cout << "Error saving the students!" << std::endl;
			}
			else {
				std::cout << "Students have been successfully saved." << std::endl;
			}

		}

		delete[] firstArgument;
		delete[] secondArgument;

	} while (strcmp(commandLine,"quit"));



	delete[] students;
	return 0;
}

