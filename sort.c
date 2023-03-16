#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

int getrand(int min, int max) 
{
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() 
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

//counting sort
void counting_sort(int arr[], int n, int max_val) 
{
    int count[max_val+1];
    for(int i = 0; i < max_val+1; i++) {
        count[i] = 0;
    }

    // Подсчитываем количество элементов со значением i 
    for(int i = 0; i < n; i++) {
        count[arr[i]] += 1;
    }

    // Суммируем элементы в массиве count
    for(int i = 1; i < max_val+1; i++) {
        count[i] += count[i-1];
    }

    // Размещаем элементы в новом массиве, сохраняя порядок
    int output[n];
    for(int i = n-1; i >= 0; i--) {
        count[arr[i]] -= 1;
        output[count[arr[i]]-1] = arr[i];
    }

    // Копируем отсортированный массив обратно в исходный массив
    for(int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

//bubble sort
void bubble_sort(int arr[], int n) 
{
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                // Меняем местами элементы
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

//merge sort
// Слияние двух отсортированных подмассивов в один отсортированный подмассив
void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1; // Длина первого подмассива
    int n2 = right - middle; // Длина второго подмассива
    int L[n1], R[n2]; // Создаем временные массивы для хранения подмассивов

    // Копируем данные из исходного массива во временные массивы L и R
    for(int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for(int j = 0; j < n2; j++) {
        R[j] = arr[middle + 1 + j];
    }

    int i = 0; // Индекс первого подмассива
    int j = 0; // Индекс второго подмассива
    int k = left; // Индекс объединенного подмассива

    // Сравниваем элементы из подмассивов L и R и копируем наименьший элемент в объединенный подмассив
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы из подмассива L, если они есть
    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы из подмассива R, если они есть
    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Функция рекурсивной сортировки Merge Sort
void merge_sort(int arr[], int left, int right) {
    if(left < right) {
        int middle = left + (right - left)/2; // Находим середину массива
        merge_sort(arr, left, middle); // Рекурсивно сортируем левый подмассив
        merge_sort(arr, middle+1, right); // Рекурсивно сортируем правый подмассив
        merge(arr, left, middle, right); // Сливаем отсортированные подмассивы в один
    }
}