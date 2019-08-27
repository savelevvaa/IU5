#include <iostream>
#include <iomanip>
using namespace std;

int fact(int a)																				//Факториал рекурсия
{
	if (a == 0)
		return 1;
	if (a == 1)
		return 1;
	return a * (a - 1);
}

template <class T1>  void fill1(T1 **arr, int a, int b, int x)						//Заполнение arr[rows][cols]
{
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (j > i)//выше главной диагонали
				arr[i][j] = pow(x, i) / pow(fact(x), i);
			if (j < i)//ниже главной диагонали
				arr[i][j] = pow(-x, i) / pow(fact(x), i);
		}
		arr[i][i] = 1;
	}
}

template <class T1>  void fill2(T1 **arr, int a, int b)								//заполнеие B[10][10]
{
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			arr[i][j] = (i * 10) + j;
		}

	}
}

template <class T1> void print1(T1 **arr, int a, int b, int eps, int flag)			//Вывод arr[rows][cols]
{
	int w;	//определение ширины столбца матрицы
	if(flag == 1)
		w = eps + 8;
	if (flag == 2)
		w = eps + 4;
	if(flag == 0)
		w = 4;
	int bring, take = 0;//переменные для запоминания i и j при переносе матрицы
	do 
	{
		bring = take;
		take += 75 / w; //кол-во столбцов 
		cout << endl;
		cout << setw(5) << "№  ";
		for (int j = bring; (j < take) && (j < b); j++) cout << setw(w) << (j + 1);
		cout << "\n_______________________________________________________________________________\n";
		for (int i = 0; i < a; i++)
		{
			cout << setw(3) << i + 1 << " |";
			for (int j = bring; (j < take) && (j < b); j++)
			{
				if (flag == 1)//условие научного вывода
					cout << scientific << setprecision(eps) << setw(w) << arr[i][j];
				if (flag == 2)//условие фиксированного вывода с учетом точности
						cout << fixed << setprecision(eps) << setw(w) << arr[i][j];
				if (flag == 0)
				{
					cout.setf(ios::dec);
					cout << setw(w) << arr[i][j];
				}
			}
			cout << "\n";
		}
		cout << "\n";
	} while (take < b);
}
template <class T1, class T2> void print2(T1 arr[][10], T2 a)								//Вывод B[10][10]
{
	int w = 4; //ширины столбца
	int bring, take = 0;//переменные для запоминания i и j при переносе матрицы
	
	do 
	{
		bring = take;
		take += 75 / w; //кол-во столбцов
		cout << endl;
		cout << setw(5) << "№  ";
		for (int j = bring; (j < take) && (j < a); j++) cout << setw(w) << (j + 1);
		cout << "\n_______________________________________________________________________________\n";
		for (int i = 0; i < a; i++)
		{
			cout << setw(3) << i + 1 << " |";
			for (int j = bring; (j < take) && (j < a); j++)
			{
				
				cout.setf(ios::dec);
				cout << setw(w) << arr[i][j];
			}
			cout << "\n";
		}
		cout << "\n";
	} while (take < a);
}
