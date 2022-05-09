#ifndef COMPLEXSEQ_H
#define COMPLEXSEQ_H
#include "Compl.h"


class complexSeq {
	complex* set;
	size_t size;

	void copyFrom(const complexSeq&);
	void free();

	void swap(size_t, size_t);
	void sortByModules();
public:

	complexSeq();
	complexSeq(const complexSeq&);
	complexSeq& operator=(const complexSeq&);
	~complexSeq();

	complexSeq(std::ifstream&);

	size_t getSize();

	friend std::ostream& operator<<(std::ostream&, const complexSeq&);

};

#endif