#include <iostream>
#include <string>

using namespace std;

const int TABLE_SIZE = 10;

// Node for the singly linked list in each bucket
struct Node {
    string key;
    string value;
    Node* next;

    Node(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    Node* buckets[TABLE_SIZE];

    // Hash function: sum of ASCII values of characters in the key % TABLE_SIZE
    int hashFunction(const string& key) const {
        int asciiSum = 0;
        for (size_t i = 0; i < key.length(); ++i) {
            asciiSum += static_cast<int>(key[i]);
        }
        return asciiSum % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            buckets[i] = nullptr;
        }
    }

    // Free all dynamically allocated linked list nodes
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    // Insert key-value pair using separate chaining (preserves duplicate keys/strings)
    void insert(const string& key, const string& value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);

        // Append at the tail of the bucket's linked list to preserve insertion order
        if (buckets[index] == nullptr) {
            buckets[index] = newNode;
        } else {
            Node* temp = buckets[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Retrieve and print all values matching a given key
    void search(const string& key) const {
        int index = hashFunction(key);
        Node* current = buckets[index];
        bool found = false;

        cout << "Search results for key \"" << key << "\" (Bucket " << index << "): ";
        while (current != nullptr) {
            if (current->key == key) {
                cout << "\"" << current->value << "\" ";
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            cout << "None";
        }
        cout << "\n";
    }

    // Display the entire hash table and its chains
    void display() const {
        cout << "--- Hash Table Contents ---\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Bucket [" << i << "]: ";
            Node* current = buckets[i];
            if (current == nullptr) {
                cout << "EMPTY";
            } else {
                while (current != nullptr) {
                    cout << "(" << current->key << ", " << current->value << ")";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    HashTable myhash;

    myhash.insert("A", "aaaaa");
    myhash.insert("B", "bbbbb");
    myhash.insert("C", "ccccc");
    myhash.insert("A", "zzzzz");

    myhash.display();
    cout << "\n";
    myhash.search("A");

    return 0;
}
