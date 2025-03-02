// Автор: Калашников А.Н.
#include <random>
#include <iostream>
#include "arrays.h"
#include <chrono>
using namespace chrono;
using namespace std;

/// Возвращает время выполнения функции func
template <typename Func>
int measure_time(Func func) { // в параметре можно использовать std::function из <functional>

	auto t0 = steady_clock::now();  // начало измерения времени
	func(); // компилятор понимает, что это функция
	auto t1 = steady_clock::now();  // конец измерения времени

	auto delta = duration_cast<milliseconds>(t1 - t0);  // время в миллисекундах
	cout << "Time (milliseconds): " << delta.count() << endl;
	return delta.count();
}

int main()
{
	test_is_sorted(); // тест функции сортировки
	test_sequential_search(); // тест функции последовательного поиска
	test_binary_search(); // тест функции бинарного поиска
	int size = 1'000;//'000'000; // размер массива
	const int MIN_VALUE = 0; // минимальное значение элемента
	const int MAX_VALUE = 1'000'000; // максимальное значение элемента
	int total_time = 0; // сумма всех измерений времени
	unsigned long long* array = createAndFillArray<unsigned long long>(size, MIN_VALUE, MAX_VALUE); // Массив из случайных чисел
	// Объект для доступа к аппаратному или программному источнику случайности
	// нужен для инициализации генератора случайных чисел
	random_device rd;
	mt19937 gen(rd());  // Генератор случайных чисел
	uniform_int_distribution<> distr(0, MAX_VALUE); // равномерное распределение

	// Проводим 10000 измерений для последовательного
	for (int i = 0; i < 1000; i++) {
		unsigned long long value_to_search = distr(gen); // случайное число, которое будем искать в массиве
		total_time += measure_time([&]() { // фактический параметр - анонимная функция(всё, что внутри скобок)
		size_t index = sequential_search<unsigned long long>(array, size, value_to_search);
		});
	}
	cout << "Массив\n";
	quickSort(array, 0, 1000);
	//shellSort<unsigned long long>(array, 1000, shellGap);
	//insertionSort<unsigned long long>(array, 1000);
	//bubbleSort(array, 1000);
	//mergeSort(array, 0, 999);
	for (int i = 0; i < 1000; i++) {
		cout << array[i] << "\n";
	}
	cout << "average time in ms for usual array = " << total_time / 1000.0 << "\n"; // среднее время выполнения среди 100 измерений
	delete[] array;

	total_time = 0;
	// Монотонно возрастающий массив из случайных чисел
	unsigned long long* monotonic_array = MonotonicallyIncreasingArray<unsigned long long>(size, MIN_VALUE, MAX_VALUE);

	// Проводим 10000 измерений для последовательного
	for (int i = 0; i < 1000; i++) {
		unsigned long long value_to_search = distr(gen); // случайное число, которое будем искать в массиве
		total_time += measure_time([&]() { // фактический параметр - анонимная функция(всё, что внутри скобок)
			size_t index = sequential_search<unsigned long long>(monotonic_array, size, value_to_search);
			});
	}
	// среднее время выполнения среди 10000 измерений
	cout << "average time in ms for monotonically increasing array(sequential search) = " << total_time / 1000.0 << "\n";

	total_time = 0;
	// Проводим 10000 измерений для бинарного поиска
	for (int i = 0; i < 1000; i++) {
		unsigned long long value_to_search = distr(gen); // случайное число, которое будем искать в массиве
		total_time += measure_time([&]() { // фактический параметр - анонимная функция(всё, что внутри скобок)
			size_t index = binary_search_recursive<unsigned long long>(monotonic_array, 0, size-1, value_to_search);
			});
	} 
	// среднее время выполнения среди 10000 измерений для бинарного поиска
	cout << "average time in ms for monotonically increasing array(binary search) = " << total_time / 1000.0;
	delete[] monotonic_array;
}


