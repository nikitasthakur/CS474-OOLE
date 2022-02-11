#pragma once

class OrderedCollection {
public:
	OrderedCollection();
	OrderedCollection(int);
	OrderedCollection(const OrderedCollection&);
	virtual ~OrderedCollection();

	int Size();
	int BasicSize();
	int find(int);
	bool isEmpty();


	OrderedCollection& insertAt(int, int);
	OrderedCollection& removeAt(int);
	OrderedCollection& iterate(int(*fn)(int));

	OrderedCollection& operator=(const OrderedCollection&);
	int& operator[](int);

	void printOC();

	int first;
	int last;
	int size;
	int basicSize;
	int* Array;

protected:
	void grow();

	/*helper functions*/
	bool shiftAtStart();
	bool shiftAtEnd();
	bool shift(int direction,int start_idx,int end_idx);

};