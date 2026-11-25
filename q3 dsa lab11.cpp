#include <iostream>

using namespace std;

const int MAX_CAPACITY = 100;

void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void printArray(const char* label, const int arr[], int size) {
    cout << label << ": [ ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << "]\n";
}

class BinaryHeap {
private:
    int heap[MAX_CAPACITY];
    int size;
    bool isMaxHeap;

    // Comparison helper: true if 'a' should be closer to the root than 'b'
    bool hasHigherPriority(int a, int b) const {
        return isMaxHeap ? (a > b) : (a < b);
    }

    void heapifyDown(int index, int currentSize) {
        while (true) {
            int target = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < currentSize && hasHigherPriority(heap[left], heap[target])) {
                target = left;
            }
            if (right < currentSize && hasHigherPriority(heap[right], heap[target])) {
                target = right;
            }

            if (target != index) {
                swapValues(heap[index], heap[target]);
                index = target;
            } else {
                break;
            }
        }
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (hasHigherPriority(heap[index], heap[parent])) {
                swapValues(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

public:
    // Build heap in O(n) time using bottom-up Floyd's algorithm
    BinaryHeap(const int arr[], int n, bool maxMode) {
        size = n;
        isMaxHeap = maxMode;
        for (int i = 0; i < size; ++i) {
            heap[i] = arr[i];
        }
        for (int i = (size / 2) - 1; i >= 0; --i) {
            heapifyDown(i, size);
        }
    }

    // Delete a specific value from any position in the heap
    void removeValue(int val) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (heap[i] == val) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Value " << val << " not found.\n";
            return;
        }

        // Replace target element with the last leaf and shrink size
        heap[index] = heap[size - 1];
        size--;

        // Restore heap property (element might need to move up OR down)
        if (index < size) {
            int parent = (index - 1) / 2;
            if (index > 0 && hasHigherPriority(heap[index], heap[parent])) {
                heapifyUp(index);
            } else {
                heapifyDown(index, size);
            }
        }
    }

    // Perform in-place Heap Sort on the Max-Heap (produces ascending order)
    void heapSort(int outputArr[], int& outSize) {
        outSize = size;
        int tempHeap[MAX_CAPACITY];
        for (int i = 0; i < size; ++i) {
            tempHeap[i] = heap[i];
        }

        // Temporarily sort using the internal array and restore afterward
        int originalSize = size;
        for (int end = size - 1; end > 0; --end) {
            swapValues(heap[0], heap[end]); // Move max element to the end
            heapifyDown(0, end);            // Restore max-heap on reduced range
        }

        for (int i = 0; i < originalSize; ++i) {
            outputArr[i] = heap[i];
            heap[i] = tempHeap[i]; // Restore original heap state
        }
        size = originalSize;
    }

    void print(const char* label) const {
        printArray(label, heap, size);
    }
};

int main() {
    int initialArray[] = {25, 30, 35, 11, 15, 19, 18, 55, 78, 36};
    int n = 10;

    printArray("Initial Array", initialArray, n);
    cout << "\n";

    // 1. Build Max-Heap and remove 55
    BinaryHeap maxHeap(initialArray, n, true);
    maxHeap.print("1a. Built Max-Heap       ");
    maxHeap.removeValue(55);
    maxHeap.print("1b. Max-Heap without 55  ");
    cout << "\n";

    // 2. Build Min-Heap and remove 18
    BinaryHeap minHeap(initialArray, n, false);
    minHeap.print("2a. Built Min-Heap       ");
    minHeap.removeValue(18);
    minHeap.print("2b. Min-Heap without 18  ");
    cout << "\n";

    // 3. Perform Heap Sort on the Max-Heap (after removing 55)
    int sortedArray[MAX_CAPACITY];
    int sortedSize = 0;
    maxHeap.heapSort(sortedArray, sortedSize);
    printArray("3.  Heap Sort Output     ", sortedArray, sortedSize);

    return 0;
}
