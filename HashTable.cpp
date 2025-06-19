#include "HashTable.h"
#include <iostream>
#include <string>  // Add this line
#include <cmath>

HashTable::HashTable() {
    tableSize = 101;
    hashArray = new std::string[tableSize]();
    currentSize = 0;
    secondaryPrime = nextPrime(tableSize / 2 + 1);
}

// Constructor to create a hash table of size 2n (smallest prime >= 2n)
HashTable::HashTable(int n) {
    tableSize = nextPrime(2 * n);
    hashArray = new std::string[tableSize]();
    currentSize = 0;
    secondaryPrime = nextPrime(tableSize / 2 + 1);
}

// Copy constructor - deep copy of another hash table
HashTable::HashTable(const HashTable& other) {
    deepCopy(other);
}

// Destructor - deallocate memory
HashTable::~HashTable() {
    delete[] hashArray;
}

// Assignment operator - deep copy of another hash table
HashTable& HashTable::operator=(const HashTable& other) {
    if (this != &other) {
        delete[] hashArray;
        deepCopy(other);
    }
    return *this;
}

// Deep copy helper function
void HashTable::deepCopy(const HashTable& other) {
    tableSize = other.tableSize;
    currentSize = other.currentSize;
    secondaryPrime = other.secondaryPrime;
    hashArray = new std::string[tableSize];
    for (int i = 0; i < tableSize; ++i) {
        hashArray[i] = other.hashArray[i];
    }
}

// Check if a number is prime
bool HashTable::isPrime(int n) const {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Get the next prime number greater than or equal to n
int HashTable::nextPrime(int n) const {
    while (!isPrime(n)) {
        ++n;
    }
    return n;
}

// Primary hash function - Horner’s method
int HashTable::hashFunction(const std::string& word) const {
    long long string_value = 0;
    for (size_t i = 0; i < word.length(); ++i) {
        char ch = word[i];
        int asc = ch - 96;  // ASCII value for lowercase letters
        string_value = (string_value * 33 + asc) % tableSize;
    }
    return string_value % tableSize;
}

// Secondary hash function for collision resolution
int HashTable::secondHash(const std::string& word) const {
    long long string_value = 0;
    for (size_t i = 0; i < word.length(); ++i) {
        char ch = word[i];
        int asc = ch - 96;
        string_value = (string_value * 33 + asc) % tableSize;
    }
    return secondaryPrime - (string_value % secondaryPrime);
}

// Insert a word into the hash table
void HashTable::insert(const std::string& word) {
    if (loadFactor() > 0.67) {
        resize();
    }

    int index = hashFunction(word);
    int stepSize = secondHash(word);

    while (!hashArray[index].empty()) {
        if (hashArray[index] == word) {
            return;  // No duplicates allowed
        }
        index = (index + stepSize) % tableSize;
    }

    hashArray[index] = word;
    currentSize++;
}

// Find a word in the hash table
bool HashTable::find(const std::string& word) const {
    int index = hashFunction(word);
    int stepSize = secondHash(word);

    while (!hashArray[index].empty()) {
        if (hashArray[index] == word) {
            return true;
        }
        index = (index + stepSize) % tableSize;
    }
    return false;
}

// Resize the hash table when the load factor exceeds 0.67
void HashTable::resize() {
    int oldSize = tableSize;
    tableSize = nextPrime(2 * tableSize);  // Find next prime greater than twice the size
    secondaryPrime = nextPrime(tableSize / 2 + 1);

    std::string* oldArray = hashArray;
    hashArray = new std::string[tableSize]();

    for (int i = 0; i < oldSize; ++i) {
        if (!oldArray[i].empty()) {
            insert(oldArray[i]);  // Re-insert elements
        }
    }

    delete[] oldArray;  // Free old memory
}

// Get the current size of the hash table (number of items)
int HashTable::size() const {
    return currentSize;
}

// Get the maximum size of the hash table (array size)
int HashTable::maxSize() const {
    return tableSize;
}

// Get the load factor of the hash table
double HashTable::loadFactor() const {
    return static_cast<double>(currentSize) / tableSize;
}