#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

void printArray(int arr[], int size);
void swap(int *a, int *b);
void bubbleSort(int arr[], int size);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

int main() {
    int arr[ARRAY_SIZE];
    srand(time(NULL));

    // Initialize array with random numbers
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 100;
    }

    int choice;
    while (1) {
        printf("\nSorting Algorithms Visualization\n");
        printf("1. Bubble Sort\n");
        printf("2. Quick Sort\n");
        printf("3. Merge Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Reset the array to random numbers for each sort
        for (int i = 0; i < ARRAY_SIZE; i++) {
            arr[i] = rand() % 100;
        }

        switch (choice) {
            case 1:
                printf("Original Array:\n");
                printArray(arr, ARRAY_SIZE);
                bubbleSort(arr, ARRAY_SIZE);
                break;
            case 2:
                printf("Original Array:\n");
                printArray(arr, ARRAY_SIZE);
                quickSort(arr, 0, ARRAY_SIZE - 1);
                break;
            case 3:
                printf("Original Array:\n");
                printArray(arr, ARRAY_SIZE);
                mergeSort(arr, 0, ARRAY_SIZE - 1);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
            printArray(arr, size);
        }
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            printArray(arr, ARRAY_SIZE);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    printArray(arr, ARRAY_SIZE);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        printArray(arr, ARRAY_SIZE);
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        printArray(arr, ARRAY_SIZE);
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        printArray(arr, ARRAY_SIZE);
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}