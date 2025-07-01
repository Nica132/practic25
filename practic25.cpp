#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void merge(float arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    float* leftArr = (float*)malloc(n1 * sizeof(float));
    float* rightArr = (float*)malloc(n2 * sizeof(float));

    // временные массивы
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    //временные массивов обратно
    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }


    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}


void mergeSort(float arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void writeToFile(const char* filename, float arr[], int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%f ", arr[i]);
    }
    fclose(file);
}


void generateData(float arr[], int size, float min, float max) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = min + (float)rand() / (float)(RAND_MAX / (max - min));
    }
}


void inputData(float arr[], int size) {
    printf("Введите %d чисел:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%f", &arr[i]);
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int size, mode;
    float min, max;

    printf("Программа сортировки слиянием\n");
    printf("Введите размер массива: ");
    scanf("%d", &size);

    float* arr = (float*)malloc(size * sizeof(float));

    printf("----------------------------\n");
    printf("Выберите режим ввода данных:\n");
    printf("1 - Ручной ввод\n");
    printf("2 - Случайная генерация\n");
    printf("----------------------------\n");
    scanf("%d", &mode);

