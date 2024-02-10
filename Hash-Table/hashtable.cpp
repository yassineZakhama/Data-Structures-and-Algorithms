#include "hashtable.h"
#include <iostream>

HashTable::HashTable(int _size, double threshold)
	: size{_size}, elements{0},collisionCount{0}, threshold_rehashing{threshold}
{
	hashTable =  new std::vector<int>(_size);

	for (auto it = hashTable->begin(); it != hashTable->end() ; ++it)
		*it = -1;
}

HashTable::~HashTable()
{
	delete hashTable;
}

// Berechnung des Hashwertes mit quadr. Sondieren
int HashTable::hashValue(int item)
{
	int i = 0;

	while (hashTable->at(((item + i * i) % size)) != -1) {
		++i;
		++collisionCount;
	}
	
	return (item + (i * i)) % size;
}

void HashTable::rehashing()
{
	// new size
	size = get_next_Prime(size * 2);

	HashTable* new_ht = new HashTable(size);

	// insert old items in new table
	for (auto it = hashTable->begin(); it != hashTable->end(); ++it)
	{
		if (*it != -1)
		{
			new_ht->insert(*it);
		}		
	}
	collisionCount = new_ht->getCollisionCount();

	delete hashTable;
	hashTable = new_ht->hashTable;
}

int HashTable::insert(int item)
{
	hashTable->at(hashValue(item)) = item;
	++elements;

	double faktor = elements / static_cast<double>(size);

	if (faktor >= threshold_rehashing)
		rehashing();

	return 1;	
}


int HashTable::at(int i)
{
	return hashTable->at(i);
}

int HashTable::getCollisionCount()
{
	return this->collisionCount;
}

int HashTable::getSize()
{
	return this->size;
}

int HashTable::getElements()
{
	return this->elements;
}

int HashTable::get_next_Prime(int x)
{
	x = x + 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x += 1;
	}
}

