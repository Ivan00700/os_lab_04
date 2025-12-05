#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> // Заголовок для работы с динамическими библиотеками

// Указатели на функции
typedef int (*GCF_Func)(int, int);
typedef int* (*Sort_Func)(int*, int);

const char* LIB_NAMES[] = {"./libimpl1.so", "./libimpl2.so"};

int main() {
    void* lib_handle = NULL; 
    // непрозрачный указатель, то есть адрес библиотеки, если надо что то найти или закрыть ее - "показываем" этот "жетончик"
    // т.е. адрес структуры описания библиотеки
    GCF_Func gcf_func = NULL;
    Sort_Func sort_func = NULL;
    int current_lib = 0;

    // Загружаем первую библиотеку по умолчанию
    // дскрптр загруженной библиотеки
    lib_handle = dlopen(LIB_NAMES[current_lib], RTLD_LAZY); // RTLD_LAZY - ленивая загрузка, значит что ОС не проверяет все функции бибилиотеки
    if (!lib_handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }
    
    // Получаем адреса функций
    gcf_func = (GCF_Func)dlsym(lib_handle, "GCF"); // !!!dlsym возвращает адрес начала машинного кода этой функции!!!
    sort_func = (Sort_Func)dlsym(lib_handle, "Sort"); // dlsym возвращает адрес начала машинного кода этой функции

    if (!gcf_func || !sort_func) {
        fprintf(stderr, "Error loading symbols: %s\n", dlerror());
        return 1;
    }

    printf("Dynamic #2 (Dynamic Loading). Current lib: %s\n", LIB_NAMES[current_lib]);

    int command;
    while (scanf("%d", &command) != EOF) {
        if (command == 0) {
            // Смена реализации
            dlclose(lib_handle); // Закрываем текущую
            current_lib = 1 - current_lib; // Переключаем индекс (0 <-> 1)
            
            lib_handle = dlopen(LIB_NAMES[current_lib], RTLD_LAZY);
            if (!lib_handle) {
                fprintf(stderr, "Error switching library: %s\n", dlerror());
                return 1;
            }
            
            gcf_func = (GCF_Func)dlsym(lib_handle, "GCF");
            sort_func = (Sort_Func)dlsym(lib_handle, "Sort");
            
            printf("Switched to %s\n", LIB_NAMES[current_lib]);
        }
        else if (command == 1) {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("GCF: %d\n", gcf_func(a, b));
        }
        else if (command == 2) {
            // Парсинг массива
            int capacity = 10, size = 0, val;
            int* arr = malloc(capacity * sizeof(int));
            char ch;
            while (scanf("%d%c", &val, &ch) == 2) {
                if (size >= capacity) {
                    capacity *= 2;
                    arr = realloc(arr, capacity * sizeof(int));
                }
                arr[size++] = val;
                if (ch == '\n') break;
            }

            sort_func(arr, size);

            printf("Sorted: ");
            for(int i=0; i<size; i++) printf("%d ", arr[i]);
            printf("\n");
            
            free(arr);
        }
        else {
            printf("Unknown command\n");
        }
    }

    dlclose(lib_handle);
    return 0;
}