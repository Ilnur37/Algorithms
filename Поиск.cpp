/*Поиск*/

#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "windows.h"
#define NOT_FOUND -1
#define DEBUG
/*помощь при отладке, выводит массивы в файл.
раскомментировать " #define DEBUG " для вывода массивов*/

using namespace std;

//Последовательный поиск
template <typename T>
int BetterLinearSearch(T* sequence, const int elements, const T needKey, int& count);

//Быстрый последовательный поиск
template <typename T>
int SentinelLinearSearch(T* sequence, const int elements, const T needKey, int& count);

//Последовательный поиск в упорядоченном массиве
template <typename T>
int SequentialSearch(T* sequence, const int elements, const T needKey, int& count);

//Бинарный поиск в упорядоченном массиве
template <typename T>
int BinarySearch(T* sequence, const int elements, const T needKey, int& count);

//Случайная последовательность
void RandomSequence(int* sequence, int elements);

//Возрастающая последовательность
void AscendingSequence(int* sequence, int elements);

void First_Task();
void Second_Task();

template <typename T>
int(*MassSearch[]) (T*, const int, const T, int& count) = {
		BetterLinearSearch, SentinelLinearSearch,
		SequentialSearch, BinarySearch };


int main() {
	setlocale(LC_ALL, "ru");
	//SetConsoleOutputCP(CP_UTF8);

	//First_Task();

	Second_Task();

	return 0;
}

//Последовательный поиск
template <typename T>
int BetterLinearSearch(T* sequence, int elements, const T needKey, int& count) {
	cout << "\n-----BetterLinearSearch-----" << endl;
	int answer = NOT_FOUND;

	for (int i = 0; i < elements; i++) {
		count += 2;
		if (sequence[i] == needKey) {
			cout << "Количество сравнений в BetterLinearSearch: " << count << endl;
			return i;
		}
	}
	count++;
	cout << "Количество сравнений в BetterLinearSearch: " << count << endl;
	return answer;
}

//Быстрый последовательный поиск
template <typename T>
int SentinelLinearSearch(T* sequence, int elements, const T needKey, int& count) {
	cout << "\n-----SentinelLinearSearch-----" << endl;
	int answer = NOT_FOUND;
	int last = sequence[elements - 1];
	sequence[elements - 1] = needKey;

	int i = 0;
	while (sequence[i] != needKey) {
		count++;
		i++;
	}

	count++;
	sequence[elements - 1] = last;
	count++;
	if ((i < elements - 1) || (sequence[elements] == needKey)) {
		if (sequence[elements] == needKey) count++;
		cout << "Количество сравнений в Sentinel_linear_search: " << count << endl;
		return i;
	}
	else {
		cout << "Количество сравнений в Sentinel_linear_search: " << count << endl;
		return answer;
	}
}

//Последовательный поиск в упорядоченном массиве
template <typename T>
int SequentialSearch(T* sequence, int elements, const T needKey, int& count) {
	cout << "\n-----SequentialSearch-----" << endl;
	int answer = NOT_FOUND;

	int i = 0;
	int temp = sequence[elements - 1];
	sequence[elements - 1] = INT_MAX;

	while (!(needKey <= sequence[i])) {
		count++;
		i++;
	}
	count++;
	sequence[elements - 1] = temp;
	count++;

	if ((needKey == sequence[i])) {
		cout << "Количество сравнений в SequentialSearch: " << count << endl;
		return i;
	}
	else {
		cout << "Количество сравнений в SequentialSearch: " << count << endl;
		return answer;
	}
}

//Бинарный поиск в упорядоченном массиве
template <typename T>
int BinarySearch(T* sequence, const int elements, const T needKey, int& count) {
	cout << "\n-----BinarySearch-----" << endl;
	int answer = NOT_FOUND;
	int rightIndex = elements;
	int leftIndex = 0;
	int middleIndex;

	while (rightIndex >= leftIndex) {
		middleIndex = (leftIndex + rightIndex) / 2;
		count++;
		if (sequence[middleIndex] > needKey) {
			rightIndex = middleIndex - 1;
			count++;
		}
		else if (sequence[middleIndex] < needKey) {
			leftIndex = middleIndex + 1;
			count++;
		}
		else {
			count++;
			cout << "Количество сравнений в BinarySearch: " << count << endl;
			return middleIndex;
		}
	}
	cout << "Количество сравнений в BinarySearch: " << count << endl;
	return answer;
}

//Случайная последовательность чисел
void RandomSequence(int* sequence, int elements) {

#ifdef DEBUG
	ofstream out;								// поток для записи
	out.open("RandomSequence.txt");				// окрываем файл для записи
#endif

	for (int i = 0; i < elements; i++) {
		sequence[i] = rand() % elements;

#ifdef DEBUG
		out << sequence[i] << '\n';
#endif
	}
}

//Возрастающая последовательность
void AscendingSequence(int* sequence, int elements) {

#ifdef DEBUG
	ofstream out;								// поток для записи
	out.open("AscendingSequence.txt");		// открываем файл для записи
#endif

	for (int i = 0; i < elements; i++) {
		sequence[i] = i + 2;

#ifdef DEBUG
		out << sequence[i] << '\n';
#endif
	}
}

void First_Task() {

	int count;
	int elements = 30;
	int key;
	int keyIndex;

	cout << "Задание №1. Поиск числового элемента" << endl;
	cout << "\nВведите ключ для поиска в массиве чисел\n";
	cin >> key;

	int* randomNumberArr = new int[elements];
	int* ascendingNumberArr = new int[elements];

	RandomSequence(randomNumberArr, elements);
	AscendingSequence(ascendingNumberArr, elements);

	for (int i = 0; i < 4; i++)
	{
		count = 0;
		if (i < 2) keyIndex = MassSearch<int>[i](randomNumberArr, elements, key, count);
		else keyIndex = MassSearch<int>[i](ascendingNumberArr, elements, key, count);

		if (keyIndex != -1) cout << "Полученный индекс = " << keyIndex << '\n';
		else cout << "Ключ не найден\n";
	}

	delete[] randomNumberArr;
	delete[] ascendingNumberArr;
}

void Second_Task() {
	cout << "\n\nЗадание №2" << endl;

	int count = 0;
	int elements = 500000;
	int key;
	int keyIndex;

	/*cout << "\nВведите количество элементов в массиве\n";
	cin >> elements;*/

	cout << "\nВведите ключ для поиска в массиве\n";
	cin >> key;

	int* randomArr = new int[elements];
	int* ascendingArr = new int[elements];

	RandomSequence(randomArr, elements);
	AscendingSequence(ascendingArr, elements);

	for (int i = 0; i < 4; i++)
	{
		count = 0;
		//Получение времени начала работы функции
		auto begin_generate = std::chrono::steady_clock::now();

		if (i < 2) keyIndex = MassSearch<int>[i](randomArr, elements, key, count);
		else keyIndex = MassSearch<int>[i](ascendingArr, elements, key, count);

		auto end_generate = std::chrono::steady_clock::now();

		//Расчёт разности времён начала и окончания работы функции
		auto duration_f = std::chrono::duration_cast<std::chrono::microseconds>(end_generate - begin_generate);

		if (keyIndex != -1) cout << "Полученный индекс = " << keyIndex << '\n';
		else cout << "Ключ не найден" << '\n';
		cout << "Функция отработала за " << duration_f.count() << " мкС\n\n\n";
	}

	delete[] randomArr;
	delete[] ascendingArr;
}
