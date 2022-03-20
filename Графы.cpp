/*Реализация алгоритма Кускала и Флойда-Уоршела*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#define inf 50000
using namespace std;

const int N = 10;

int matrix[N][N] =
{
   {0, 4, inf, inf, inf, inf, 8, inf, inf, inf},
   {inf, 0, inf, 6, 5, inf, inf, inf, 2, inf},
   {6, inf, 0, inf, inf, inf, inf, 4, inf, inf},
   {inf, inf, inf, 0, inf, 2, inf, inf, inf, 1},
   {inf, inf, 4, 3, 0, inf, inf, inf, inf, inf},
   {inf, inf, inf, inf, inf, 0, inf, inf, 5, inf},
   {inf, inf, inf, inf, 3, inf, 0, inf, 1, inf},
   {inf, inf, inf, inf, inf, inf, 5, 0, inf, inf},
   {inf, inf, 1, inf, inf, inf, inf, inf, 0, 4},
   {inf, inf, inf, inf, 2, inf, inf, inf, inf, 0},
};


//Таблица
void Part_of_table_1();
void Part_of_table_2();
void Part_of_table_3();
void Part_of_table_4();

void Print_Pred(int** pred);                //печать матрицы pred
void Print_Matrix();         //печать матрицы смежности
void Print_Shortest(int** shortest);        //печать матрицы shortest
void Print_Route(int** pred);               //печать кратчайшего маршрута

void Floyd_Warshall_algorithm(int** pred, int** shortest);  //алгоритм Флойда-Уоршелла

void Change_Graph();        //изменение ориентированного на неорентированный граф

void Kruskal_algorithm();   //алгоритм Крускала

int main()
{
    system("color F0");

    //создание матриц pred и shortest
    int** shortest_Floyd_Warshall = new int* [N];
    for (int i = 0; i < N; i++) shortest_Floyd_Warshall[i] = new int[N];

    int** pred_Floyd_Warshall = new int* [N];
    for (int i = 0; i < N; i++) pred_Floyd_Warshall[i] = new int[N];

    //заполнение матриц pred и shortest
    for (int u = 0; u < N; u++)
    {
        for (int v = 0; v < N; v++)
        {
            shortest_Floyd_Warshall[u][v] = matrix[u][v];
            if ((matrix[u][v] < inf) && (matrix[u][v] != 0))
                pred_Floyd_Warshall[u][v] = u;
            else
                pred_Floyd_Warshall[u][v] = -1;
        }
    }

    cout << "\t\t\tAdjacency Matrix" << endl;
    Print_Matrix();

    cout << "________________________________________________________" << endl;
    Floyd_Warshall_algorithm(pred_Floyd_Warshall, shortest_Floyd_Warshall);
    Print_Route(pred_Floyd_Warshall);
    cout << "________________________________________________________" << endl;

    Change_Graph();           

    cout << "\t\tAdjacency matrix of the new graph" << endl;
    Print_Matrix();

    Kruskal_algorithm();

    for (int i = 0; i < N; i++) {
        delete[] shortest_Floyd_Warshall[i];  // удаляем массив
    }
    for (int i = 0; i < N; i++) {
        delete[] pred_Floyd_Warshall[i];  // удаляем массив
    }
}

void Print_Matrix()
{
    Part_of_table_1();
    Part_of_table_2();
    for (int u = 0; u < N; u++) {
        Part_of_table_3();
        cout << setfill(' ') << char(179) << setw(4) << u << char(179);
        for (int v = 0; v < N; v++) {
            if (matrix[u][v] == inf) cout << setw(4) << "OO" << char(179);
            else cout << setw(4) << matrix[u][v] << char(179);
        }
    }
    Part_of_table_4();
    cout << endl;
}

//Таблица
void Part_of_table_1() {
    cout << setfill(char(196))
        << char(218) << setw(5);            // "┌───────────"
    for (int i = 0; i < N; i++)
        cout << char(194) << setw(5);       // "┬───────────"
    cout << char(191) << endl;              // "┐"
};
void Part_of_table_2() {
    cout << setfill(' ');
    cout << char(179) << setw(4) << " ";    // "│  "
    for (int i = 0; i < 10; i++)
        cout << char(179) << setw(4) << i;  // "│ 1"
    cout << char(179);                      // "│"

}
void Part_of_table_3() {
    cout << endl << setfill(char(196))
        << char(195) << setw(5);
    for (int i = 0; i < N; i++)
        cout << char(197) << setw(5);       // "├───────────"
    cout << char(180) << endl;              // "┤"
}
void Part_of_table_4() {
    cout << endl << setfill(char(196))
        << char(192) << setw(5);            // "└───────────"
    for (int i = 0; i < N; i++)
        cout << char(193) << setw(5);       // "┴───────────"
    cout << char(217) << endl;              // "┘"
}

void Print_Pred(int** pred)
{
    cout << "\t\t\tPred" << endl;
    Part_of_table_1();
    Part_of_table_2();
    for (int u = 0; u < N; u++) {
        Part_of_table_3();
        cout << setfill(' ') << char(179) << setw(4) << u << char(179);
        for (int v = 0; v < N; v++) {
            if (pred[u][v] >= 0) cout << setw(4) << pred[u][v] << char(179);
            else cout << setw(4) << "NULL" << char(179);
        }
    }
    Part_of_table_4();
    cout << endl;
}

void Print_Shortest(int** shortest)
{
    cout << "\t\t\tShortest" << endl;
    Part_of_table_1();
    Part_of_table_2();
    for (int u = 0; u < N; u++) {
        Part_of_table_3();
        cout << setfill(' ') << char(179) << setw(4) << u << char(179);
        for (int v = 0; v < N; v++) {
            if (shortest[u][v] == inf) cout << setw(4) << "OO" << char(179);
            else cout << setw(4) << shortest[u][v] << char(179);
        }
    }
    Part_of_table_4();
    cout << endl;
}

//печать кратчайшего маршрута
void Print_Route(int** pred) {
    cout << endl << endl;
    int finish, start;
    int temp;
    for (start = 0; start < N; start++) {
        cout << "Route from the top: " << start << endl;
        for (finish = 0; finish < N; finish++) {
            temp = finish;
            //если начало совпадает с концом:
            if (start == finish) {
                cout << "\tRoute in " << finish << " is 0"<< endl;
                continue;
            }
            if (pred[start][temp] >= 0) {
                cout <<"\t" << finish;
                while (temp != start) {                         //проход по матрице pred
                    cout << " <- " << pred[start][temp];    // для поиска предшевствущих вершин
                    temp = pred[start][temp];
                }
                cout << endl;
            }
            //если путь отсутствует
            else cout << "There is no route to top " << finish << endl;
        }
        cout << endl << endl;
    }
}

//алгоритм Флойда-Уоршелла
void Floyd_Warshall_algorithm(int** pred, int** shortest)
{
    cout << "Data at the beginning of program execution:" << endl << endl;
    Print_Shortest(shortest);
    Print_Pred(pred);
    cout << "________________________________________________________" << endl;

    for (int x = 0; x < N; x++)
    {
        for (int u = 0; u < N; u++)
        {
            for (int v = 0; v < N; v++)
            {
                if (shortest[u][x] + shortest[x][v] < shortest[u][v])
                {
                    shortest[u][v] = shortest[u][x] + shortest[x][v];
                    pred[u][v] = pred[x][v];
                }
            }
        }
        cout << "\t\t\tx = " << x << endl;
        Print_Shortest(shortest);
        Print_Pred(pred);
        cout << "_._._._._._._._._._._._._._._._._._._._._._._._._._._._._" << endl;
    }

    cout << "________________________________________________________" << endl;
    cout << "Data at the end of program execution:" << endl << endl;
    Print_Shortest(shortest);
    Print_Pred(pred);
    cout << "________________________________________________________";
}

//изменение ориентированного на неорентированный граф
void Change_Graph() {
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            if ((matrix[u][v] != matrix[v][u]) && (matrix[v][u] != inf)) matrix[u][v] = matrix[v][u];
        }
    }
}

//алгоритм Крускала
void Kruskal_algorithm() {
    int count_of_route = 0;
    int k = 0;
    int Sum = 0;

    //счетчик числа ребер
    for (int u = 0; u < N; u++) {
        for (int v = u + 1; v < N; v++) {
            if (matrix[u][v] != inf) {
                count_of_route++;
            }
        }
    }

    vector<int> tree_id(N);         //Принадлежность вершины тому или иному поддереву
    for (int i = 0; i < N; ++i)
        tree_id[i] = i;

    vector < pair<int, int> > result;           //массив ребер, принадлежащих остовному дереву графа

    vector < pair < int, pair<int, int> > > priority_queue(count_of_route);       //массив, хранит информацию о весе
    for (int u = 0; u < N; u++) {                                                 // и вершинах, принадлежащих ребру
        for (int v = u + 1; v < N; v++) {
            if (matrix[u][v] != inf) {
                priority_queue[k].first = matrix[u][v];
                priority_queue[k].second.first = u;
                priority_queue[k].second.second = v;
                k++;
            }
        }
    }
    sort(priority_queue.begin(), priority_queue.end());           //сортировка рёбер по неубыванию

    for (int i = 0; i < priority_queue.size(); i++)
    {
        int a = priority_queue[i].second.first;
        int b = priority_queue[i].second.second;
        int l = priority_queue[i].first;

        if (tree_id[a] != tree_id[b])                               //принадлежат ли концы ребра разным деревьям
        {
            result.push_back(make_pair(a, b));

            int old_id = tree_id[b], new_id = tree_id[a];
            for (int j = 0; j < N; ++j)
                if (tree_id[j] == old_id) 
                    tree_id[j] = new_id;
        }
    }

    cout << "\n\n\n\t\t\tKruskal_algorithm" << endl;
    cout << "Route\tweight:" << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i].first << "--" << result[i].second << "\t " << matrix[result[i].first][result[i].second] << endl;
        Sum += matrix[result[i].first][result[i].second];
    }
    cout << "\nMinimum weight: " << Sum << endl;
}