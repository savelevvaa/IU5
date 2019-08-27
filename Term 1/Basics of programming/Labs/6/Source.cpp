#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

typedef double(*PF)(double);
typedef double(*PI)(double, double);

struct I_print {	//данные для печати результатов интегрирования
	char *name;//название функции
	double i_sum;	//значение интегральной суммы
	PI i_toch;	//точное значение интеграла
	int n;	//число разбиений области интегрирования 
			//при котором достигнута требуемая точность
};

//--------------------------------------------------------------------------------------------Прототипы функций----------------------------------------------------------------------------------------------------
double f1(double x); double int1(double a, double b);
double f2(double x); double int2(double a, double b);
double f3(double x); double int3(double a, double b);
double f4(double x); double int4(double a, double b);
double IntRect(PF f, double a, double b, double eps, double &n);
double IntTrap(PF f, double a, double b, double eps, double &n);
void PrintTabl(I_print i_prn[], int k);
//**************************************************************************************************MAIN***********************************************************************************************************
void main()
{
	setlocale(LC_ALL, "ru");
	const short N = 4;
	double a = -1, b = 3, integral, n = 100;
	double eps = 0.01;
	char exit;
	I_print arr[N];
	PF arr1[N] = { f1, f2, f3, f4 };
	PI arr2[N] = { int1, int2, int3, int4 };
	const char arr3[N] = { "y=x ", "y=sin(22x)", "y=x^4 ", "y=arctg(x)" };
 

		for (eps; eps > 0.000001; eps /= 10)
		{
			for (int i = 0; i < N; i++)
			{
				arr[i].name = arr3[i];
				arr[i].i_toch = arr2[i];
				arr[i].n = 0;
				arr[i].i_sum = IntRect(arr1[i], a, b, eps, n);
			}
			cout << "Методом Прямоугольников: \n";
			PrintTabl(arr, N);
			for (int i = 0; i < N; i++)
			{
				arr[i].name = arr3[i];
				arr[i].i_toch = arr2[i];
				arr[i].n = 0;
				arr[i].i_sum = IntTrap(arr1[i], a, b, eps, n);
			}
			cout << "Методом Трапеций: \n";
			PrintTabl(arr, N);
		}
		cout << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << IntRect(arr1[i], a, b, eps, n) << endl;
		}
		cout << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << IntTrap(arr1[i], a, b, eps, n) << endl;
		}


	system("pause");
}
void PrintTabl(I_print i_prn[], int k)
{
	system("chcp 866>nul");
	const int m = 4;//число столбцов таблицы
	int wn[m] = { 12,18,18,10 };//ширина столбцов таблицы
	//char *title[m] = { "Function","Integral","IntSum","N " };
	int size[m];
	for (int i = 0; i < m; i++)
//		size[i] = strlen(title[i]);
	//шапка таблицы
	cout << char(218) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(194);
	cout << setw(wn[m - 1]) << char(191) << endl;

	cout << char(179);
	for (int j = 0; j < m; j++)
//		cout << setw((wn[j] - size[j]) / 2) << setfill(' ') << ' ' << title[j]
//		<< setw((wn[j] - size[j]) / 2) << char(179);
	cout << endl;
	for (int i = 0; i < k; i++)
	{//заполнение таблицы
		cout << char(195) << fixed;
		for (int j = 0; j < m - 1; j++)
			cout << setfill(char(196)) << setw(wn[j]) << char(197);

		cout << setw(wn[m - 1]) << char(180) << setfill(' ') << endl;

		cout << char(179) << setw((wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name << setw((wn[0] - strlen(i_prn[i].name)) / 2) << char(179);

		cout << setw(wn[1] - 1) << setprecision(10) << i_prn[i].i_toch << char(179)
			<< setw(wn[2] - 1) << i_prn[i].i_sum << char(179)
			<< setw(wn[3] - 1) << i_prn[i].n << char(179) << endl;
	}
	//низ таблицы
	cout << char(192) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(193);
	cout << setw(wn[m - 1]) << char(217) << endl;
	//восстановление первоначальных значений 
	cout << setprecision(6) << setfill(' ');
	system("chcp 1251>nul");
}

//------------------------------------------------------------------------------------------Метод Прямоугольников--------------------------------------------------------------------------------------------------
double IntRect(PF f, double a, double b, double eps, double &n)
{
	double S = 0, q, step, x;
	do
	{
		q = S;
		step = (b - a) / n;
		x = a;
		S = f(x)*step;
		for (int i = 0; i < n - 1; i++)
		{
			x += step;
			S += f(x)*step;
		}
	} while (abs(S - q) > eps);
	return S;
}
//---------------------------------------------------------------------------------------------Метод Трапеций------------------------------------------------------------------------------------------------------
double IntTrap(PF f, double a, double b, double eps, double &n)
{
	double S = 0, q, step, x;
	do
	{
		q = S;
		step = (b - a) / n;
		x = a;
		S = ((f(x) + f(x + step)) / 2)*step;
		for (int i = 0; i < n - 1; i++)
		{
			x += step;
			S += ((f(x) + f(x + step)) / 2)*step;
		}
	} while (abs(S - q) > eps);
	return S;
}
//-------------------------------------------------------------------------------------------------Функции---------------------------------------------------------------------------------------------------------

double f1(double x)
{
	return x;
}
double int1(double a, double b)
{
	return (b * b - a * a) / 2.0;
}
double f2(double x)
{
	return sin(22 * x);
}
double int2(double a, double b)
{
	return (cos(a*22.0) - cos(b*22.0)) / 22.0;
}
double f3(double x)
{
	return x * x * x * x;
}
double int3(double a, double b)
{
	return (b*b*b*b*b - a * a*a*a*a) / 5.0;
}
double f4(double x)
{
	return atan(x);
}
double int4(double a, double b)
{
	return b * atan(b) - a * atan(a) - (log(b*b + 1) - log(a*a + 1)) / 2.0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//
//
//cout << "Вычисление интегралов: " << endl;
//cout << "Табличные значения: " << endl;
//integral = (b * b - a * a) / 2.0;
//cout << "y = x : " << integral << endl;
//integral = (cos(a*22.0) - cos(b*22.0)) / 22.0;
//cout << "y = sin22x : " << integral << endl;
//integral = (b*b*b*b*b - a * a*a*a*a) / 5.0;
//cout << "y = x^4 : " << integral << endl;
//integral = b * atan(b) - a * atan(a) - (log(b*b + 1) - log(a*a + 1)) / 2.0;
//cout << "y = arcthx : " << integral << endl;
//cout << "Выбирите число разбиений интервала: ";
//cin >> n;