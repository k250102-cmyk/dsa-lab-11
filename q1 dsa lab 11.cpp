#include <iostream>

using namespace std;

const int MAX_CAPACITY = 100;

class ParcelMinHeap {
private:
    int heap[MAX_CAPACITY];
    int size;

    // Manual swap helper instead of <algorithm>
    void swapValues(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Restores the min-heap property by moving the newly added element up
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;

            // If current parcel is more urgent (smaller value) than its parent, swap
            if (heap[index] < heap[parentIndex]) {
                swapValues(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

public:
    // Initialize with an existing C-style array of valid min-heap elements
    ParcelMinHeap(const int existingHeap[], int initialSize) {
        size = (initialSize <= MAX_CAPACITY) ? initialSize : MAX_CAPACITY;
        for (int i = 0; i < size; ++i) {
            heap[i] = existingHeap[i];
        }
    }

    // Insert a new parcel urgency rating into the heap
    void insertParcel(int urgencyRating) {
        if (size >= MAX_CAPACITY) {
            cout << "Heap overflow: Dispatch queue is full.\n";
            return;
        }

        // 1. Place the new parcel at the next free slot in the array
        heap[size] = urgencyRating;
        size++;

        // 2. Bubble it up to its valid position
        heapifyUp(size - 1);
    }

    // Print the array representation and level-by-level tree structure
    void printHeap() const {
        cout << "Heap Array: [ ";
        for (int i = 0; i < size; ++i) {
            cout << heap[i] << " ";
        }
        cout << "]\n\nTree Structure (Level-by-Level):\n";

        int levelSize = 1;
        int count = 0;
        for (int i = 0; i < size; ++i) {
            cout << heap[i] << " ";
            count++;
            if (count == levelSize) {
                cout << "\n";
                levelSize *= 2;
                count = 0;
            }
        }
        if (count != 0) cout << "\n";
    }
};

int main() {
    // Existing valid min-heap (parent at index 2 is 3, so inserting 2 triggers a swap)
    int initialParcels[] = {1, 4, 3, 5, 4, 5};
    int initialSize = 6;

    ParcelMinHeap dispatchQueue(initialParcels, initialSize);

    cout << "--- Before Insertion ---\n";
    dispatchQueue.printHeap();

    // New parcel with urgency rating 2 arrives
    int newParcelUrgency = 2;
    dispatchQueue.insertParcel(newParcelUrgency);

    cout << "\n--- After Inserting Parcel (Urgency: " << newParcelUrgency << ") ---\n";
    dispatchQueue.printHeap();

    return 0;
}
