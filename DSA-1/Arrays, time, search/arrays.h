// Автор: Калашников А.Н.
#pragma once
#include <iostream>
#include <random>   // библиотека для генерации случайных чисел
#include <fstream>
#include <algorithm> // Для max и min
using namespace std;

/// Возвращает массив типа T* размера size с минимальным значением min_value и максимальным max_value
template <typename T>
T* createAndFillArray(size_t size, T min_value, T max_value) {
    // Объект для доступа к аппаратному или программному источнику случайности
    // нужен для инициализации генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());  // Генератор случайных чисел
    uniform_int_distribution<> distr(min_value, max_value); // равномерное распределение

    T* array = new T[size];  // Создание массива

    for (size_t i = 0; i < size; ++i) {
        array[i] = distr(gen);  // Заполнение массива случайными числами
    }

    return array;

}

/// Возвращает монотонно возрастающий массив типа T* размера size с минимальным значением min_value 
template <typename T>
T* MonotonicallyIncreasingArray(size_t size, T min_value, T max_value) {
   // Объект для доступа к аппаратному или программному источнику случайности
    // нужен для инициализации генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());  // Генератор случайных чисел
    uniform_int_distribution<> distr(min_value, max_value); // равномерное распределение
    T* array = new T[size];  // Создание массива
    array[0] = distr(gen); // Нулевой элемент создаём случайным образом
    for (size_t i = 1; i < size; ++i) {
        // Заполнение массива случайными числами
        array[i] = array[i-1] + distr(gen)/1000; // для монотонного возрастания к каждому следующему элементу прибавляем distr(gen)/10
      
    }
    return array;
}

/// Записывает массив array типа T* размера size в файл filename
template <typename T>
void array_to_file(T* array, size_t size, const string& filename) {
    ofstream f(filename); // Открываем файл на запись
    if (f.is_open()) {
        for (size_t i = 0; i < size; ++i) { 
            f << array[i] << " ";
        }
        f.close();
    }
}

// Возвращает булевое значение, отвечающее на вопрос, отсортирован массив array типа T* размера или нет
template <typename T>
bool is_sorted(T* array, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        if (array[i] < array[i - 1]) { // Если каждый следующий массив меньше предыдущего
            return false;  // Если порядок нарушен
        }
    }
    return true; // Если массив отсортирован
}

/// Если элемент value найден алгоритмом последовательного поиска - возвращает индекс элемента в массиве array типа T* размера size
/// Если не найден - возвращает индекс на 1 больше крайнего индекса массива
/// Временная сложность: O(1) для лучшего случая, O(n) - для среднего и худшего случая
/// Дополнительная память: O(1)
template <typename T>
size_t sequential_search(T* array, size_t size, T value) {
    for (size_t i = 0; i < size; ++i) {
        if (array[i] == value) { // Если элемент массива соответствует искомому
            return i;  // Возвращаем индекс найденного элемента
            
        }
    }
    return size;  // Если элемент не найден, возвращаем индекс на 1 больше последнего
}

/// Шаблонная рекурсивная функция бинарного поиска
/// Возвращает индекс элемента, если он найден, иначе -1
/// Временная сложность: O(1) для лучшего случая, O(log n) - для среднего и худшего случая
/// Дополнительная память: O(log n)
template <typename T>
long long binary_search_recursive(T* array, long long left, long long right, T value) {
    if (left > right) {
        return -1; // Элемент не найден
    }
    long long mid = left + (right - left) / 2.0; // Избегаем переполнения
    if (array[mid] == value) {
        return mid; // Найден элемент
        
    }
    else if (array[mid] < value) {
        return binary_search_recursive(array, mid + 1, right, value); // Ищем в правой части
    }
    else {
        return binary_search_recursive(array, left, mid - 1, value); // Ищем в левой части
    }
}


/* Задание 6. Сортировки
Реализуйте алгоритмы сортировки
Сортировка слиянием. Создайте отдельную функцию для слияния двух отсортированных массивов. (до 6 марта).
Один или несколько алгоритмов сортировки, работающих за O(n^2) в среднем случае (до 6 марта).
Быстрая сортировка (quick sort). Создайте отдельную функцию для сортировки массива(частичной) относительно опорного значения.
Сортировка Шелла
Напишите тесты.
Приведите в коде ссылку на это задание. Текст задания.
Документируйте функции, пишите пояснения к алгоритмам и коду.
Указывайте оценку BigO для временной сложности алгоритма для разных классов входных данных, оценку дополнительных затрат памяти.
Постройте график времени сортировки массива в зависимости от его размера
Для реализованных алгоритмов. Сравните форму кривой с классом сложности BigO для среднего случая.
Добавьте график времени работы для функции сортировки массива из стандартной библиотеки. Напишите, какой алгоритм эта функция реализует.
Учитывайте замечания к измерению времени работы функций из предыдущих заданий и лекций.*/

/// Функция для слияния двух отсортированных подмассивов
/// Временная сложность: O(n) для всех классов входных данных
/// Дополнительная память: O(n)
template <typename T>
void merge(T* arr, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    T* leftArr = new T[n1];
    T* rightArr = new T[n2];
    // Копируем элементы в левый и правый временные массивы с помощью copy
    copy(arr + left, arr + left + n1, leftArr);
    copy(arr + mid + 1, arr + mid + 1 + n2, rightArr);
    size_t i = 0, j = 0, k = left;
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
    // Копируем оставшиеся элементы из leftArr, если они есть
    copy(leftArr + i, leftArr + n1, arr + k);
    // Обновляем k после копирования leftArr 
     k += (n1 - i);

    // Копируем оставшиеся элементы из rightArr, если они есть
    copy(rightArr + j, rightArr + n2, arr + k);

    delete[] leftArr;
    delete[] rightArr;
}

/// Сортировка слиянием массива arr с левой границей left и правой границей right по неубыванию
/// Временная сложность: O(n log n) для всех классов входных данных
/// Дополнительная память: O(n)
template <typename T>
void mergeSort(T* arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


/// Сортировка пузырьком массива array размера size по неубыванию
/// Временная сложность: O(n) для лучшего случая, O(n^2) - для среднего и худшего случая
/// Дополнительная память: O(1)
template <typename T>
void bubbleSort(T* array, size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

/// Сортировка вставками массива array размера size по неубыванию
/// Временная сложность: O(n) для лучшего случая, O(n^2) - для среднего и худшего случая
/// Дополнительная память: O(1)
template <typename T>
void insertionSort(T* array, size_t size) {
    for (size_t i = 1; i < size; i++) {
        T key = array[i];
        size_t j = i;
        while (j > 0 && array[j - 1] > key) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = key;
    }
}

/// Сортировка Шелла массива array размера size по неубыванию, изменение шага сортировки осуществляется в функции gapFunction
/// Временная сложность: O(n log n) в лучшем случае, O(n(log(n))^2) - в среднем и худшем случае
/// Дополнительная память: O(1)
template <typename T>
void shellSort(T* array, size_t size, size_t(*gapFunction)(size_t, size_t)) {
    for (size_t gap = gapFunction(size, 0); gap > 0; gap = gapFunction(size, gap)) {
        for (size_t i = gap; i < size; i++) {
            T temp = array[i];
            size_t j = i;
            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
    }
}

/// Функция для разбиения массива array с нижней границей low и верхней границей high относительно опорного элемента
/// Временная сложность: O(n) для всех классов входных данных
/// Дополнительная память: O(1)
template <typename T>
size_t partition(T* array, size_t low, size_t high) {
    size_t mid = (low + high) / 2;
    if (array[low] > array[mid])
        swap(array[low], array[mid]);
    if (array[low] > array[high])
        swap(array[low], array[high]);
    if (array[mid] > array[high])
        swap(array[mid], array[high]);
    // Теперь array[mid] является медианой
    swap(array[mid], array[high]);
    
    T pivot = array[high];
    size_t i = low;

    for (size_t j = low; j < high; j++) {
        if (array[j] < pivot) {
            swap(array[i], array[j]);
            i++;
        }
    }
    swap(array[i], array[high]);
    return i;
}

/// Быстрая сортировка массива array с нижней границей low и верхней границей high по неубыванию
/// Временная сложность: O(n log n) в лучшем и среднем случае, O(n^2) - в худшем случае
/// Дополнительная память: O(log n) 
template <typename T>
void quickSort(T* array, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(array, low, high);
        if (pi > 0) quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}


/// Последовательность Шелла (обычная) - шаг уменьшается в 2 раза
size_t shellGap(size_t size, size_t prevGap);

size_t fibonacciGap(size_t size, size_t prevGap);

/// Тест функции сортировки массива is_sorted
void test_is_sorted();

/// Функция тестирования последовательного поиска
void test_sequential_search();

/// Тест функции бинарного поиска
void test_binary_search();

void testMergeSort();

// Тесты для bubbleSort
void testBubbleSort();

// Тесты для insertionSort
void testInsertionSort();

// Тесты для shellSort
void testShellSort();

// Тесты для quickSort
void testQuickSort();

