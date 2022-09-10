/*
 * Myvector.cpp
 *
 *  Created on: Mar 28, 2022
 *      Author: goren
 */

#include "Myvector.h"
#include <algorithm>

Myvector::Myvector() {
	_data = new int[1];
	_capacity = 1;
	_size = 0;
}

Myvector::Myvector(const Myvector &r) :
		_capacity(r._capacity), _size(r._size) {
	//_capacity=r._capacity;
	//_size=r._size;
	_data = new int[_capacity];
	std::copy(r._data, r._data + r._capacity, _data);
}

Myvector::~Myvector() {
	delete[] _data;
}

int Myvector::size() {
	return _size;
}

int Myvector::capacity() {
	return _capacity;
}

void Myvector::realloc() {
	int *new_data = new int[_capacity * 2];
	std::copy(_data, _data + _capacity, new_data);
	delete[] _data;
	_data = new_data;
	_capacity *= 2;
}

void Myvector::push_back(int e) {
	_data[_size] = e;
	_size++;
}

int Myvector::get(int pos) {
	return _data[pos];
}

void Myvector::set(int pos, int e) {
	_data[pos] = e;
}
