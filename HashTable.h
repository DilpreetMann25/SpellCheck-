#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

class HashTable {
private:
    std::string* hashArray;     // Array to hold the hash table entries
    int tableSize;              // Size of the hash table
    int currentSize;            // Number of elements in the hash table
    int secondaryPrime;         // Second prime number for double hashing

    // Helper function for deep copying the hash table
    void deepCopy(const HashTable& other);

    // Check if a number is prime
    bool isPrime(int n) const;

    // Get the next prime number greater than or equal to n
    int nextPrime(int n) const;

    // Primary hash function
    int hashFunction(const std::string& word) const;

    // Secondary hash function for collision resolution
    int secondHash(const std::string& word) const;

    // Resize the hash table when the load factor exceeds 0.67
    void resize();

public:
    // Default constructor
    HashTable();

    // Constructor to create a hash table of size 2n (smallest prime >= 2n)
    HashTable(int n);

    // Copy constructor - deep copy of another hash table
    HashTable(const HashTable& other);

    // Destructor - deallocate memory
    ~HashTable();

    // Assignment operator - deep copy of another hash table
    HashTable& operator=(const HashTable& other);

    // Insert a word into the hash table
    void insert(const std::string& word);

    // Find a word in the hash table
    bool find(const std::string& word) const;

    // Get the current size of the hash table (number of items)
    int size() const;

    // Get the maximum size of the hash table (array size)
    int maxSize() const;

    // Get the load factor of the hash table
    double loadFactor() const;
};

#endif
