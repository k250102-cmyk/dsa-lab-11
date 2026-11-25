#include <iostream>
#include <string>

using namespace std;

const int TABLE_SIZE = 100;

struct Node {
    string key;
    string meaning;
    Node* next;

    Node(const string& k, const string& m) : key(k), meaning(m), next(nullptr) {}
};

class ASCIIDictionary {
private:
    Node* buckets[TABLE_SIZE];

    // Hash function: (Sum of ASCII values of characters in word) MOD 100
    int hashFunction(const string& word) const {
        int k = 0;
        for (size_t i = 0; i < word.length(); ++i) {
            k += static_cast<int>(word[i]);
        }
        return k % TABLE_SIZE;
    }

public:
    ASCIIDictionary() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            buckets[i] = nullptr;
        }
    }

    ~ASCIIDictionary() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    // a) Add_Record(): Inserts a word (key) and its value/meaning using Separate Chaining
    void Add_Record(const string& key, const string& meaning) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, meaning);

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

    // Overloaded interactive version taking user input directly
    void Add_Record() {
        string key, meaning;
        cout << "Enter word (key): ";
        cin >> key;
        cout << "Enter meaning/value: ";
        cin >> meaning;
        Add_Record(key, meaning);
    }

    // b) Word_Search(): Searches for a single string and prints an error if not found
    void Word_Search(const string& key) const {
        int index = hashFunction(key);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                cout << "search key " << key << ": " << current->meaning << "\n";
                return;
            }
            current = current->next;
        }

        cout << "Error: Word \"" << key << "\" not found in dictionary!\n";
    }

    // Delete_Record(): Removes a key from its separate chaining linked list
    void Delete_Record(const string& key) {
        int index = hashFunction(key);
        Node* current = buckets[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    buckets[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "key " << key << " deleted successfully !\n";
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Error: Key \"" << key << "\" not found for deletion!\n";
    }

    // c) Print_Dictionary(): Displays all populated indices and their chains
    void Print_Dictionary() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (buckets[i] != nullptr) {
                cout << "index " << i << ": ";
                Node* current = buckets[i];
                while (current != nullptr) {
                    cout << "(" << current->key << ", " << current->meaning << ")";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
                cout << "\n";
            }
        }
    }
};

int main() {
    ASCIIDictionary dict;

    // Adding records
    // "AB" -> 65 + 66 = 131 -> 131 % 100 = 31
    // "CD" -> 67 + 68 = 135 -> 135 % 100 = 35
    // "EF" -> 69 + 70 = 139 -> 139 % 100 = 39
    dict.Add_Record("AB", "FASTNU");
    dict.Add_Record("CD", "CS");
    dict.Add_Record("EF", "DS");

    // b) Search for key "AB"
    dict.Word_Search("AB");

    // Delete key "EF" (as shown in expected output)
    dict.Delete_Record("EF");

    // c) Display complete dictionary
    dict.Print_Dictionary();

    return 0;
}
