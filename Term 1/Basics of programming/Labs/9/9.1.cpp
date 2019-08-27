#include <iostream>
#include <iomanip>
#include "head 9.1.h"

using namespace std;

int menu()
{
	int choice;
	cout << "Меню:\n\n";
	cout << "(1) Нахождение обратной матрицы\n(2) СЛАУ\n(3) Завершить\n:> ";
	cin >> choice;
	return choice;
}
void printM(double**, int);


int main()
{
	setlocale(LC_ALL, "ru");
	cout << "\t\t\t\t== Матрици и СЛАУ ==\n";

	while (true)
	{
		switch (menu())
		{
		case 1:
		{
			int n;
			cout << "////////////////////////////////////////////////////////////////////////////////";
			cout << "(1) Нахождение обратной матрицы\n\n";
			cout << "Введите размер матрици\n:>  ";
			cin >> n;

			double **Matr = new double *[n];
			for (int i = 0; i < n; i++)
				Matr[i] = new double[n];

			cout << "\nВведите элементы матрици\n:> ";
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					cin >> Matr[i][j];
			cout << " Матрица: \n";
			printM(Matr, n);

			double **Matr_Reverse = Reverse(Matr, n);
			cout << " Обратная матрица: \n";
			printM(Matr_Reverse, n);

			Proverka(Matr, Matr_Reverse, n);
			cout << "\n////////////////////////////////////////////////////////////////////////////////";
			break;
		}
		case 2:
		{
			cout << "////////////////////////////////////////////////////////////////////////////////";
			cout << "(2) Решение системы уравнений\n\n";
			SLAU();
			cout << "\n////////////////////////////////////////////////////////////////////////////////";
			break;
		}
		case 3:
			system("pause"); return false;
		}
	}
//	cout << "Введите размер матрици ";
//	cin >> n;
//
//	double **Matr = new double *[n];
//	for (int i = 0; i < n; i++)
//		Matr[i] = new double[n];
//
//
//	cout << "\nВведите элементы матрици\n";
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//			cin >> Matr[i][j];
//
//
//	double **Matr_Reverse = Reverse(Matr, n);
//	cout << " Обратная матрица: \n";
//	printM(Matr_Reverse, n);
//	
//	Proverka(Matr, Matr_Reverse, n);                     //проверка умножением
//
////-------------------------------------------------------------------------ЧАСТЬ II---------------------------------------------------------------------
////------------------------------------------------------------------------Решение СЛАУ------------------------------------------------------------------
//	cout << "\nРешение системы уравнений.\n";
//	SLAU();
	system("Pause");
	return 0;
}

void printM(double** matr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(5) << fixed << setprecision(1) << matr[i][j] << "   ";
		cout << "\n";
	}
}

//double **Reverse(double **mat, int n)
//{
//	double a, b, c;
//	double *mas = new double[2 * n];
//
//	// Создание единичной матрици
//	double **mat_ed = new double *[n];
//	for (int i = 0; i < n; i++)
//		mat_ed[i] = new double[n];
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//		{
//			if (i == j) mat_ed[i][j] = 1;
//			else mat_ed[i][j] = 0;
//		}
//
//	// Создание вспомогательной матрици
//	double **mat_help = new double *[n];
//	for (int i = 0; i < n; i++)
//		mat_help[i] = new double[2 * n];
//
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < (2 * n); j++)
//		{
//			if (j < n)
//				mat_help[i][j] = mat[i][j];
//			else mat_help[i][j] = mat_ed[i][j - n];
//		}
//
//	// Прямой ход
//	for (int k = 0; k < n; k++)                          //в конце цикла получается верхняя треугольная матрица
//	{
//		if (mat_help[k][k] == 0)
//		{
//			for (int i = k + 1; i < n; i++)
//			{
//				if (mat_help[i][k] != 0)
//				{
//					for (int j = 0; j < n * 2; j++)
//					{
//						c = mat_help[i][j];
//						mat_help[i][j] = mat_help[k][j];
//						mat_help[k][j] = c;
//					}
//					break;
//				}
//			}
//		}
//		for (int i = k; i < n; i++)                      //тут получается строка(k-атая) с диагональным элементом= 1 и элементами под ним(обнуляемые)= 0
//		{
//			if (i == k)                                 //Сохраняем строку(k-тую) чтоб потом с помощию неё обнулять элементы под диагональными единийами
//			{
//				for (int j = 0; j < 2 * n; j++)
//					mas[j] = mat_help[i][j];
//			}
//
//			for (int j = k; j < 2 * n; j++)                //в конце цикла преобразовывается строка
//			{
//				if (i == k)
//				{
//					if (j == k) a = mat_help[k][k];      //сохраняем значение первого элемента i-той строки
//					mat_help[i][j] = mat_help[i][j] / a;  //делим каждый j-тый элемент i-той строки на значение первого элемента для получения единиц на диагонали
//				}
//				else {
//					if (j == k) b = mat_help[i][j];
//					mat_help[i][j] = mat_help[i][j] - mas[j] * b / a;  //обнуляем элементы под диагональными единийами
//				}
//			}
//		}
//	}
//	// Обратный ход(прямой ход, только зануляем павые верхние элементы)
//	for (int k = n - 1; k >= 0; k--)
//		for (int i = k; i >= 0; i--)
//		{
//			if (i == k)
//			{
//				for (int j = 0; j < 2 * n; j++)
//					mas[j] = mat_help[i][j];
//			}
//
//			for (int j = k; j < 2 * n; j++)
//			{
//				if (i == k)
//				{
//					if (j == k) a = mat_help[k][k];
//					mat_help[i][j] = mat_help[i][j] / a;
//				}
//				else {
//					if (j == k) b = mat_help[i][j];
//					mat_help[i][j] = mat_help[i][j] - mas[j] * b / a;
//				}
//			}
//		}
//
//	double **mat_ob = new double*[n];
//	for (int i = 0; i < n; i++)
//		mat_ob[i] = new double[n];
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//			mat_ob[i][j] = mat_help[i][j + n];
//
//	return mat_ob;
//}
//
//void Proverka(double **mat1, double **mat2, int n)
//{
//	double s;
//	double **mat = new double *[n];
//	for (int i = 0; i < n; i++)
//		mat[i] = new double[n];
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			s = 0;
//			for (int k = 0; k < n; k++)
//				s = s + mat1[i][k] * mat2[k][j];
//			if (i == j)mat[i][j] = 1; else                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//				mat[i][j] = s;
//
//		}
//
//	}
//
//	cout << " Умножение обратной на исходную: \n";
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//			cout << setw(8) << fixed << setprecision(3) << abs(mat[i][j]) << "   ";
//		cout << "\n";
//	}
//}
//
//void Proverka(double **mat1, double *mat2, int n)
//{
//	double s;
//	double *mat = new double[n];
//	for (int i = 0; i < n; i++)
//	{
//		s = 0;
//		for (int j = 0; j < n; j++)
//		{
//			s = s + mat1[i][j] * mat2[j];
//		}
//		mat[i] = s;
//	}
//
//	cout << "\nРезультат:\n";
//	for (int i = 0; i < n; i++)
//		cout << "x" << i + 1 << " = " << mat[i] << "\n";
//}
//
//
//void SLAU()
//{
//	int n;
//	cout << "Введите количество уравнений в системе - ";
//	cin >> n;
//	double **mat = new double *[n];
//	for (int i = 0; i < n; i++)
//		mat[i] = new double[n];
//
//	for (int i = 0; i < n; i++)
//	{
//		cout << "Введите коэффициенты уравнения: " << i + 1 << "\n";
//		for (int j = 0; j < n; j++)
//			cin >> mat[i][j];
//	}
//	double **mat_ob = Reverse(mat, n);
//	double *svob = new double[n];
//	cout << "Введите свободные члены уравнений:\n";
//	for (int j = 0; j < n; j++)
//		cin >> svob[j];
//	Proverka(mat_ob, svob, n);
//}