#include "ArrayList.h"
#include <iostream>
#include <assert.h>

template <class T>
ArrayList<T>::ArrayList() {
	size = 5;
	count = 0;
	arr = new T[size];
}

template <class T>
int ArrayList<T>::Length() {
	return count;
}


template <class T>
void ArrayList<T>::Expand() {
	size *= 2;
	T* tmp = new T[size];

	for (int i = 0; i < count; i++) {
		tmp[i] = arr[i];
	}

	delete[]arr;
	arr = tmp;
}

template <class T>
T ArrayList<T>::End() {
	return arr[count - 1];
}

template <class T>
void ArrayList<T>::Append(T value) {
	/*ofstream out;
	out.open("another.txt", ios::app);
	out.write((char*)&value, sizeof(value));
	out.close();*/

	if (count == size) {
		Expand();
	}

	arr[count] = value;
	count++;
}

template <class T>
T ArrayList<T>::At(int pos) {
	assert(pos >= 0 && pos < count);
	return arr[pos];
}

template <class T>
void ArrayList<T>::DeleteAt(int pos) {
	assert(pos >= 0 && pos < count);

	for (int i = pos; i < count - 1; i++) {
		arr[i] = arr[i + 1];
	}
	count--;
}

template <class T>
void ArrayList<T>::InsertAt(int pos, T value) {
	assert(pos >= 0 && pos < count);

	if (count == size) {
		Expand();
	}

	for (int i = count; i > pos; i--) {
		arr[i] = arr[i - 1];
	}

	arr[pos] = value;
	count++;
}

template <class T>
ArrayList<T>::~ArrayList() {

	delete[]arr;
}
