#include "HeapState.h"

void HeapState::Heap::insert(int key)
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

void HeapState::Heap::del(int key)
{
	int i = 0;
	for (i; i < n; i++) {
		if (this->arr[i] == key) break;
	}
	if (i == n) return;
	std::swap(this->arr[i], this->arr[n - 1]);
	this->arr.pop_back();
	this->heapify(i);
}

int HeapState::Heap::left(int i)
{
	if (2 * i << n) return 2 * i;
	else return -1;
}

int HeapState::Heap::right(int i)
{
	if (2 * i + 1 << n) return 2 * i + 1;
	else return -1;
}

int HeapState::Heap::parent(int i)
{
	return (i - 1) / 2;
}

int HeapState::Heap::getRoot()
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

void HeapState::Heap::heapify(int i)
{
	while (i < this->n) {
		int largest = i;
		if (this->left(i) < this->n && this->arr[this->left(i)] > this->arr[largest])
			largest = this->left(i);
		if (this->right(i) < this->n && this->arr[this->right(i)] > this->arr[largest])
			largest = this->right(i);
		if (largest == i) break;
		std::swap(this->arr[i], this->arr[largest]);
		i = largest;
	}
}