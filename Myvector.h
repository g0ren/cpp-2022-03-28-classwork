/*
 * Myvector.h
 *
 *  Created on: Mar 28, 2022
 *      Author: goren
 */

#ifndef MYVECTOR_H_
#define MYVECTOR_H_

class Myvector {
	int *_data;
	int _capacity;
	int _size;
	void realloc();
public:
	Myvector();
	virtual ~Myvector();
	Myvector(const Myvector &r);

	int size();
	int capacity();
	void push_back(int);
	int get(int);
	void set(int,int);
};

#endif /* MYVECTOR_H_ */
