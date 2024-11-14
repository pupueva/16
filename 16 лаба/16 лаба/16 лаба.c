#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#define CRT_NO_SECURE_DEPRECATE

// ������� ��� ���������� ������� ���������� �� �������
double* full_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        ptr_array[i] = pow(i + 1, 2) - pow(cos(i + 2), 2);
    }
    return ptr_array;
}

// ������� ��� ������ ��������� �������
int put_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", ptr_array[i]);
    }
    printf("\n");
    return 0;
}

// ������� ��� ��������� ��������� �������, �������� �� � 10 ���
double* calc_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        ptr_array[i] /= 10.0;
    }
    return ptr_array;
}

// ������� ��� �������� �������� � �������� ��������
int delete_k(double* ptr_array, int size, int k) {
    for (int i = k; i < size - 1; i++) {
        ptr_array[i] = ptr_array[i + 1];
    }
    return size - 1; // ���������� ����� ���������� ���������
}

// ������� ��� ������� �������� -999 ����� ���������� �������
double* insert_element(double* ptr_array, int* size, int index, double value) {
    int new_size = *size + 1;
    ptr_array = (double*)realloc(ptr_array, new_size * sizeof(double));
    if (ptr_array == NULL) {
        printf("������ ����������������� ������\n");
        exit(1);
    }
    for (int i = new_size - 1; i > index + 1; i--) {
        ptr_array[i] = ptr_array[i - 1];
    }
    ptr_array[index + 1] = value;
    *size = new_size;
    return ptr_array;
}

// ������� ��� ���������� ���������� ������� ���������� �� -1 �� 1
double* fill_random(double* ptr_array, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        ptr_array[i] = (double)rand() / RAND_MAX * 2 - 1;
    }
    return ptr_array;
}

// �������������� ������� ��� �������������� ������� � ����������� �� �������
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

// �������� �������
int main() {
    setlocale(LC_CTYPE,"RUS");
    double* ptr_array;
    int size;

    printf("������� ������ �������: ");
    scanf_s("%d", &size);

    // ��������� ������ ��� ������
    ptr_array = (double*)malloc(size * sizeof(double));
    if (ptr_array == NULL) {
        printf("������ ��������� ������\n");
        return -1;
    }

    // ���������� ������� ���������� ���������� �� -1 �� 1
    fill_random(ptr_array, size);

    // ������ ��������� �������
    printf("�������� ������:\n");
    put_elements(ptr_array, size);

    // ��������� ��������� �������
    calc_elements(ptr_array, size);
    printf("������ ����� ���������� ��������� � 10 ���:\n");
    put_elements(ptr_array, size);

    // �������� �������� � �������� ��������
    int del_index;
    printf("������� ������ �������� ��� ��������: ");
    scanf_s("%d", &del_index);
    if (del_index >= 0 && del_index < size) {
        size = delete_k(ptr_array, size, del_index);
        printf("������ ����� �������� �������� �� ������� %d:\n", del_index);
        put_elements(ptr_array, size);
    }
    else {
        printf("������������ ������ ��� ��������\n");
    }

    // ������� �������� -999 ����� ��������� �������
    int insert_index;
    printf("������� ������ ��� ������� �������� -999: ");
    scanf_s("%d", &insert_index);
    if (insert_index >= 0 && insert_index < size) {
        ptr_array = insert_element(ptr_array, &size, insert_index, -999);
        printf("������ ����� ������� -999 ����� ������� %d:\n", insert_index);
        put_elements(ptr_array, size);
    }
    else {
        printf("������������ ������ ��� �������\n");
    }

    // ������������ ������
    free(ptr_array);
    return 0;
}
