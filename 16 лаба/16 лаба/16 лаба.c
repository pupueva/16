#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#define CRT_NO_SECURE_DEPRECATE

// Функция для заполнения массива значениями по формуле
double* full_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        ptr_array[i] = pow(i + 1, 2) - pow(cos(i + 2), 2);
    }
    return ptr_array;
}

// Функция для вывода элементов массива
int put_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", ptr_array[i]);
    }
    printf("\n");
    return 0;
}

// Функция для обработки элементов массива, уменьшая их в 10 раз
double* calc_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        ptr_array[i] /= 10.0;
    }
    return ptr_array;
}

// Функция для удаления элемента с заданным индексом
int delete_k(double* ptr_array, int size, int k) {
    for (int i = k; i < size - 1; i++) {
        ptr_array[i] = ptr_array[i + 1];
    }
    return size - 1; // Возвращаем новое количество элементов
}

// Функция для вставки элемента -999 после указанного индекса
double* insert_element(double* ptr_array, int* size, int index, double value) {
    int new_size = *size + 1;
    ptr_array = (double*)realloc(ptr_array, new_size * sizeof(double));
    if (ptr_array == NULL) {
        printf("Ошибка перераспределения памяти\n");
        exit(1);
    }
    for (int i = new_size - 1; i > index + 1; i--) {
        ptr_array[i] = ptr_array[i - 1];
    }
    ptr_array[index + 1] = value;
    *size = new_size;
    return ptr_array;
}

// Функция для случайного заполнения массива значениями от -1 до 1
double* fill_random(double* ptr_array, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        ptr_array[i] = (double)rand() / RAND_MAX * 2 - 1;
    }
    return ptr_array;
}

// Дополнительная функция для преобразования массива в зависимости от условий
void adjust_elements(double* ptr_array, int size) {
    int first_positive_index = -1;
    for (int i = 0; i < size; i++) {
        if (ptr_array[i] > 0) {
            first_positive_index = i;
            break;
        }
    }

    if (first_positive_index != -1) {
        for (int i = first_positive_index; i < size; i++) {
            if (ptr_array[i] > 1) {
                ptr_array[i] -= 0.5;
            }
            else {
                ptr_array[i] += 0.5;
            }
        }
    }
}

// Основная функция
int main() {
    setlocale(LC_CTYPE,"RUS");
    double* ptr_array;
    int size;

    printf("Введите размер массива: ");
    scanf_s("%d", &size);

    // Выделение памяти под массив
    ptr_array = (double*)malloc(size * sizeof(double));
    if (ptr_array == NULL) {
        printf("Ошибка выделения памяти\n");
        return -1;
    }

    // Заполнение массива случайными значениями от -1 до 1
    fill_random(ptr_array, size);

    // Печать исходного массива
    printf("Исходный массив:\n");
    put_elements(ptr_array, size);

    // Обработка элементов массива
    calc_elements(ptr_array, size);
    printf("Массив после уменьшения элементов в 10 раз:\n");
    put_elements(ptr_array, size);

    // Удаление элемента с заданным индексом
    int del_index;
    printf("Введите индекс элемента для удаления: ");
    scanf_s("%d", &del_index);
    if (del_index >= 0 && del_index < size) {
        size = delete_k(ptr_array, size, del_index);
        printf("Массив после удаления элемента на индексе %d:\n", del_index);
        put_elements(ptr_array, size);
    }
    else {
        printf("Некорректный индекс для удаления\n");
    }

    // Вставка элемента -999 после заданного индекса
    int insert_index;
    printf("Введите индекс для вставки элемента -999: ");
    scanf_s("%d", &insert_index);
    if (insert_index >= 0 && insert_index < size) {
        ptr_array = insert_element(ptr_array, &size, insert_index, -999);
        printf("Массив после вставки -999 после индекса %d:\n", insert_index);
        put_elements(ptr_array, size);
    }
    else {
        printf("Некорректный индекс для вставки\n");
    }

    // Освобождение памяти
    free(ptr_array);
    return 0;
}
