#include <random>
#include <iostream>
#include "arrays.h"
#include <chrono>
using namespace chrono;
using namespace std;

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
	test_is_sorted();
	int size = 10000000;
	const int MIN_VALUE = 0;
	const int MAX_VALUE = 10000000;
	int total_time = 0;
	//int* array = createAndFillArray<int>(size, MIN_VALUE, MAX_VALUE);
	//random_device rd;
	//mt19937 gen(rd());  // Генератор случайных чисел
	//uniform_int_distribution<> distr(10000, size); // равномерное распределение
	//for (int i = 0; i < 100; i++) {
	//	
	//	int value_to_search1 = array[distr(gen)];
	//	total_time += measure_time([&]() { // фактический параметр - анонимная функция(всё, что внутри скобок)
	//	int index = sequential_search<int>(array, size, value_to_search1);

	//	});
	//}
	//cout << "average time in ms for usual array = " << total_time / 100.0;
	//total_time = 0;
	int* monotonic_array = MonotonicallyIncreasingArray<int>(size, MIN_VALUE, MAX_VALUE);
	random_device rd;
	mt19937 gen(rd());  // Генератор случайных чисел
	uniform_int_distribution<> distr(10000, size); // равномерное распределение
	//uniform_int_distribution<> distr(10000, size); // равномерное распределение
	for (int i = 0; i < 100; i++) {
		int value_to_search1 = monotonic_array[distr(gen)];
		total_time += measure_time([&]() { // фактический параметр - анонимная функция(всё, что внутри скобок)
			int index = sequential_search<int>(monotonic_array, size, value_to_search1);
			});
	}
	cout << "average time in ms for monotonically increasing array = " << total_time / 100.0;
}


