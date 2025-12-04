#include <stdio.h>
#include <stdlib.h>
#include "libs.h"

// Функция для чтения массива из строки
int* parse_array(int* size) {
    int capacity = 10;
    int* arr = malloc(capacity * sizeof(int));
    *size = 0;
    int val;
    char ch;
    
    // Читаем числа пока не встретим новую строку
    while (scanf("%d%c", &val, &ch) == 2) {
        if (*size >= capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(int));
        }
        arr[(*size)++] = val;
        if (ch == '\n') break;
    }
    return arr;
}

int main() {
    int command;
    printf("Program #1 (Static Linking)\n");
    printf("Commands:\n 1 A B (GCF)\n 2 arr... (QuickSort)\n");

    while (scanf("%d", &command) != EOF) {
        if (command == 1) {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("GCF: %d\n", GCF(a, b));
        } 
        else if (command == 2) {
            int size;
            int* arr = parse_array(&size);
            
            Sort(arr, size);
            
            printf("Sorted: ");
            for(int i=0; i<size; i++) printf("%d ", arr[i]);
            printf("\n");
            
            free(arr);
        }
        else {
            printf("Unknown command for Program 1\n");
        }
    }
    return 0;
}