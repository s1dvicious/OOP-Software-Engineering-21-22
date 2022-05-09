#include "complexSeq.h"

void complexSeq::copyFrom(const complexSeq& other) {

	seq = new complex[other.size];
	size = other.size;
	for (size_t i = 0; i < size; ++i) {
		seq[i] = other.seq[i];
	}

}

void complexSeq::free() {
	delete[] seq;
	size = 0;
}

complexSeq::complexSeq(): seq(nullptr),size(0) {}

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
	seq = new complex[size];

	for (size_t i = 0; i < size; ++i) {
		ifs >> seq[i];
	}

	sortByModules();

}

std::ostream& operator<<(std::ostream& ofs, const complexSeq& obj) {
	for (size_t i = 0; i < obj.size; ++i) {
		ofs << obj.seq[i]<<"\t";
	}
	ofs << std::endl;
	for (size_t i = 0; i < obj.size; ++i) {
		ofs << obj.seq[i].getMod() << "\t";
	}

	std::cout << ">Successfully wrote to the file.";

	return ofs;
}

void complexSeq::swap(size_t i, size_t j) {
	complex temp = seq[i];
	seq[i] = seq[j];
	seq[j] = temp;
}

//Selection sort!

void complexSeq::sortByModules() {

	for (size_t i = 0; i < size-1; ++i) {
		size_t min_index = i;
		for (size_t j = i+1; j < size; ++j) 
			if (seq[min_index].mod > seq[j].mod) min_index = j;
		if (min_index != i) {
			swap(i, min_index);
		}
	}
}