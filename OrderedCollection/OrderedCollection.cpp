#include "OrderedCollection.h"
#include <iostream>

using namespace std;

/*
Default Constructor
*/
OrderedCollection::OrderedCollection() {


	size = 0;
	basicSize = 8;
	first = 4;
	last = 3;
	Array = new int[8];
	for (int z = 0; z < basicSize; z++) {
		Array[z] = 0;
	}
}

/*
Copy Constructor
*/

OrderedCollection::OrderedCollection(const OrderedCollection& orderedcollection) {


	size = orderedcollection.size;
	basicSize = orderedcollection.basicSize;
	first = orderedcollection.first;
	last = orderedcollection.last;
	Array = new int[basicSize];

	for (int z = 0; z < basicSize; z++) {
		Array[z] = orderedcollection.Array[z];
	}
}

/*
Constructor taking an initial element
*/

OrderedCollection::OrderedCollection(int x) {


	size = 0;
	basicSize = 8;
	first = 4;
	last = 3;
	Array = new int[8];

	for (int z = 0; z < basicSize; z++) {
		Array[z] = 0;
	}

	insertAt(0, x);
}

OrderedCollection::~OrderedCollection() {
	delete[] Array;
}


/*
Assignment Operator for the class :operator=(const OrderedCollection&)
*/

OrderedCollection& OrderedCollection::operator=(const OrderedCollection& orderedcollection) {

	if (this != &orderedcollection) {
		size = orderedcollection.size;
		basicSize = orderedcollection.basicSize;
		last = orderedcollection.last;
		first = orderedcollection.first;
		delete[] Array;
		Array = new int[basicSize];

		for (int z = 0; z < basicSize; z++) {
			Array[z] = orderedcollection.Array[z];
		}

	}
	return *this;
}

/*
indexing operator for OrderedCollection instances : operator[](int)
*/

int& OrderedCollection::operator[](int idx) {
	if (idx < 0 || idx > last - first + 1) {
		std::cout << ".....Index is out of bounds....." << std::endl;
	}
	else {
		return Array[idx + first];
	}
}

/*
Public Functions for the class
*/

/*returns size of the OC wrt filled positions*/
int OrderedCollection::Size() {
	return size;
}

/*returns size of the OC wrt the entire capacity of the OC*/
int OrderedCollection::BasicSize() {
	return basicSize;
}

/* returns a boolean value indicating if the OC has any elements or not*/
bool OrderedCollection::isEmpty() {
	return (size == 0);
}

/* finds the element passed as argument in the array and returns the index*/

int OrderedCollection::find(int x) {
	for (int z = first; z < last + 1; ++z) {
		if (Array[z] == x)
			return z - first;
	}

	return -1;
}

OrderedCollection& OrderedCollection::iterate(int (*fn)(int)) {
	for (int z = first; z <= last; ++z) {
		Array[z] = fn(Array[z]);
	}

	return *this;
}


OrderedCollection& OrderedCollection::removeAt(int idx) {
	if (idx < 0 || idx > last - first + 1) {
		std::cout << ".....Index of out bounds....." << std::endl;
		return *this;
	}

	Array[first + idx] = 0;
	if (idx == 0) {
		first++;
	}
	else {
		if (idx == size + 1) {
			last--;
		}
		else {
			if (idx < size / 2) {
				shift(1, 0, idx);
				first++;

			}
			else {
				shift(-1, idx, size);
				last--;
			}
		}
	}

	for (int z = 0; z < first; z++) {
		Array[z] = 0;
	}

	for (int z = last + 1; z < basicSize; z++) {
		Array[z] = 0;
	}
	size--;
	return *this;
}

OrderedCollection& OrderedCollection::insertAt(int idx, int x) {
	if (idx < 0 || idx > last - first + 1) {
		std::cout << "......Index is out of bounds....." << std::endl;
		return *this;
	}


	if (Array[first + idx] == 0 && first + size < basicSize) {
		Array[first + idx] = x;
		last++;
	}
	else {
		if (first + idx >= 0 && Array[first + idx] == 0) {
			Array[first + idx] = x;
			last++;
		}
		else {
			bool shifted = false;
			if (idx < basicSize / 2) {
				shifted = shift(-1, 0, idx);
				if (shifted) {
					first--;
					last--;
				}

			}
			if (!shifted && first > idx) {
				shifted = shift(1, idx, size + 1);
				if (shifted) {
					first++;
					last++;
				}
			}
			if (!shifted) {
				if (first > idx) {
					shifted = shiftAtStart();
				}
				else {
					if (basicSize - size >= last - idx)
						shifted = shiftAtEnd();
				}
			}
			if (shifted) {
				Array[first + idx] = x;
				last++;
			}
			else {
				grow();
				if (first + idx >= 0 && Array[first + idx] == 0) {
					Array[first + idx] = x;
					last++;
				}
				else
					if (Array[first + idx] == 0 && first + size != basicSize) {
						Array[first + idx] = x;
						last++;
					}
					else {
						if (idx < basicSize / 2) {
							shifted = shift(-1, 0, idx);
							first--;
							last--;
						}
						else {
							shifted = shift(1, idx, size + 1);
							first++;
							last++;
						}
					}
				if (shifted) {
					Array[first + idx] = x;
					last++;
				}
			}
		}
	}

	size++;
	return *this;
}

/*protected functions*/

/*Grow function - adds additional region in the OC*/
void OrderedCollection::grow() {
	int* new_Array = new int[basicSize * 2];
	int cntr = 0;
	int new_first = (basicSize * 2) / 4;
	for (int z = first; z <= last; ++z) {
		new_Array[new_first + cntr] = Array[z];
		cntr++;
	}
	delete[] Array;
	first = new_first;
	Array = new_Array;
	last = size + first;
	basicSize = basicSize * 2;

	for (int z = 0; z < first; z++) {
		Array[z] = 0;
	}

	for (int z = last; z < basicSize; z++) {
		Array[z] = 0;
	}
}


/*Helper functions*/

bool OrderedCollection::shiftAtEnd() {
	if (Array[0] == 0) {
		int cntr = 0;
		while (Array[0] == 0) {
			for (int z = 0; z < basicSize; ++z) {
				if (z != basicSize)
					Array[z] = Array[z + 1];
				else
					Array[z] = 0;
			}
			cntr++;
			first--;
			last--;
		}
		for (int z = 0; z < first; z++) {
			Array[z] = 0;
		}

		for (int z = last+1; z < basicSize; z++) {
			Array[z] = 0;
		}
	}
	else {
		return false;
	}
	return true;
}


bool OrderedCollection::shiftAtStart() {
	if (Array[basicSize - 1] == 0) {
		int cntr = 0;
		while (Array[basicSize - 1] == 0) {
			for (int z = basicSize - 1; z >= 0; --z) {
				if (z != 0) {
					Array[z] = Array[z - 1];
				}
				else {
					Array[z] = 0;
				}
			}
			cntr++;
			first++;
			last++;
		}
		for (int z = 0; z < first; z++) {
			Array[z] = 0;
		}

		for (int z = last+1; z < basicSize; z++) {
			Array[z] = 0;
		}
	}
	else {
		return false;
	}
	return true;
}


bool OrderedCollection::shift(int direction, int start_idx, int end_idx) {
	if (direction == -1) {
		if (Array[0] == 0) {
			for (int z = first + start_idx -1; z <= first + end_idx; ++z) {
				Array[z - 1] = Array[z];
			}
		}
		else {
			return false;
		}
	}
	else
		if (direction == 1) {
			if (first + end_idx != basicSize && Array[first + end_idx] == 0) {
				for (int z = first + end_idx -1 ; z >=  start_idx -1 ; --z) {
					Array[z + 1] = Array[z];
				}
			}
			else {
				return false;
			}
		}

	for (int z = 0; z < first; z++) {
		Array[z] = 0;
	}

	for (int z = last+1; z < basicSize; z++) {
		Array[z] = 0;
	}

	return true;
}


void OrderedCollection::printOC() {
	std::cout << "\n" << std::endl;
	std::cout << "Values" << std::endl;
	std::cout << "[";
	for (int z = 0; z < basicSize; ++z) {
		std::cout << Array[z] << "\t";
	}
	std::cout << "]";
	std::cout << std::endl;
	std::cout << "Indices" << std::endl;
	std::cout << "<<";
	for (int z = 0; z < basicSize; ++z) {
		std::cout << z << "\t";
	}
	std::cout << ">>" << std::endl;
	std::cout << "\n" << std::endl;
}




int testfn(int x) {
	std::cout << x << " " << endl;
	return x *3;
}


int main() {
	
	/* Default constructor check*/
	OrderedCollection oc = OrderedCollection();
	oc.printOC();
	
	cout << "size: " << oc.Size() << endl; //Size() check
	cout << "basicSize: " << oc.BasicSize() << endl;  //BasicSize() check
	cout << "isempty array??? " << oc.isEmpty() << endl; //isEmpty() Check

	/*insertAt check*/
	for (int var = 0; var < 30; ++var) {
		oc.insertAt(var, var + 1);
		oc.printOC();
	}

	cout << "value 11 is found at index: " << oc.find(11) << endl;

	/*removeAt check*/
	cout << "Remove At testing:" << endl;
	oc.removeAt(7);
	oc.printOC();

	/*iterate check*/
	oc.iterate(*testfn);
	oc.printOC();

	/*operator assignment check : operator=(const OrderedCollection&)*/
	OrderedCollection oc2 = OrderedCollection(999);
	oc.operator = (oc2);
	oc.printOC();

	oc2.insertAt(0, 222);
	oc2.insertAt(0, 333);
	oc2.insertAt(0, 444);

	/*Operator[]  check*/
	oc2.printOC();
	std::cout << "Operator[] test:  " << oc2.operator[](1);
	return 0;

	/*copy constructor check*/

	OrderedCollection oc3 = OrderedCollection(oc2);
	oc3.printOC();

	/*Destructor check*/
	oc3.~OrderedCollection();
}