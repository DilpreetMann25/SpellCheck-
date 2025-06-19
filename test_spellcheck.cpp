#include "HashTable.h"
#include "spellcheck.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void loadDictionary(HashTable& dict, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string word;
    while (getline(file, word)) {
        if (!word.empty()) {
            dict.insert(word);
        }
    }
}

void printSuggestions(const string& label, const vector<string>& suggestions) {
    cout << label << ": ";
    if (suggestions.empty()) {
        cout << "(no suggestions)";
    } else {
        for (const string& s : suggestions) {
            cout << s << " ";
        }
    }
    cout << endl;
}

void testWord(const HashTable& dict, const string& word) {
    cout << "\nTesting word: \"" << word << "\"\n";

    if (dict.find(word)) {
        cout << "  Result: Word is correctly spelled.\n";
        return;
    }

    for (size_t i = 0; i < word.size(); ++i) {
        char ch = word[i];
        // Code
    }

    printSuggestions("  Extra Letter", extraLetter(dict, word));
    printSuggestions("  Transposition", transposition(dict, word));
    printSuggestions("  Missing Space", missingSpace(dict, word));
    printSuggestions("  Missing Letter", missingLetter(dict, word));
    printSuggestions("  Incorrect Letter", incorrectLetter(dict, word));
}

int main() {
    HashTable dict;
    loadDictionary(dict, "wordlist1000.txt");

    cout << "Dictionary loaded. Words inserted: " << dict.size() << "\n";

    // Test words
    vector<string> testWords = {
        "chate",      // should suggest: chat, hate
        "atr",        // should suggest: art, tar
        "rateat",     // should suggest: rate at, rat eat
        "poe",        // should suggest: poet, pole, pope, etc.
        "thed",       // should suggest: them, then, they
        "science",    // correctly spelled
        "zzzz"        // no suggestions
    };

    for (const string& word : testWords) {
        testWord(dict, word);
    }

    return 0;
}
