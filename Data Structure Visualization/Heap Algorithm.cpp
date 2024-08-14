#include "HeapGraph.h"

void Heap::insert(int key)
{
	if (this->capacity == this->n) return;
	int i = this->n;
	this->arr.push_back(key);
	this->n++;
	while (i > 0 && this->arr[i] > this->arr[this->parent(i)]) {
		std::swap(this->arr[i], this->arr[this->parent(i)]);
		i = this->parent(i);
	}
}

bool Heap::del(int key)
{
	int i = 0;
	for (i; i < n; i++) {
		if (this->arr[i] == key) break;
	}
	if (i == n) return false;
	std::swap(this->arr[i], this->arr[n - 1]);
	this->arr.pop_back(); n--;
	this->heapify(i);
	return true;
}

int Heap::left(int i)
{
	if (2 * i + 1 < n) return 2 * i + 1;
	else return -1;
}

int Heap::right(int i)
{
	if (2 * i + 2 < n) return 2 * i + 2;
	else return -1;
}

int Heap::parent(int i)
{
	return (i - 1) / 2;
}

int Heap::getRoot()
{
	if (this->n == 0) return -1;
	int root = this->arr[0];
	this->arr[0] = this->arr[n - 1];
	this->arr.pop_back();
	this->n--;
	int i = 0;
	this->heapify(i);
	return root;
}

void Heap::heapify(int i)
{
	while (i < this->n) {
		int largest = i;
		if (this->left(i) != -1 && this->arr[this->left(i)] > this->arr[largest])
			largest = this->left(i);
		if (this->right(i) != -1 && this->arr[this->right(i)] > this->arr[largest])
			largest = this->right(i);
		if (largest == i) break;
		std::swap(this->arr[i], this->arr[largest]);
		i = largest;
	}
}

void Heap::makeHeap()
{
	for (int i = n - 2 / 2; i >= 0; i--) heapify(i);
}
