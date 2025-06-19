#ifndef SPELLCHECK_H
#define SPELLCHECK_H

#include <string>
#include <vector>
#include <algorithm>
#include "HashTable.h"

using namespace std;

// Function declarations for the spell check operations
vector<string> extraLetter(const HashTable &dict, const string& word);
vector<string> transposition(const HashTable &dict, string word);
vector<string> missingSpace(const HashTable &dict, string word);
vector<string> missingLetter(const HashTable &dict, string word);
vector<string> incorrectLetter(const HashTable &dict, string word);

// Function implementations

// Check if the word is in the dictionary
bool isWordInDict(const HashTable &dict, const string &word) {
    return dict.find(word);
}

// Function to check extraLetter case: find words by removing one letter
vector<string> extraLetter(const HashTable &dict, const string& word) {
    vector<string> matches;

    if (isWordInDict(dict, word)) {
        matches.push_back(word);  // Return the word if it's already in the dictionary
        return matches;
    }

    for (size_t i = 0; i < word.size(); ++i) {
        string modified = word.substr(0, i) + word.substr(i + 1);
        if (isWordInDict(dict, modified)) {
            matches.push_back(modified);
        }
    }

    // Return empty if no matches are found
    if (matches.empty()) {
        return matches;
    }

    sort(matches.begin(), matches.end());  // Sort alphabetically
    return matches;
}

// Function to check transposition case: find words by swapping adjacent letters
vector<string> transposition(const HashTable &dict, string word) {
    vector<string> matches;

    if (isWordInDict(dict, word)) {
        matches.push_back(word);
        return matches;
    }

    for (size_t i = 0; i < word.size() - 1; ++i) {
        string modified = word;
        swap(modified[i], modified[i + 1]);
        if (isWordInDict(dict, modified)) {
            matches.push_back(modified);
        }
    }

    if (matches.empty()) {
        return matches;
    }

    sort(matches.begin(), matches.end());  // Sort alphabetically
    return matches;
}

// Function to check missingSpace case: find pairs of words that can be created by inserting a space
vector<string> missingSpace(const HashTable &dict, string word) {
    vector<string> matches;

    if (isWordInDict(dict, word)) {
        matches.push_back(word);
        return matches;
    }

    for (size_t i = 1; i < word.size(); ++i) {
        string left = word.substr(0, i);
        string right = word.substr(i);
        if (isWordInDict(dict, left) && isWordInDict(dict, right)) {
            matches.push_back(left + " " + right);
        }
    }

    if (matches.empty()) {
        return matches;
    }

    sort(matches.begin(), matches.end());  // Sort alphabetically
    return matches;
}

// Function to check missingLetter case: find words by adding one letter
vector<string> missingLetter(const HashTable &dict, string word) {
    vector<string> matches;

    if (isWordInDict(dict, word)) {
        matches.push_back(word);
        return matches;
    }

    for (size_t i = 0; i <= word.size(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            string modified = word.substr(0, i) + c + word.substr(i);
            if (isWordInDict(dict, modified)) {
                matches.push_back(modified);
            }
        }
    }

    if (matches.empty()) {
        return matches;
    }

    sort(matches.begin(), matches.end());  // Sort alphabetically
    return matches;
}

// Function to check incorrectLetter case: find words by replacing one letter
vector<string> incorrectLetter(const HashTable &dict, string word) {
    vector<string> matches;

    if (isWordInDict(dict, word)) {
        matches.push_back(word);
        return matches;
    }

    for (size_t i = 0; i < word.size(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            if (word[i] == c) continue;  // Skip the same letter
            string modified = word;
            modified[i] = c;
            if (isWordInDict(dict, modified)) {
                matches.push_back(modified);
            }
        }
    }

    if (matches.empty()) {
        return matches;
    }

    sort(matches.begin(), matches.end());  // Sort alphabetically
    return matches;
}

#endif
