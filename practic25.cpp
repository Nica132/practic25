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

