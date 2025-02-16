#include <random>
#include <iostream>
#include "arrays.h"
#include <chrono>
using namespace std::chrono;
using namespace std;

template <typename Func>
void measure_time(Func func) {
	using namespace std::chrono;

	auto t0 = steady_clock::now();  // начало измерения времени
	func();                         // выполнение функции
	auto t1 = steady_clock::now();  // конец измерения времени

	auto delta = duration_cast<milliseconds>(t1 - t0);  // время в миллисекундах
	std::cout << "Time delta (milliseconds): " << delta.count() << std::endl;
}

int main()
{
	const int SIZE = 10000000000;
	const int MIN_VALUE = 0;
	const int MAX_VALUE = 10000000;
	int dummysum = 0;
	random_device rd;
	mt19937 gen(rd());  // Генератор случайных чисел
	uniform_int_distribution<> distr(1000000, SIZE);
	int total;
	int* array2 = createAndFillArray<int>(SIZE, MIN_VALUE, MAX_VALUE);
	for (int i = 0; i < 1000; i++) {
		//int* array1 = MonotonicallyIncreasingArray<int>(SIZE, MIN_VALUE, MAX_VALUE);
		
		int value_to_search1 = array2[distr(gen)];
		//cout << value_to_search1 << "\n";
		measure_time([&]() {
			
			int index = sequential_search<int>(array2, SIZE, value_to_search1);
			dummysum += index;

		});
	}
}


