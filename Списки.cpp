#include <iostream>
#include "windows.h"

#define LIMIT 50
using namespace std;

void CreateHead(double value);  			// Формирование головы

void PrintList();  		     				// Печать списка

void Push_Front(double value);  	 		// Добавление элемента в начало списка
void Pop_Front(); 	 						// Удаление элемента из начала списка

void Push_Back(double value);  				// Добавление элемента в конец списка
void Pop_Back();  	     					// Удаление элемента из конца списка

void Insert(double value, int index);		// Добавление элемента в выбранное место списка
void Remove(int index);  		 			// Удаление выбранного элемента из списка

void SearchNode(double value);   			// Поиск элемента
void SearchMaximum();						// Поиск максимального элемента

void ClearList(); 			 				// Удаление списка

void Menu(); 				 				// Вывод доступных действий


struct List {
	double data;
	int index;

	static int listSize;

	List* pointerNext;				//указатель на слудующий элемент
	List* pointerPrev;				//указатель на предыдущий элемент
};


List* headNode = nullptr;
List* currentNode = nullptr;
List* newNode = nullptr;

int List::listSize = 0;

int main() {
	//SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "Russian");

	int choiceCase;
	double bufferElement;  			     //Элемент буферный
	int bufferIndex;
	int size;
	double value = (double)(rand() % LIMIT) / 10;

	// Формирование головы
	CreateHead(value);


	cout << "\nВведите размерность создаваемого списка " << endl;
	cin >> size;

	for (int i = 0; i < size - 1; i++) {  			// Формирование списка
		value = (double)(rand() % LIMIT) / 10;
		Push_Back(value);
	}


	while (true) {
		Menu();

		cin >> choiceCase;
		switch (choiceCase) {
		case 1:
			cout << "\nСформированный актуальный список:" << endl;
			PrintList();
			continue;
		case 2:
			cout << "\nВведите значение для поиска" << endl;
			cin >> bufferElement;
			SearchNode(bufferElement);
			continue;
		case 3:
			cout << "\nПоиск узла с максимальным значением данных" << endl;
			SearchMaximum();
			continue;
		case 4:
			cout << "\nВведите новый элемент для его включения в начало списка" << endl;
			cin >> bufferElement;
			Push_Front(bufferElement);
			continue;
		case 5:
			cout << "\nУдаление узла из начала списка" << endl;
			Pop_Front();
			continue;
		case 6:
			cout << "\nВведите новый элемент для его включения в конец списка" << endl;
			cin >> bufferElement;
			Push_Back(bufferElement);
			continue;
		case 7:
			cout << "\nУдаление узла из конца списка" << endl;
			Pop_Back();
			continue;
		case 8:
			cout << "\nВведите новый элемент для включения в список" << endl;
			cin >> bufferElement;
			cout << "\nВведите индекс узла для включаемого элемента" << endl;
			cin >> bufferIndex;
			Insert(bufferElement, bufferIndex);
			continue;
		case 9:
			cout << "\nУдаление элемента из заданной позиции списка. Введите номер позиции:" << endl;
			cin >> bufferIndex;
			Remove(bufferIndex);
			continue;
		case 10:
			cout << "\nАктуальный размер списка:" << endl;
			cout << List::listSize << endl;
			continue;
		case 11:
			cout << "\nПрограмма успешно завершена." << endl;
			ClearList();
			return 0;
		default:
			cout << "\nВведенное значение не распознано." << endl;
			continue;
		}
	}
}

void Menu()
{
	cout << "\nВыберите действие:" << endl;
	cout << "1 - Посмотреть текущий список." << endl;
	cout << "2 - Поиск узла с заданным значением." << endl;
	cout << "3 - Поиск узла с максимальным значением." << endl;
	cout << "4 - Добавить элемент в начало списка." << endl;
	cout << "5 - Удалить элемент из начала списка." << endl;
	cout << "6 - Добавить элемент в конец списка." << endl;
	cout << "7 - Удалить элемент из конца списка." << endl;
	cout << "8 - Добавить элемент в заданную позицию списка." << endl;
	cout << "9 - Удалить элемент из заданной позиции списка." << endl;
	cout << "10 - Показать актуальный размер списка." << endl;
	cout << "11 - Удаление списка и выход и программы." << endl;
}

// Формирование головы
void CreateHead(double value) {
	headNode = new List;  			   	   		 	//  Выделение памяти под заглавный элемент

	headNode->data = value;							//  Заполняем элемент
	headNode->index = 0;
	List::listSize++;

	headNode->pointerPrev = nullptr;       			//  Указатель на следующий элемент
	headNode->pointerNext = nullptr;       			//  Указатель на предыдущий элемент
}

// Добавление элемента в конец списка
void Push_Back(double value) {

	if (headNode->pointerNext == nullptr) {
		newNode = new List;  			   			//  Выделение памяти под новый элемент

		newNode->data = value;  			  		//  Заполняем элемент
		newNode->index = (headNode->index + 1);
		List::listSize++;

		headNode->pointerNext = newNode;
		newNode->pointerNext = nullptr;        		//  Новый элемент указывает на начало
		newNode->pointerPrev = headNode;
	}
	//если больше одного элемента
	else {
		currentNode = headNode;

		while (currentNode->pointerNext != nullptr) {	//Пока не достигнем последнего элемента
			currentNode = currentNode->pointerNext;		
		}

		newNode = new List;								//  Выделение памяти под новый элемент
		currentNode->pointerNext = newNode;				//  Перенос указателя прошлого последнего элемента на новый

		newNode->data = value;							//  Заполняем элемент
		newNode->index = (currentNode->index + 1);
		List::listSize++;

		newNode->pointerNext = nullptr;
		newNode->pointerPrev = currentNode;
	}

	//  Выделение памяти под новый элемент
	//  Заполняем элемент
	//  Сохраняем указатель на последний элемент
	//  Последний элемент указывает на новый
	//  Новый элемент указывает на начало
	//  Новый элемент указывает на предыдущий
	//  Перенос указателя прошлого последнего элемента на новый
}

// Удаление элемента из конца списка
void Pop_Back() {
	currentNode = newNode->pointerPrev;			//Сохраняем указатель на предпоследний элемент

	//Удаление последнего
	newNode->pointerPrev = nullptr;
	currentNode->pointerNext = nullptr;
	delete currentNode->pointerNext;
	newNode = nullptr;
	delete newNode;

	List::listSize--;

	newNode = currentNode;
}

// Добавление элемента в начало списка
void Push_Front(double value) {
	currentNode = headNode;						
	headNode = new List;						//  Выделение памяти под новый элемент
	currentNode->pointerPrev = headNode;		//  Перенос указателя прошлого первого элемента на новый


	headNode->data = value;						//  Заполняем элемент
	headNode->index = 0;
	List::listSize++;

	headNode->pointerNext = currentNode;
	headNode->pointerPrev = nullptr;

	while (currentNode->pointerNext != nullptr) {
		currentNode->index++;
		currentNode = currentNode->pointerNext;
	}

	currentNode->index++;

}

// Удаление элемента из начала списка
void Pop_Front() {
	currentNode = headNode;					//Сохраняем указатель на головной элемент
	currentNode->pointerNext->index = currentNode->index;

	while (currentNode->pointerNext->pointerNext != nullptr) {
		currentNode = currentNode->pointerNext;
		currentNode->pointerNext->index = (currentNode->index + 1);
	}

	currentNode = headNode;						//Сохраняем указатель на головной элемент
	headNode = headNode->pointerNext;			//Указатель на головной элемент указывает на следующий
	headNode->pointerPrev = nullptr;

	//Удаление предыдущего головного элемента
	currentNode->pointerNext = nullptr;
	delete currentNode->pointerNext;
	currentNode = nullptr;
	delete currentNode;


	List::listSize--;

	currentNode = newNode->pointerPrev;
}

// Добавление элемента в выбранное место списка
void Insert(double value, int index) {
	
	if (index == 0) {							//Добавление элемента в начало списка
		Push_Front(value);
	}
	else if (index == List::listSize - 1) {		//Добавление элемента в конец списка
		Push_Back(value);
	}
	//Добавление элемента в выбранное место списка
	else {
		currentNode = headNode;					//Сохраняем указатель на головной элемент

		while (currentNode->pointerNext->index != index) {
			currentNode = currentNode->pointerNext;
		}
		newNode = new List;						//Выделение памяти под новый элемент

		//Связываем новый элемент со списком
		currentNode->pointerNext->pointerPrev = newNode;
		newNode->pointerNext = currentNode->pointerNext;

		currentNode->pointerNext = newNode;
		newNode->pointerPrev = currentNode;

		newNode->data = value;

		List::listSize++;

		newNode = headNode;
		for (int i = 1; i < List::listSize; i++) {
			newNode = newNode->pointerNext;
			newNode->index = i;
		}
	}
}

// Удаление выбранного элемента из списка
void Remove(int index) {
	if (index == 0) {							// Удаление выбранного элемента из начала списка
		Pop_Front();
	}
	else if (index == List::listSize - 1) {		// Удаление выбранного элемента из конца списка
		Pop_Back();
	}
	// Удаление выбранного элемента из списка
	else {										
		currentNode = headNode;					//Сохраняем указатель на головной элемент

		while (currentNode->index != index) {
			currentNode = currentNode->pointerNext;
		}

		//Связываем список после удаления элемента
		currentNode->pointerPrev->pointerNext = currentNode->pointerNext;
		currentNode->pointerNext->pointerPrev = currentNode->pointerPrev;
		
		//Удаление выбранного элемента
		currentNode->pointerNext = nullptr;
		currentNode->pointerPrev = nullptr;
		currentNode = nullptr;
		delete currentNode;

		List::listSize--;

		newNode = headNode;
		for (int i = 1; i < List::listSize; i++) {
			newNode = newNode->pointerNext;
			newNode->index = i;
		}
	}
}

// Поиск элемента
void SearchNode(double value) {
	bool nodeFound = false;

	currentNode = headNode;				//  Сохраняем указатель на головной элемент

	int index = 0;
	while (index < List::listSize) {

		if (currentNode->data == value) {
			nodeFound = true;
			cout << "\nПоиск прошел успешно. Индекс узла списка с нужным значением: " << currentNode->index << endl;
		}

		index++;
		currentNode = currentNode->pointerNext;
	}

	if (!nodeFound) {
		cout << "\nПоиск прошел неудачно. Узел с заданным значением отсутствует в списке" << endl;
	}
}

// Поиск максимального элемента
void SearchMaximum() {
	double maximum = headNode->data;
	double maximumIndex = headNode->index;

	currentNode = headNode;

	int i = 0;
	while (i < List::listSize) {
		if (currentNode->data > maximum) {
			maximum = currentNode->data;
			maximumIndex = currentNode->index;
		}

		currentNode = currentNode->pointerNext;
		i++;
	}

	cout << "\nМаксимальное значение данных в списке: " << maximum << endl;
	cout << "\nИндекс максимального значения данных в списке: " << maximumIndex << endl;
}

// Удаление списка
void ClearList() {

	while (headNode != newNode) {
		Pop_Front();
	}

	headNode = nullptr;
	delete headNode;

	newNode = nullptr;
	delete newNode;
}

// Печать списка
void PrintList() {
	currentNode = headNode;

	while (currentNode != nullptr) {
		cout << currentNode->index << ") " << currentNode->data << endl;
		currentNode = currentNode->pointerNext;
	}
}