#include <iostream>

using namespace std;

const int MAX_CAPACITY = 100;

class StreamMaxHeap {
private:
    int heap[MAX_CAPACITY];
    int size;

    // Manual swap helper without <algorithm>
    void swapValues(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Restores the max-heap property by sinking the root element down
    void heapifyDown(int index) {
        while (true) {
            int largest = index;
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;

            // Check if left child exists and has higher priority than current largest
            if (leftChild < size && heap[leftChild] > heap[largest]) {
                largest = leftChild;
            }

            // Check if right child exists and has higher priority than current largest
            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }

            // If a child has higher priority, swap and continue sinking down
            if (largest != index) {
                swapValues(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    // Initialize with an existing C-style array of valid max-heap elements
    StreamMaxHeap(const int existingHeap[], int initialSize) {
        size = (initialSize <= MAX_CAPACITY) ? initialSize : MAX_CAPACITY;
        for (int i = 0; i < size; ++i) {
            heap[i] = existingHeap[i];
        }
    }

    // Extract and delete the highest-priority item (root)
    int extractMax() {
        if (size <= 0) {
            cout << "Heap underflow: Priority queue is empty.\n";
            return -1;
        }

        // 1. Save the highest-priority item at the root
        int maxPriorityItem = heap[0];

        // 2. Move the last element in the heap to the root and shrink size
        heap[0] = heap[size - 1];
        size--;

        // 3. Restore max-heap property by bubbling the new root down
        if (size > 0) {
            heapifyDown(0);
        }

        return maxPriorityItem;
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
    // Existing valid max-heap of data stream priorities
    int initialStream[] = {95, 80, 75, 40, 60, 50, 30};
    int initialSize = 7;

    StreamMaxHeap priorityQueue(initialStream, initialSize);

    cout << "--- Before Root Extraction ---\n";
    priorityQueue.printHeap();

    // Extract and process the highest-priority root element
    int processedItem = priorityQueue.extractMax();
    cout << "\nExtracted & Processed Root Priority: " << processedItem << "\n";

    cout << "\n--- After Deleting Root ---\n";
    priorityQueue.printHeap();

    return 0;
}
