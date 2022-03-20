/*Бинарное дерево*/

//Вариант 13: Определить, каких чисел больше - положительных или отрицательных. [-100;100]

#include <iostream>
//#define size 15
#define size 15
using namespace std;

int arr[size] = { 0, -50, 50, -75, -25, 25, 75, -90, -60, -40, -10, 10, 40, 60, 90 };
//int arr[size] = {63, 27, 80, 13, 51, 70, 92, 26, 33, 58, 82, 57, 60};
//int arr[size] = { 15, 14, 13 };
//int arr[size] = { 15, 16, 17 };
struct binary_tree {
	int data;

	binary_tree* left_el;				//указатель на левый элемент
	binary_tree* right_el;				//указатель на правый элемент
	binary_tree* back;					//указатель на родителя
	int level;							//уровень
};
binary_tree* first = nullptr;			//указатель на корень древа
binary_tree* minNode = nullptr;

void CreateFirst();															//создание корневого элемента
struct binary_tree* Push(binary_tree* currentNode, int value);				//заполнение дерева

void PrintTree( binary_tree* currentNode, int level);						//печать дерева

struct binary_tree* Search( binary_tree* currentNode, int key);				//поиск элемента по ключу

struct binary_tree* SearchMin(binary_tree* currentNode);					//поиск минимального узла

void RemoveNode(binary_tree* currentNode, int key);							//удаление узла

void ChangeLvL(binary_tree* currentNode);									//измение уровня узла

void InOrderTravers(binary_tree* currentNode, int& count, int& maxLvl);		//Симметричный обход

void Task2(binary_tree* currentNode, int& countPos, int& countNeg);			//

void Freemem(binary_tree* currentNode);										//очистка памяти

void Menu();

int main() {
	//SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "rus");
	int bufferElement;  			     //Элемент буферный
	int choiceCase;
	int count, maxLvl;
	int countPos, countNeg;
	CreateFirst();

	for (int i = 1; i < size; i++) Push(first, arr[i]);

	while (true) {
		Menu();

		cin >> choiceCase;
		switch (choiceCase) {
		case 1:
			cout << "\t\tБинарное дерево\n\n";
			cout << "Lvl 0:\tLvl 1:\tLvl 2:\tLvl 3:\tLvl 4:\n\n";
			PrintTree(first, 0);
			continue;
		case 2:
			cout << "\nВведите искомый элемент: ";
			cin >> bufferElement;
			cout << "\nПоиск элемента " << bufferElement << "...\n";
			cout << "Путь: ";
			Search(first, bufferElement);
			continue;
		case 3:
			cout << "\nВведите число, которое нужно добавить: ";
			cin >> bufferElement;
			Push(first, bufferElement);
			cout << "\nУзел добавлен. Новое дерево:\n";
			cout << "Lvl 0:\tLvl 1:\tLvl 2:\tLvl 3:\tLvl 4:\n\n";
			PrintTree(first, 0);
			continue;
		case 4:
			cout << "\nВведите число, которое нужно удалить: ";
			cin >> bufferElement;
			RemoveNode(first, bufferElement);
			cout << "\nНовое дерево:\n";
			cout << "Lvl 0:\tLvl 1:\tLvl 2:\tLvl 3:\tLvl 4:\n\n";
			PrintTree(first, 0);
			continue;
		case 5:
			cout << "\nСимметричный обход дерева, нахождение высоты дерева и количества узлов.\n";
			count = 0;
			maxLvl = 0;
			InOrderTravers(first, count, maxLvl);
			cout << "\n Высота дерева: " << maxLvl + 1 << endl;
			cout << " Количество узлов: " << count << endl;
			continue;
		case 6:
			cout << "Определение каких чисел больше - положительных или отрицательных." << endl;
			countPos = 0;
			countNeg = 0;
			Task2(first, countPos, countNeg);
			cout << "Отрицательных чисел: " << countNeg << endl;
			cout << "Положительных чисел: " << countPos << endl;
			if (countNeg > countPos) cout << "Отрицательных чисел больше." << endl;
			if (countNeg < countPos) cout << "Полжительных чисел больше." << endl;
			if (countNeg == countPos) cout << "Отрицательных чисел и положительных равное количество." << endl;
			continue;
		case 11:
			cout << "\nПрограмма успешно завершена." << endl;
			Freemem(first);
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
	cout << "1 - Посмотреть текущее дерево." << endl;
	cout << "2 - Поиск узла с заданным значением." << endl;
	cout << "3 - Добавить узел" << endl;
	cout << "4 - Удалить узел" << endl;
	cout << "5 - Симметричный обход дерева, нахождение высоты дерева и количества узлов." << endl;
	cout << "6 - Определение каких чисел больше - положительных или отрицательных." << endl;
	cout << "11 - Удаление списка и выход и программы." << endl;
}

//создание корневого элемента
void CreateFirst() {
	first = new binary_tree;
	first->data = arr[0];
	first->left_el = nullptr;
	first->right_el = nullptr;
	first->back = nullptr;
	first->level = 0;
}

//заполнение дерева
binary_tree* Push(binary_tree* currentNode, int value)
{
	//найдено место для нового элемента
	if (currentNode == nullptr) {
		currentNode = new binary_tree;
		currentNode->data = value;
		currentNode->left_el = nullptr;
		currentNode->right_el = nullptr;
	}
	//новый элемент меньше того, кем занято место 
	else if (value < currentNode->data) {
		currentNode->left_el = Push(currentNode->left_el, value);
		currentNode->left_el->back = currentNode;
		currentNode->left_el->level = currentNode->left_el->back->level + 1;
	}
	//новый элемент больше того, кем занято место 
	else {
		currentNode->right_el = Push(currentNode->right_el, value);
		currentNode->right_el->back = currentNode;
		currentNode->right_el->level = currentNode->right_el->back->level + 1;
	}
	return(currentNode);
}

//печать дерева
void PrintTree(struct binary_tree* currentNode, int level)
{
	if (currentNode) {
		PrintTree(currentNode->right_el, level + 1);						// вывод правого поддерева
		for (int i = 0; i < level; i++) cout << "\t";
		cout << " " << currentNode->data << endl;							// вывод корня поддерева
		PrintTree(currentNode->left_el, level + 1);							// вывод левого поддерева
	}
}

//поиск элемента по ключу
binary_tree* Search(binary_tree* currentNode, int key)
{
	if (currentNode == nullptr) {
		cout << "...\n" << "Элемент не найден." << endl;
		return nullptr;
	}
	if (key == currentNode->data) {
		cout << currentNode->data << endl << "Элемент найден." << endl;
		return currentNode;
	}
	else if (key < currentNode->data){
		cout << currentNode->data << " --> ";
		Search(currentNode->left_el, key);
	}
	else {
		cout << currentNode->data << " --> ";
		Search(currentNode->right_el, key);
	}
}

//поиск минимального узла
binary_tree* SearchMin(binary_tree* currentNode) {
	if (currentNode->left_el == nullptr) return currentNode;
	else SearchMin(currentNode->left_el);
}

//измение уровня узла
void ChangeLvL(binary_tree* currentNode)
{
	if (currentNode) {
		ChangeLvL(currentNode->left_el);
		currentNode->level--;
		ChangeLvL(currentNode->right_el);
	}
}

//удаление узла
void RemoveNode(binary_tree* currentNode, int key)
{
	currentNode = Search(first, key);
	if (currentNode == nullptr) {
		cout << "Заданного узла не существует." << endl;
		return;
	}

	//Если удаляемый узел не имеет потомков
	if ((currentNode->left_el == nullptr) && (currentNode->right_el == nullptr)) {
		cout << "Узел " << currentNode->data << " не имеет потомков\nПроизводим удаление ..." << endl;

		//Если удаляется корневой элемент
		if (currentNode->back == nullptr) {
			delete first;
			return;
		}
		if (currentNode == currentNode->back->left_el) {
			currentNode->back->left_el = nullptr;
			Freemem(currentNode);
		}
		else {
			currentNode->back->right_el = nullptr;
			Freemem(currentNode);
		}
	}

	//Если удаляемый узел имеет потомка СЛЕВА
	else if ((currentNode->left_el != nullptr) && (currentNode->right_el == nullptr)) {
		cout << "Узел " << currentNode->data << " имеет левого потомка\nПроизводим удаление ..." << endl;

		//Если удаляется корневой элемент
		if (currentNode->back == nullptr) {
			first = currentNode->left_el;
			delete first->back;
			ChangeLvL(first);
			return;
		}

		if (currentNode == currentNode->back->left_el) {
			currentNode->back->left_el = currentNode->left_el;
			currentNode->left_el->back = currentNode->back;
		}
		else {
			currentNode->back->right_el = currentNode->left_el;
			currentNode->left_el->back = currentNode->back;
		}
		ChangeLvL(currentNode->left_el);

		delete currentNode;
	}

	//Если удаляемый узел имеет потомка СПРАВА
	else if ((currentNode->left_el == nullptr) && (currentNode->right_el != nullptr)) {
		cout << "Узел " << currentNode->data << " имеет правого потомка\nПроизводим удаление  ..." << endl;

		//Если удаляется корневой элемент
		if (currentNode->back == nullptr) {
			first = currentNode->right_el;
			delete first->back;
			ChangeLvL(first);
			return;
		}

		if (currentNode == currentNode->back->left_el) {
			currentNode->back->left_el = currentNode->right_el;
			currentNode->right_el->back = currentNode->back;
		}
		else {
			currentNode->back->right_el = currentNode->right_el;
			currentNode->right_el->back = currentNode->back;
		}

		ChangeLvL(currentNode->right_el);

		delete currentNode;
	}

	//Если узел имеет двух потомков
	else {
		cout << "Узел " << currentNode->data << " имеет двух потомков " << endl;
		cout << "Производим поиск элемента, который заменит его\n";
		minNode = SearchMin(currentNode->right_el);
		cout << "Узел " << currentNode->data << " будет земенен на узел " << minNode->data << endl;

		if (minNode->right_el != nullptr) {
			minNode->right_el->back = minNode->back;

			if (minNode == minNode->back->right_el) minNode->back->right_el = minNode->right_el;
			else minNode->back->left_el = minNode->right_el;

			ChangeLvL(minNode->right_el);
		}
		else if (minNode != currentNode->right_el) minNode->back->left_el = nullptr;
		else minNode->back->right_el = nullptr;

		if (currentNode->back == nullptr) {
			cout << "Удаляемый узел является вешиной" << endl;
			first = minNode;
			first->back = nullptr;
		}
		else {
			if (currentNode->back->left_el == currentNode) currentNode->back->left_el = minNode;
			else currentNode->back->right_el = minNode;
			minNode->back = currentNode->back;
		}

		minNode->left_el = currentNode->left_el;
		minNode->right_el = currentNode->right_el;
		minNode->level = currentNode->level;
		currentNode->left_el->back = minNode;
		if (currentNode->right_el != nullptr) currentNode->right_el->back = minNode;

		delete currentNode;
	}
}

//Симметричный обход
void InOrderTravers(binary_tree* currentNode, int& count, int& maxLvl)
{
	if (currentNode) {
		InOrderTravers(currentNode->left_el, count, maxLvl);
		cout << currentNode->data << " ";
		count++;
		if (currentNode->level > maxLvl) maxLvl = currentNode->level;
		InOrderTravers(currentNode->right_el, count, maxLvl);
	}
}

void Task2(binary_tree* currentNode, int& countPos, int& countNeg) {
	if (currentNode) {
		Task2(currentNode->left_el, countPos, countNeg);
		if (currentNode->data < 0) countNeg++;
		else countPos++;
		Task2(currentNode->right_el, countPos, countNeg);
	}
}

//очистка памяти
void Freemem(binary_tree* currentNode) {
	if (currentNode != nullptr) {
		Freemem(currentNode->left_el);
		Freemem(currentNode->right_el);
		delete currentNode;
	}
}