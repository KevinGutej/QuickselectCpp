#include <stdio.h>
#include <time.h>

class Random {
    unsigned long long seed;
public:
    Random() : seed((unsigned long long)time(0)) {}

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

class Utils {
public:
    void swap(int &a, int &b) {
        int t = a;
        a = b;
        b = t;
    }

    void quicksort(int arr[], int left, int right) {
        if (left < right) {
            int pivot = arr[right];
            int i = left - 1;
            for (int j = left; j < right; j++) {
                if (arr[j] <= pivot) {
                    i++;
                    swap(arr[i], arr[j]);
                }
            }
            swap(arr[i + 1], arr[right]);
            int p = i + 1;
            quicksort(arr, left, p - 1);
            quicksort(arr, p + 1, right);
        }
    }

    int findMin(int arr[], int n) {
        int min = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] < min) min = arr[i];
        }
        return min;
    }

    int findMax(int arr[], int n) {
        int max = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] > max) max = arr[i];
        }
        return max;
    }

    double findMedian(int arr[], int n) {
        quicksort(arr, 0, n - 1);
        if (n % 2 == 1) return arr[n / 2];
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    }

    void printArray(int arr[], int size) {
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
};

class QuickSelect {
    Random rng;

    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

    int partition(int arr[], int left, int right, int pivotIndex) {
        int pivotValue = arr[pivotIndex];
        swap(arr[pivotIndex], arr[right]);
        int storeIndex = left;

        for (int i = left; i < right; i++) {
            if (arr[i] < pivotValue) {
                swap(arr[i], arr[storeIndex]);
                storeIndex++;
            }
        }

        swap(arr[storeIndex], arr[right]);
        return storeIndex;
    }

public:
    int select(int arr[], int size, int k, int findLargest) {
        if (k < 1 || k > size) return -1;
        if (findLargest) k = size - k + 1;
        k--;

        int left = 0, right = size - 1;

        while (left <= right) {
            int pivotIndex = rng.nextInt(left, right);
            int partitionIndex = partition(arr, left, right, pivotIndex);

            if (partitionIndex == k) return arr[partitionIndex];
            else if (partitionIndex < k) left = partitionIndex + 1;
            else right = partitionIndex - 1;
        }

        return arr[left];
    }
};

int main() {
    QuickSelect qs;
    Utils utils;
    int arr[1000];
    int n, k, choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 1000) {
        printf("Invalid size\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int original[1000];
    for (int i = 0; i < n; i++) original[i] = arr[i];

    printf("\nChoose an operation:\n");
    printf("1. Find k-th smallest\n");
    printf("2. Find k-th largest\n");
    printf("3. Find minimum\n");
    printf("4. Find maximum\n");
    printf("5. Find median\n");
    printf("6. Sort array\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2) {
        printf("Enter k (1 to %d): ", n);
        scanf("%d", &k);
        if (k < 1 || k > n) {
            printf("Invalid k\n");
            return 1;
        }
    }

    if (choice == 1) {
        int res = qs.select(arr, n, k, 0);
        printf("The %d-th smallest element is: %d\n", k, res);
    } else if (choice == 2) {
        int res = qs.select(arr, n, k, 1);
        printf("The %d-th largest element is: %d\n", k, res);
    } else if (choice == 3) {
        int res = utils.findMin(arr, n);
        printf("Minimum value is: %d\n", res);
    } else if (choice == 4) {
        int res = utils.findMax(arr, n);
        printf("Maximum value is: %d\n", res);
    } else if (choice == 5) {
        double med = utils.findMedian(arr, n);
        printf("Median is: %.2f\n", med);
    } else if (choice == 6) {
        utils.quicksort(arr, 0, n - 1);
        printf("Sorted array: ");
        utils.printArray(arr, n);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
