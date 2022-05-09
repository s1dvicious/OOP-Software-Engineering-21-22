#include "complexSeq.h"

void complexSeq::copyFrom(const complexSeq& other) {

	set = new complex[other.size];
	size = other.size;
	for (size_t i = 0; i < size; ++i) {
		set[i] = other.set[i];
	}

}

void complexSeq::free() {
	delete[] set;
	size = 0;
}

complexSeq::complexSeq(): set(nullptr),size(0) {}

complexSeq::complexSeq(const complexSeq& toCopy) {

	copyFrom(toCopy);

}

complexSeq& complexSeq::operator=(const complexSeq& rhs) {

	if (this != &rhs) {

		free();
		copyFrom(rhs);

	}

	return *this;
}

complexSeq::~complexSeq() {
	free();
}


size_t complexSeq::getSize(){
	return this->size;
}

complexSeq::complexSeq(std::ifstream& ifs) {

	ifs >> size;
	set = new complex[size];

	for (size_t i = 0; i < size; ++i) {
		ifs >> set[i];
	}

	sortByModules();

}

std::ostream& operator<<(std::ostream& ofs, const complexSeq& obj) {
	for (size_t i = 0; i < obj.size; ++i) {
		ofs << obj.set[i]<<"\t";
	}
	ofs << std::endl;
	for (size_t i = 0; i < obj.size; ++i) {
		ofs << obj.set[i].getMod() << "\t";
	}

	std::cout << ">Successfully wrote to the file.";

	return ofs;
}

void complexSeq::swap(size_t i, size_t j) {
	complex temp = set[i];
	set[i] = set[j];
	set[j] = temp;
}

//Selection sort!

void complexSeq::sortByModules() {

	for (size_t i = 0; i < size-1; ++i) {
		size_t min_index = i;
		for (size_t j = i+1; j < size; ++j) 
			if (set[min_index].mod > set[j].mod) min_index = j;
		if (min_index != i) {
			swap(i, min_index);
		}
	}
}