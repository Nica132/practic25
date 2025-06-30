#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// Функция слияния двух подмассивов для float
void merge(float arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы с динамическим выделением памяти
    float* leftArr = (float*)malloc(n1 * sizeof(float));
    float* rightArr = (float*)malloc(n2 * sizeof(float));

    if (leftArr == NULL || rightArr == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }

    // Копируем данные во временные массивы
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Слияние временных массивов обратно в arr[left..right]
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

    // Копируем оставшиеся элементы leftArr[], если есть
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы rightArr[], если есть
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}

// Функция сортировки слиянием
void mergeSort(float arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Функция записи массива в файл
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

// Функция генерации случайных чисел в заданном диапазоне
void generateData(float arr[], int size, float min, float max) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = min + (float)rand() / (float)(RAND_MAX / (max - min));
    }
}

// Функция ручного ввода данных
void inputData(float arr[], int size) {
    printf("Введите %d чисел (через пробел или Enter):\n", size);
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
    if (arr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    printf("Выберите режим ввода данных:\n");
    printf("1 - Ручной ввод\n");
    printf("2 - Случайная генерация\n");
    scanf("%d", &mode);

    switch (mode) {
    case 1:
        inputData(arr, size);
        break;
    case 2:
        printf("Введите минимальное значение: ");
        scanf("%f", &min);
        printf("Введите максимальное значение: ");
        scanf("%f", &max);
        generateData(arr, size, min, max);
        break;
    default:
        printf("Неверный режим!\n");
        free(arr);
        return 1;
    }

    // Запись исходного массива в файл
    writeToFile("input.txt", arr, size);

    // Сортировка массива
    mergeSort(arr, 0, size - 1);

    // Запись отсортированного массива в файл
    writeToFile("output.txt", arr, size);

    // Вывод результатов
    printf("\nИсходные данные сохранены в input.txt\n");
    printf("Отсортированные данные сохранены в output.txt\n");
    printf("Результат сортировки:\n");
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}