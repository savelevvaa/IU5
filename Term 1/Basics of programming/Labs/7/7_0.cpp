#include <iostream>
#include <iomanip>
#include "head.h"
using namespace std;

void menu(int &choice1, int &choice2) //меню взаимодействия 
{
	cout << "\t(1) Произвольная матрица. " << endl;
	cout << "\t(2) Квадратная матрица. " << endl;
	cout << "\t(3) Матраца вида B[10][10]. " << endl;
	cout << "\t(4) Завершить. " << endl << "\t: ";
	cin >> choice1;
	switch (choice1)
	{
	case 1:
	{
		cout << "\t(1) Вывод в научном стиле. " << endl;
		cout << "\t(2) Вывод в фиксированном стиле. " << endl << "\t: ";
		cin >> choice2;
		break;
	}
	case 2:
	{
		cout << "\t(1) Вывод в научном стиле. " << endl;
		cout << "\t(2) Вывод в фиксированном стиле. " << endl << "\t: ";
		cin >> choice2;
		break;

	}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	char exit = 'n';
	int i = 1;
	cout << "\t\t\tОбработка и печать числовой матрицы." << endl << endl;
	cout << "////////////////////////////////////////////////////////////////////////////////" << endl;
	do
	{
		int rows = 0, cols = 0, eps = 0, x = 1, choice1 = 0, choice2 = 0;
		cout << i << ")" << endl;
		menu(choice1, choice2); //вызов меню

		switch (choice1) 
		{
		case 1://произвольная матрица
		{
			cout << "  Введите кол-во строк(rows) и столбцов(cols): ";
			cin >> rows >> cols;
			double **arr = new double *[rows];

			for (int i = 0; i < rows; i++)
			{
				arr[i] = new double[cols];
			}
			cout << "  Введите точность вывода: ";
			cin >> eps;
			fill1(arr, rows, cols, x);
			print1(arr, rows, cols, eps, choice2);
			if(rows > cols)
			{
				for (int i = 0; i < cols; i++)
				{
					delete arr[i];
				}
				delete[] arr;
			}
			if(rows < cols)
			{
				for (int i = 0; i < rows; i++)
				{
					delete[] arr[i];
				}
				delete[] arr;
			}
			break;
		}
		case 2://квадратная матрица
		{
			cout << "  Введите N (rows=cols): ";
			cin >> rows;
			cols = rows;
			double **arr = new double *[rows];

			for (int i = 0; i < cols; i++)
			{
				arr[i] = new double[cols];
			}
			cout << "  Введите точность вывода: ";
			cin >> eps;
			fill1(arr, rows, cols, x);
			print1(arr, rows, cols, eps, choice2);
			for (int i = 0; i < rows; i++)
			{
				delete arr[i];
			}
			delete[] arr;
			break;
		}
		case 3://массив B[][]
		{
			choice2 = 0;
			int rows1 = 10, cols1 = 10;
			int B[10][10];
			int **b = new int*[10];
			for(int i = 0; i < 10; i++)
				b[i] = B[i];
			fill2(b, rows1, cols1);
			print1(b, rows1, cols1, eps, choice2);
			cout << endl;
			cout << B << "  " << B[0] << "  " << B[2] << endl;
			cout << B[0][0] << "  " << **B << "  " << *B[0] << endl;
			cout << *(*(B + 1)) << "  " << *B[1] << endl;
			cout << *(B[0] + 1) << "  " << *(*B + 1) << endl;
			cout << B[0][20] << "  " << *(B[0] + 20) << "  " << *B[2] << endl << endl;
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
				{
					B[i][j] = NULL;
				}
			break;
		}
		case 4://выход
		{
			exit = 'y';
			break;
		}
		}
		i++;
		cout << "////////////////////////////////////////////////////////////////////////////////" << endl;
	} while (exit != 'y');

	system("pause");
	return 0;
}
