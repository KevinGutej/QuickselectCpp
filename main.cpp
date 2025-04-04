#include <stdio.h>

class Random {
    unsigned long long seed;
public:
    Random() : seed(123456789ULL) {}
    unsigned int next() {
        seed ^= seed << 21;
        seed ^= seed >> 35;
        seed ^= seed << 4;
        return (unsigned int)(seed & 0x7FFFFFFF);
    }
    int nextInt(int min, int max) {
        return min + (int)(next() % (max - min + 1));
    }
};

Random rng;

void manualSwap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int left, int right, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    manualSwap(arr[pivotIndex], arr[right]);
    int storeIndex = left;

    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            manualSwap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }

    manualSwap(arr[storeIndex], arr[right]);
    return storeIndex;
}

int quickselect(int arr[], int size, int k, int findLargest) {
    if (k < 1 || k > size) return -1;

    if (findLargest) {
        k = size - k + 1;
    }

    k--;

    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int pivotIndex = rng.nextInt(left, right);
        int partitionIndex = partition(arr, left, right, pivotIndex);

        if (partitionIndex == k)
            return arr[partitionIndex];
        else if (partitionIndex < k)
            left = partitionIndex + 1;
        else
            right = partitionIndex - 1;
    }

    return arr[left];
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 3, 5, 7, 19, 26, 4, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    printf("Original array: ");
    printArray(arr, size);

    int kthSmallest = quickselect(arr, size, k, 0);
    printf("The %d-th smallest element is: %d\n", k, kthSmallest);

    int kthLargest = quickselect(arr, size, k, 1);
    printf("The %d-th largest element is: %d\n", k, kthLargest);

    return 0;
}
