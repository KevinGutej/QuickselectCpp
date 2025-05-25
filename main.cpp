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
        for (int i = 1; i < n; i++) if (arr[i] < min) min = arr[i];
        return min;
    }

    int findMax(int arr[], int n) {
        int max = arr[0];
        for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
        return max;
    }

    double findMedian(int arr[], int n) {
        quicksort(arr, 0, n - 1);
        if (n % 2 == 1) return arr[n / 2];
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    }

    int sum(int arr[], int n) {
        int s = 0;
        for (int i = 0; i < n; i++) s += arr[i];
        return s;
    }

    double average(int arr[], int n) {
        return (double)sum(arr, n) / n;
    }

    int frequency(int arr[], int n, int num) {
        int count = 0;
        for (int i = 0; i < n; i++) if (arr[i] == num) count++;
        return count;
    }

    int mode(int arr[], int n) {
        int maxCount = 0, modeVal = arr[0];
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) if (arr[j] == arr[i]) count++;
            if (count > maxCount) {
                maxCount = count;
                modeVal = arr[i];
            }
        }
        return modeVal;
    }

    void reverse(int arr[], int n) {
        int l = 0, r = n - 1;
        while (l < r) swap(arr[l++], arr[r--]);
    }

    int countEven(int arr[], int n) {
        int count = 0;
        for (int i = 0; i < n; i++) if (arr[i] % 2 == 0) count++;
        return count;
    }

    int countOdd(int arr[], int n) {
        int count = 0;
        for (int i = 0; i < n; i++) if (arr[i] % 2 != 0) count++;
        return count;
    }

    void rotateLeft(int arr[], int n, int d) {
        d = d % n;
        for (int i = 0; i < d; i++) {
            int temp = arr[0];
            for (int j = 0; j < n - 1; j++) arr[j] = arr[j + 1];
            arr[n - 1] = temp;
        }
    }

    void rotateRight(int arr[], int n, int d) {
        d = d % n;
        for (int i = 0; i < d; i++) {
            int temp = arr[n - 1];
            for (int j = n - 1; j > 0; j--) arr[j] = arr[j - 1];
            arr[0] = temp;
        }
    }

    void printArray(int arr[], int size) {
        for (int i = 0; i < size; i++) printf("%d ", arr[i]);
        printf("\n");
    }

    int isPrime(int num) {
        if (num <= 1) return 0;
        for (int i = 2; i * i <= num; i++) if (num % i == 0) return 0;
        return 1;
    }

    int countPrimes(int arr[], int n) {
        int count = 0;
        for (int i = 0; i < n; i++) if (isPrime(arr[i])) count++;
        return count;
    }

    int findSecondMin(int arr[], int n) {
        int min = findMin(arr, n), second = 2147483647;
        for (int i = 0; i < n; i++) if (arr[i] != min && arr[i] < second) second = arr[i];
        return second;
    }

    int findSecondMax(int arr[], int n) {
        int max = findMax(arr, n), second = -2147483648;
        for (int i = 0; i < n; i++) if (arr[i] != max && arr[i] > second) second = arr[i];
        return second;
    }

    int removeDuplicates(int arr[], int n) {
        if (n == 0) return 0;
        quicksort(arr, 0, n - 1);
        int j = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i] != arr[j]) arr[++j] = arr[i];
        }
        return j + 1;
    }

    int binarySearch(int arr[], int n, int key) {
        quicksort(arr, 0, n - 1);
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] == key) return mid;
            else if (arr[mid] < key) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    int range(int arr[], int n) {
        return findMax(arr, n) - findMin(arr, n);
    }

    int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    int lcm(int a, int b) {
        return (a * b) / gcd(a, b);
    }

    void prefixSum(int arr[], int n, int prefix[]) {
        prefix[0] = arr[0];
        for (int i = 1; i < n; i++) prefix[i] = prefix[i - 1] + arr[i];
    }

    void suffixSum(int arr[], int n, int suffix[]) {
        suffix[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) suffix[i] = suffix[i + 1] + arr[i];
    }

    int countPositive(int arr[], int n) {
        int count = 0;
        for (int i = 0; i < n; i++) if (arr[i] > 0) count++;
        return count;
    }

    int countNegative(int arr[], int n) {
        int count = 0;
        for (int i = 0; i < n; i++) if (arr[i] < 0) count++;
        return count;
    }

    int product(int arr[], int n) {
        int p = 1;
        for (int i = 0; i < n; i++) p *= arr[i];
        return p;
    }

    int countDistinct(int arr[], int n) {
        int temp[1000];
        for (int i = 0; i < n; i++) temp[i] = arr[i];
        int newSize = removeDuplicates(temp, n);
        return newSize;
    }

    bool isSorted(int arr[], int n) {
        for (int i = 1; i < n; i++) {
            if (arr[i] < arr[i - 1]) return false;
        }
        return true;
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
    int arr[1000], prefix[1000], suffix[1000];
    int n, k, choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    if (n <= 0 || n > 1000) {
        printf("Invalid size\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("\nOriginal array:\n");
    utils.printArray(arr, n);

    printf("\nChoose an operation:\n");
    printf("1. K-th Smallest\n2. K-th Largest\n3. Min\n4. Max\n5. Median\n6. Sort\n7. Sum\n8. Avg\n9. Frequency\n");
    printf("10. Mode\n11. Reverse\n12. Count Even\n13. Count Odd\n14. Rotate Left\n15. Rotate Right\n");
    printf("16. Second Min\n17. Second Max\n18. Count Primes\n19. Remove Duplicates\n20. Range\n21. Binary Search\n");
    printf("22. GCD\n23. LCM\n24. Prefix Sum\n25. Suffix Sum\n26. Count Positive\n27. Count Negative\n28. Product\n");
    printf("29. Count Distinct\n30. Is Sorted?\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: case 2:
            printf("Enter k (1 to %d): ", n);
            scanf("%d", &k);
            if (k < 1 || k > n) {
                printf("Invalid k\n");
                return 1;
            }
            printf("%d-th %s element: %d\n", k, (choice == 1 ? "smallest" : "largest"),
                   qs.select(arr, n, k, choice == 2));
            break;
        case 3: printf("Minimum: %d\n", utils.findMin(arr, n)); break;
        case 4: printf("Maximum: %d\n", utils.findMax(arr, n)); break;
        case 5: printf("Median: %.2f\n", utils.findMedian(arr, n)); break;
        case 6: utils.quicksort(arr, 0, n - 1); utils.printArray(arr, n); break;
        case 7: printf("Sum: %d\n", utils.sum(arr, n)); break;
        case 8: printf("Average: %.2f\n", utils.average(arr, n)); break;
        case 9: {
            int x;
            printf("Enter number: ");
            scanf("%d", &x);
            printf("Frequency: %d\n", utils.frequency(arr, n, x));
            break;
        }
        case 10: printf("Mode: %d\n", utils.mode(arr, n)); break;
        case 11: utils.reverse(arr, n); utils.printArray(arr, n); break;
        case 12: printf("Even count: %d\n", utils.countEven(arr, n)); break;
        case 13: printf("Odd count: %d\n", utils.countOdd(arr, n)); break;
        case 14: {
            int d;
            printf("Positions: ");
            scanf("%d", &d);
            utils.rotateLeft(arr, n, d);
            utils.printArray(arr, n);
            break;
        }
        case 15: {
            int d;
            printf("Positions: ");
            scanf("%d", &d);
            utils.rotateRight(arr, n, d);
            utils.printArray(arr, n);
            break;
        }
        case 16: printf("Second Min: %d\n", utils.findSecondMin(arr, n)); break;
        case 17: printf("Second Max: %d\n", utils.findSecondMax(arr, n)); break;
        case 18: printf("Prime count: %d\n", utils.countPrimes(arr, n)); break;
        case 19: {
            int newSize = utils.removeDuplicates(arr, n);
            printf("After removing duplicates: ");
            utils.printArray(arr, newSize);
            break;
        }
        case 20: printf("Range: %d\n", utils.range(arr, n)); break;
        case 21: {
            int x;
            printf("Enter number: ");
            scanf("%d", &x);
            int idx = utils.binarySearch(arr, n, x);
            if (idx == -1) printf("Not found\n");
            else printf("Found at index: %d\n", idx);
            break;
        }
        case 22: {
            int a, b;
            printf("Enter two numbers: ");
            scanf("%d%d", &a, &b);
            printf("GCD: %d\n", utils.gcd(a, b));
            break;
        }
        case 23: {
            int a, b;
            printf("Enter two numbers: ");
            scanf("%d%d", &a, &b);
            printf("LCM: %d\n", utils.lcm(a, b));
            break;
        }
        case 24: utils.prefixSum(arr, n, prefix); utils.printArray(prefix, n); break;
        case 25: utils.suffixSum(arr, n, suffix); utils.printArray(suffix, n); break;
        case 26: printf("Positive count: %d\n", utils.countPositive(arr, n)); break;
        case 27: printf("Negative count: %d\n", utils.countNegative(arr, n)); break;
        case 28: printf("Product: %d\n", utils.product(arr, n)); break;
        case 29: printf("Distinct elements: %d\n", utils.countDistinct(arr, n)); break;
        case 30: printf("Sorted? %s\n", utils.isSorted(arr, n) ? "Yes" : "No"); break;
        default: printf("Invalid choice\n");
    }

    printf("\nFinal array state:\n");
    utils.printArray(arr, n);

    return 0;
}
