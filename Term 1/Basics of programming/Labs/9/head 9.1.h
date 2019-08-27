#include <iostream>
#include <iomanip>
using namespace std;

//double **Reverse(double **Matr, int n)
//{
//	double a, b, c;
//	double *str = new double[2 * n];		//строка для обнуления
//
//	// Создание единичной матрици
//	double **Matr_Ed = new double *[n];
//	for (int i = 0; i < n; i++)
//		Matr_Ed[i] = new double[n];
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//		{
//			if (i == j) Matr_Ed[i][j] = 1;
//			else Matr_Ed[i][j] = 0;
//		}
//
//	// Создание вспомогательной матрици
//	double **Matr_Rashir = new double *[n];
//	for (int i = 0; i < n; i++)
//		Matr_Rashir[i] = new double[2 * n];
//
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < (2 * n); j++)
//		{
//			if (j < n)
//				Matr_Rashir[i][j] = Matr[i][j];
//			else Matr_Rashir[i][j] = Matr_Ed[i][j - n];
//		}
//
//	// Прямой ход
//	for (int i = 0; i < n; i++)                          //в конце цикла получается верхняя треугольная матрица
//	{
//		if (Matr_Rashir[i][i] == 0)
//		{
//			for (int j = i + 1; j < n; j++)
//			{
//				if (Matr_Rashir[j][i] != 0)
//				{
//					for (int k = 0; k < n * 2; k++)
//					{
//						c = Matr_Rashir[j][k];
//						Matr_Rashir[j][k] = Matr_Rashir[i][k];
//						Matr_Rashir[i][k] = c;
//					}
//					break;
//				}
//			}
//		}
//		for (int j = i; j < n; j++)                      //тут получается строка(k-атая) с диагональным элементом= 1 и элементами под ним(обнуляемые)= 0
//		{
//			if (j == i)                                 //Сохраняем строку(k-тую) чтоб потом с помощию неё обнулять элементы под диагональными единийами
//			{
//				for (int k = 0; k < 2 * n; k++)
//					str[k] = Matr_Rashir[j][k];
//			}
//
//			for (int k = i; k < 2 * n; k++)                //в конце цикла преобразовывается строка
//			{
//				if (j == i)
//				{
//					if (k == i) a = Matr_Rashir[i][i];      //сохраняем значение первого элемента i-той строки
//					Matr_Rashir[j][k] = Matr_Rashir[j][k] / a;  //делим каждый j-тый элемент i-той строки на значение первого элемента для получения единиц на диагонали
//				}
//				else {
//					if (k == i) b = Matr_Rashir[j][k];
//					Matr_Rashir[j][k] = Matr_Rashir[j][k] - str[k] * b / a;  //обнуляем элементы под диагональными единийами
//				}
//			}
//		}
//	}
//	// Обратный ход(прямой ход, только зануляем павые верхние элементы)
//	for (int i = n - 1; i >= 0; i--)
//		for (int j = i; j >= 0; j--)
//		{
//			if (j == i)
//			{
//				for (int k = 0; k < 2 * n; k++)
//					str[k] = Matr_Rashir[j][k];
//			}
//
//			for (int k = i; k < 2 * n; k++)
//			{
//				if (j == i)
//				{
//					if (k == i) a = Matr_Rashir[i][i];
//					Matr_Rashir[i][k] = Matr_Rashir[j][k] / a;
//				}
//				else {
//					if (k == i) b = Matr_Rashir[j][k];
//					Matr_Rashir[i][k] = Matr_Rashir[j][k] - str[k] * b / a;
//				}
//			}
//		}
//
//	double **mat_ob = new double*[n];
//	for (int i = 0; i < n; i++)
//		mat_ob[i] = new double[n];
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//			mat_ob[i][j] = Matr_Rashir[i][j + n];
//
//	return mat_ob;
//}




double** Reverse(double** Matr, int n)
{
	double a, b, c;
	double *arr = new double[2 * n];

	double **Matr_Ed = new double *[n];				//ЕДЕНИЧНАЯ
	for (int i = 0; i < n; i++)
		Matr_Ed[i] = new double[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j) Matr_Ed[i][j] = 1;
			else Matr_Ed[i][j] = 0;
		}

	double **Matr_Rashir = new double *[n];			//РАСШИРЕННАЯ (ВСПОМОГАТЕЛЬНАЯ)
	for (int i = 0; i < n; i++)
		Matr_Rashir[i] = new double[2 * n];

	for (int i = 0; i < n; i++)						//Заполнение расширенной матрицы
		for (int j = 0; j < (2 * n); j++)
		{
			if (j < n)
				Matr_Rashir[i][j] = Matr[i][j];
			else Matr_Rashir[i][j] = Matr_Ed[i][j - n];
		}

	for (int i = 0; i < n; i++)                         //ПРЯМОЙ ХОД (в конце получается верхнаяя треугольная матрица) 
	{
		if (Matr_Rashir[i][i] == 0)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (Matr_Rashir[j][i] != 0)
				{
					for (int k = 0; k < n * 2; k++)
					{
						c = Matr_Rashir[j][k];
						Matr_Rashir[j][k] = Matr_Rashir[i][k];
						Matr_Rashir[i][k] = c;
					}
					break;
				}
			}
		}
		for (int j = i; j < n; j++)                      //тут получается строка (i-атая) с диагональным элементом= 1 и элементами под ним(обнуляемые)= 0
		{
			if (j == i)                                 //Сохраняем строку (i-тую) для обнуления элементов под главной деагональю (с еденицами)
			{
				for (int k = 0; k < 2 * n; k++)
					arr[k] = Matr_Rashir[j][k];
			}

			for (int k = i; k < 2 * n; k++)                //С каждым i-ым проходом (главного for) тут преобразовывается строка
			{
				if (j == i)
				{
					if (k == i)
						a = Matr_Rashir[i][i];      //сохраняем значение первого элемента j-той строки
					Matr_Rashir[j][k] = Matr_Rashir[j][k] / a;  //делим каждый k-тый элемент j-той строки на значение первого элемента для получения единиц на главной диагонали
				}
				else
				{
					if (k == i)
						b = Matr_Rashir[j][k];
					Matr_Rashir[j][k] = Matr_Rashir[j][k] - arr[k] * b / a;  //обнуляем элементы под главной диагональю 
				}
			}
		}
	}

	for (int i = n - 1; i >= 0; i--)					//ОБРАТНЫЙ ХОД (Обнуляем правые верхние элементы)
		for (int j = i; j >= 0; j--)
		{
			if (j == i)
			{
				for (int k = 0; k < 2 * n; k++)
					arr[k] = Matr_Rashir[j][k];
			}

			for (int k = i; k < 2 * n; k++)
			{
				if (j == i)
				{
					if (k == i) a = Matr_Rashir[i][i];
					Matr_Rashir[j][k] = Matr_Rashir[j][k] / a;
				}
				else {
					if (k == i) b = Matr_Rashir[j][k];
					Matr_Rashir[j][k] = Matr_Rashir[j][k] - arr[k] * b / a;
				}
			}
		}
	double **Reverse_Matr = new double*[n];
	for (int i = 0; i < n; i++)
		Reverse_Matr[i] = new double[n];
	for (int i = 0; i < n; i++)				//вынимаем обратную матрицу в из преобразованного в новый массив
		for (int j = 0; j < n; j++)
			Reverse_Matr[i][j] = Matr_Rashir[i][j + n];

	return Reverse_Matr;

	
}

void Proverka(double **Matr1, double **Matr2, int n)
{
	double s;
	double **Matr_Ed = new double *[n];
	for (int i = 0; i < n; i++)
		Matr_Ed[i] = new double[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			s = 0;
			for (int k = 0; k < n; k++)
				s = s + Matr1[i][k] * Matr2[k][j];							//Умножаем "строку на столбец"
			if (i == j)Matr_Ed[i][j] = 1; else               
				Matr_Ed[i][j] = s;

		}

	}

	cout << " Умножение обратной на исходную: \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(8) << fixed << setprecision(2) << abs(Matr_Ed[i][j]) << "   ";
		cout << "\n";
	}
}

void Korny(double **Matr1, double *Matr2, int n)
{
	double s;
	double *Korni = new double[n];
	for (int i = 0; i < n; i++)
	{
		s = 0;
		for (int j = 0; j < n; j++)
		{
			s = s + Matr1[i][j] * Matr2[j];
		}
		Korni[i] = s;
	}

	cout << "\nКорни СЛАУ:\n";
	for (int i = 0; i < n; i++)
		cout << "x" << i + 1 << " = " << Korni[i] << "\n";
}


void SLAU()
{
	int n;
	cout << "Введите количество уравнений в системе\n:> ";
	cin >> n;
	double **Matr_Koef = new double *[n];					//МАТРИЦА КОЕФИЦИЕНТОВ
	for (int i = 0; i < n; i++)
		Matr_Koef[i] = new double[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Введите коэффициенты " << i + 1 << "-го уравнения\n(" << n << " шт.):> ";
		for (int j = 0; j < n; j++)
			cin >> Matr_Koef[i][j];
	}
	double **Matr_Koef_Reverse = Reverse(Matr_Koef, n);		//Находим обратную матрицу коефициентов
	double *Svobodnye = new double[n];						//МАССИВ СВОБОДНЫХ ЧЛЕНОВ
	cout << "Введите свободные члены уравнений\n:> ";
	for (int j = 0; j < n; j++)
		cin >> Svobodnye[j];
	Korny(Matr_Koef_Reverse, Svobodnye, n);
}