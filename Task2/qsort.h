#pragma once

// Быстрая сортировка (функция принимает индексы начала
// и конца участка массива, который необходимо отсортировать)
void quickSort(int array[], int start, int end);

//
void swap(int* a, int* b);

int partition(int array[], int start, int end);
