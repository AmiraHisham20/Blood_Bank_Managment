#pragma once
template <class T>
class ArrayList
{
	T* arr;
	int size;
	int count;

public:
	ArrayList();
	int Length();
	void Append(T value);
	T At(int pos);
	//void display();
	T End();
	void DeleteAt(int pos);
	void InsertAt(int pos, T value);
	~ArrayList();
private:
	void Expand();
};

