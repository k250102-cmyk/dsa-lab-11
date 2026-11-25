#include <iostream>
#include <list>
#include <string>

using namespace std;

const int TABLE_SIZE = 10;

// Key-value entry stored inside each std::list bucket
struct Entry {
    string key;
    string value;

    Entry(const string& k, const string& v) : key(k), value(v) {}
};

class Hash {
private:
    // Array of built-in C++ doubly linked lists (std::list) for separate chaining
    list<Entry> buckets[TABLE_SIZE];

    // Hash function: sum of ASCII values modulo TABLE_SIZE
    int hashFunction(const string& key) const {
        int sum = 0;
        for (size_t i = 0; i < key.length(); ++i) {
            sum += static_cast<int>(key[i]);
        }
        return sum % TABLE_SIZE;
    }

public:
    // Insert a key-value pair into the corresponding bucket's std::list
    void insert(const string& key, const string& value) {
        int index = hashFunction(key);

        // Update value if key already exists in the list
        for (list<Entry>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->key == key) {
                it->value = value;
                return;
            }
        }

        // Otherwise append new entry to the linked list
        buckets[index].push_back(Entry(key, value));
    }

    // Search for a key and display its value
    bool search(const string& key) const {
        int index = hashFunction(key);

        for (list<Entry>::const_iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->key == key) {
                cout << "Found [" << key << "]: " << it->value << " (Bucket " << index << ")\n";
                return true;
            }
        }

        cout << "Key [" << key << "] not found.\n";
        return false;
    }

    // Delete a key-value pair from the bucket's std::list
    void remove(const string& key) {
        int index = hashFunction(key);

        for (list<Entry>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->key == key) {
                buckets[index].erase(it);
                cout << "Deleted key [" << key << "] from Bucket " << index << ".\n";
                return;
            }
        }

        cout << "Cannot delete: Key [" << key << "] not found.\n";
    }

    // Display all buckets and their linked list elements
    void display() const {
        cout << "--- Hash Table Contents ---\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Bucket [" << i << "]: ";
            if (buckets[i].empty()) {
                cout << "EMPTY";
            } else {
                for (list<Entry>::const_iterator it = buckets[i].begin(); it != buckets[i].end(); ++it) {
                    if (it != buckets[i].begin()) {
                        cout << " -> ";
                    }
                    cout << "(" << it->key << ", " << it->value << ")";
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    Hash hashTable;

    // Insert elements ("A" = 65 -> bucket 5, "K" = 75 -> bucket 5 [collision], "B" = 66 -> bucket 6)
    hashTable.insert("A", "Alpha");
    hashTable.insert("K", "Kilo");
    hashTable.insert("B", "Bravo");
    hashTable.insert("C", "Charlie");

    hashTable.display();
    cout << "\n";

    // Search operations
    hashTable.search("K");
    hashTable.search("Z");
    cout << "\n";

    // Delete operation
    hashTable.remove("A");
    cout << "\n";

    hashTable.display();

    return 0;
}
