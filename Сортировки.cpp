/*Сортировки*/


#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include "windows.h"
#define DEBUG
/*помощь при отладке, выводит массивы в файл.
раскомментировать " #define DEBUG " для вывода массивов*/

using namespace std;

const int maximum = 10000;
const int minimum = 0;
const int numberOfFunc = 3;

int comparisonCount = 0;
int swapCount = 0;

void PrintSequence(int* sequence, int elements) {
	cout << endl;
	for (int i = 0; i < elements; i++) {
		cout << sequence[i] << " ";
	}
}

//Случайная последовательность
void RandomSequence(int* sequence, int elements) {
	srand(time(NULL));
	cout << "Random Sequence" << endl;

	for (int i = 0; i < elements; i++) {
		sequence[i] = rand() % maximum;
		//cout << sequence[i] << "\n";
	}
}

//Возрастающая последовательность
void AscendingSequence(int* sequence, int elements) {
	cout << "Ascending Sequence" << endl;
	int temp = minimum;
	for (int i = 0; i < elements; i++) {
		sequence[i] = temp;
		temp += (maximum - minimum) / elements;
		//cout << sequence[i] << "\n";
	}
}

//Убывающая последовательность
void DescendingSequence(int* sequence, int elements) {
	cout << "Descending Sequence" << endl;
	int temp = maximum;

	int index = 0;
	for (int i = elements; i > 0; i--) {
		sequence[index] = temp;
		temp -= (maximum - minimum) / elements;

		//cout << "sequence[" << index << "] = " << sequence[index] << "\n";
		//cout << sequence[index] << "\n";
		index++;
	}
}

void ShakerSort(int* sequence, int elements) {
	//cout << "\n\nShaker Sort\n";

	int control = elements - 1;
	int left = 0;
	int right = elements - 1;

	do {
		for (int i = left; i < right; i++) {
			comparisonCount++;

			if (sequence[i] > sequence[i + 1]) {
				std::swap(sequence[i], sequence[i + 1]);
				swapCount++;
				control = i;
			}

		}

		right = control;
		for (int i = right; i > left; i--) {
			comparisonCount++;

			if (sequence[i] < sequence[i - 1]) {
				std::swap(sequence[i], sequence[i - 1]);
				swapCount++;
				control = i;
			}
		}
		left = control;

		#ifdef DEBUG
		PrintSequence(sequence, elements);
		#endif

	} while (left < right);
}

void QuickSort(int* sequence, int first, int last, int elements)
{
	int middle;
	int left = first, right = last;
	middle = sequence[(left + right) / 2]; //вычисление опорного элемента
	do {
		while (sequence[left] < middle) left++;
		while (sequence[right] > middle) right--;
		if (left <= right) {
			comparisonCount++;

			if (sequence[left] > sequence[right]) {
				std::swap(sequence[left], sequence[right]);
				swapCount++;
			}

			left++;
			right--;
		}
		#ifdef DEBUG
		PrintSequence(sequence, elements);
		#endif

	} while (left < right);

	if (first < right) QuickSort(sequence, first, right, elements);
	if (left < last) QuickSort(sequence, left, last, elements);
}

int main()
{
	setlocale(LC_ALL, "rus");

	int elements;
	int* sortArray;

	// Создаем массив указателей на функции генераторы последовательностей
	void(*getSequence[numberOfFunc]) (int* sequence, int elements) = {
			RandomSequence, AscendingSequence, DescendingSequence
	};

	cout << "Введите количество элементов:\n";
	cin >> elements;

	sortArray = new int[elements];

	cout << "----------------------------------------Шейкерная сортировка----------------------------------------" << endl;
	for (auto& j : getSequence) {
		j(sortArray, elements);

		swapCount = 0;
		comparisonCount = 0;
		
		#ifdef DEBUG
		PrintSequence(sortArray, elements);
		#endif

		//Получение времени начала работы функции
		auto begin_sort = std::chrono::steady_clock::now();

		ShakerSort(sortArray, elements);

		auto end_sort = std::chrono::steady_clock::now();

		#ifdef DEBUG
		PrintSequence(sortArray, elements);
		#endif
		//Расчёт разности времён начала и окончания работы функции
		auto duration_of_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_sort - begin_sort);

		std::cout << "\n\nКоличество пересылок = " << swapCount << std::endl;
		std::cout << "Количество сравнений = " << comparisonCount << std::endl;
		std::cout << "Время работы сортировки = " << duration_of_sort.count() << " мкС\n" << std::endl;

	}

	cout << "----------------------------------------Быстрая сортировка----------------------------------------" << endl;
	for (auto& i : getSequence) {
		i(sortArray, elements);

		swapCount = 0;
		comparisonCount = 0;

		#ifdef DEBUG
		PrintSequence(sortArray, elements);
		#endif

		//Получение времени начала работы функции
		auto begin_sort = std::chrono::steady_clock::now();

		QuickSort(sortArray, 0, elements - 1, elements);

		auto end_sort = std::chrono::steady_clock::now();
		
		#ifdef DEBUG
		PrintSequence(sortArray, elements);
		#endif

		//Расчёт разности времён начала и окончания работы функции
		auto duration_of_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_sort - begin_sort);

		std::cout << "\n\nКоличество пересылок = " << swapCount << std::endl;
		std::cout << "Количество сравнений = " << comparisonCount << std::endl;
		std::cout << "Время работы сортировки = " << duration_of_sort.count() << " мкС\n" << std::endl;

	}

	delete[] sortArray;
}
