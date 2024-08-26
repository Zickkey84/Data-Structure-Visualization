#include "HashGraph.h"

int Hash::hashCode(int x) {return x % this->size;}

bool Hash::Insert(int x)
{
	int index = hashCode(x);
	while (this->hashArr[index] != -1) {
		index++;
		if (index == this->size) index = 0;
		if (index == hashCode(x)) return false;
	}
	this->hashArr[index] = x;
	return true;
}

bool Hash::Delete(int x)
{
	int index = hashCode(x);
	while (this->hashArr[index] != x) {
		index++;
		if (index == this->size) index = 0;
		if (index == hashCode(x)) return false;
	}
	this->hashArr[index] = -1;
	return true;
}

int Hash::Search(int x)
{
	int index = hashCode(x);
	while (this->hashArr[index] != x) {
		index++;
		if (index == this->size) index = 0;
		if (index == hashCode(x)) return -1;
	}
	return index;
}
