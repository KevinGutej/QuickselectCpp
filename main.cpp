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

    int sum(int arr[], int n) {
        int s = 0;
        for (int i = 0; i < n; i++) {
            s += arr[i];
        }
        return s;
    }

    double average(int arr[], int n) {
        int s = sum(arr, n);
        return (double)s / n;
    }

    int frequency(int arr[], int n, int num) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] == num) count++;
        }
        return count;
    }

    int mode(int arr[], int n) {
        int maxCount = 0;
        int modeValue = arr[0];
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (arr[j] == arr[i]) count++;
            }
            if (count > maxCount) {
                maxCount = count;
                modeValue = arr[i];
            }
        }
        return modeValue;
    }

    void reverse(int arr[], int n) {
        int left = 0;
        int right = n - 1;
        while (left < right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    int countEven(int arr[], int n) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) count++;
        }
        return count;
    }

    int countOdd(int arr[], int n) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) count++;
        }
        return count;
    }

    void rotateLeft(int arr[], int n, int d) {
        d = d % n;
        for (int i = 0; i < d; i++) {
            int temp = arr[0];
            for (int j = 0; j < n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            arr[n - 1] = temp;
        }
    }

    void rotateRight(int arr[], int n, int d) {
        d = d % n;
        for (int i = 0; i < d; i++) {
            int temp = arr[n - 1];
            for (int j = n - 1; j > 0; j--) {
                arr[j] = arr[j - 1];
            }
            arr[0] = temp;
        }
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

    printf("\nChoose an operation:\n");
    printf("1. Find k-th smallest\n");
    printf("2. Find k-th largest\n");
    printf("3. Find minimum\n");
    printf("4. Find maximum\n");
    printf("5. Find median\n");
    printf("6. Sort array\n");
    printf("7. Sum of elements\n");
    printf("8. Average of elements\n");
    printf("9. Frequency of a number\n");
    printf("10. Mode of the array\n");
    printf("11. Reverse the array\n");
    printf("12. Count even numbers\n");
    printf("13. Count odd numbers\n");
    printf("14. Rotate left\n");
    printf("15. Rotate right\n");
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
        printf("Minimum value is: %d\n", utils.findMin(arr, n));
    } else if (choice == 4) {
        printf("Maximum value is: %d\n", utils.findMax(arr, n));
    } else if (choice == 5) {
        printf("Median is: %.2f\n", utils.findMedian(arr, n));
    } else if (choice == 6) {
        utils.quicksort(arr, 0, n - 1);
        printf("Sorted array: ");
        utils.printArray(arr, n);
    } else if (choice == 7) {
        printf("Sum of elements: %d\n", utils.sum(arr, n));
    } else if (choice == 8) {
        printf("Average: %.2f\n", utils.average(arr, n));
    } else if (choice == 9) {
        int x;
        printf("Enter number to find frequency: ");
        scanf("%d", &x);
        printf("Frequency of %d: %d\n", x, utils.frequency(arr, n, x));
    } else if (choice == 10) {
        printf("Mode of array: %d\n", utils.mode(arr, n));
    } else if (choice == 11) {
        utils.reverse(arr, n);
        printf("Reversed array: ");
        utils.printArray(arr, n);
    } else if (choice == 12) {
        printf("Number of even elements: %d\n", utils.countEven(arr, n));
    } else if (choice == 13) {
        printf("Number of odd elements: %d\n", utils.countOdd(arr, n));
    } else if (choice == 14) {
        int d;
        printf("Enter number of positions to rotate left: ");
        scanf("%d", &d);
        utils.rotateLeft(arr, n, d);
        printf("Array after left rotation: ");
        utils.printArray(arr, n);
    } else if (choice == 15) {
        int d;
        printf("Enter number of positions to rotate right: ");
        scanf("%d", &d);
        utils.rotateRight(arr, n, d);
        printf("Array after right rotation: ");
        utils.printArray(arr, n);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
