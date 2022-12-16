#include <iostream>
#include <vector>
using namespace std;

// 삽입 정렬
int insertSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && arr[j] < arr[j - 1]) {
        swap(arr[j], arr[j - 1]);
        j--;
        }
    }
    return 0;
}

// 퀵 정렬
int quickSort(int* nums, int left, int right) {
    if (left >= right) {
        return 0;
    }

    int pivot = nums[(left + right) / 2];
    int i = left;
    int j = right;

    while (i < j) {
        while (nums[i] < pivot) {
        i++;
        }
        while (nums[j] > pivot) {
        j--;
        }

        if (i <= j) {
        swap(nums[i], nums[j]);
        i++;
        j--;
        }
    }

    quickSort(nums, left, j);
    quickSort(nums, i, right);
    
    return 0;
}

// 자연합병정렬
int merge(int arr[], int l, int m, int r) {
    // Create two temporary arrays to hold the subarrays to be merged
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    // Copy the data from arr to the temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    // Merge the temporary arrays back into arr
    int i = 0, j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
        arr[k] = L[i];
        i++;
        } else {
        arr[k] = R[j];
        j++;
        }
        k++;
    }

    // Copy any remaining elements from L and R
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    return 0;
}

int naturalMergeSort(int arr[], int l, int r) {
    // Base case: if the subarray has less than 2 elements, it is already sorted
    if (l >= r) {
        return 0;
    }

    // Find the first element of the second half of the array
    int m = l + 1;
    // while (m <= r && arr[m] >= arr[m - 1]) {
    //     m++;
    // }

    // Recursively sort the two halves of the array
    naturalMergeSort(arr, l, m - 1);
    naturalMergeSort(arr, m, r);

    // Merge the two sorted halves
    merge(arr, l, m - 1, r);
    return 0;
}

// 힙 정렬
void heapify(int* nums, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && nums[left] > nums[largest]) {
        largest = left;
    }

    if (right < n && nums[right] > nums[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(nums[i], nums[largest]);
        heapify(nums, n, largest);
    }
}

void heapSort(int *nums, int n) {

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(nums, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(nums[0], nums[i]);
        heapify(nums, i, 0);
    }
}