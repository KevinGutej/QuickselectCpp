#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

int randomizedPartition(vector<int>& arr, int left, int right) {
    int pivotIndex = left + (rand() % (right - left + 1));
    swap(arr[pivotIndex], arr[right]);
    return partition(arr, left, right);
}

int quickselect(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];

    int partitionIndex = randomizedPartition(arr, left, right);

    if (partitionIndex == k) return arr[partitionIndex];
    else if (partitionIndex > k) return quickselect(arr, left, partitionIndex - 1, k);
    else return quickselect(arr, partitionIndex + 1, right, k);
}

void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    vector<int> arr = {12, 3, 5, 7, 19, 26, 4, 10};
    int k = 4;
    cout << "Original array: ";
    printArray(arr);
    int result = quickselect(arr, 0, arr.size() - 1, k - 1);
    cout << "The " << k << "-th smallest element is: " << result << endl;
    return 0;
}
