#include "libs.h"
#include <stdio.h>

// Наивный алгоритм (перебор)
int GCF(int A, int B) {
    int min = (A < B) ? A : B;
    for (int i = min; i > 0; i--) {
        if (A % i == 0 && B % i == 0) {
            return i;
        }
    }
    return 1;
}

// функция для QuickSort
void quickSortInternal(int* array, int low, int high) {
    if (low < high) {
        int pivot = array[(low + high) / 2];
        int i = low;
        int j = high;
        while (i <= j) {
            while (array[i] < pivot) i++;
            while (array[j] > pivot) j--;
            if (i <= j) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i++;
                j--;
            }
        }
        quickSortInternal(array, low, j);
        quickSortInternal(array, i, high);
    }
}

// Сортировка Хоара
int* Sort(int* array, int size) {
    quickSortInternal(array, 0, size - 1);
    return array;
}