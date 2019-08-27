#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

typedef double(*PF)(double);
typedef double(*PI)(double, double);

struct I_print {	//данные для печати результатов интегрирования
	char *name;//название функции
	double i_sum;	//значение интегральной суммы
	double i_toch;	//точное значение интеграла
	int n;	//число разбиений области интегрирования 
			//при котором достигнута требуемая точность
};

//--------------------------------------------------------------------------------------------Прототипы функций----------------------------------------------------------------------------------------------------
double f1(double x); double int1(double a, double b);
double f2(double x); double int2(double a, double b);
double f3(double x); double int3(double a, double b);
double f4(double x); double int4(double a, double b);
double IntRect(PF f, double a, double b, double eps, int &n);
double IntTrap(PF f, double a, double b, double eps, int &n);
void PrintTabl(I_print i_prn[], int k);
//**************************************************************************************************MAIN***********************************************************************************************************
int main()
{
	system("chcp 1251>nul");
	const short N = 4;
	double a, b;
	int n;
	double eps = 0.00001;
	double Eps[5] = {0.01, 0.001, 0.0001, 0.00001, 0.000001};
	char exit;
	I_print arr[N];
	const PF arr1[N] = { f1, f2, f3, f4 };
	const PI arr2[N] = { int1, int2, int3, int4 };
	char *arr3[N] = { "y=x ", "y=sin(22x)", "y=x^4 ", "y=arctg(x)" };
	do
	{
		cout << "Введите интервал (a , b): ";
		cin >> a >> b;
		if (a > b) 
		{
				cout << "а должно быть больше b, повторите ввод\n";
				cout << endl;
		}
	}
	while(a > b);
 
	for(int i = 0; i < 5; i++)
	{
		eps = Eps[i];
		cout << "Заданныя точность " << eps << endl;
			for (int i = 0; i < N; i++)
			{
				arr[i].n = 0;
				arr[i].name = arr3[i];
				arr[i].i_toch = arr2[i](a,b);
				arr[i].i_sum = IntRect(arr1[i], a, b, eps, arr[i].n);
			}
			cout << "Методом Прямоугольников: \n";
			PrintTabl(arr, N);
			for (int i = 0; i < N; i++)
			{
				arr[i].n = 0;
				arr[i].name = arr3[i];
				arr[i].i_toch = arr2[i](a,b);
				arr[i].i_sum = IntTrap(arr1[i], a, b, eps, arr[i].n);
			}
			cout << "Методом Трапеций: \n";
			PrintTabl(arr, N);
			cout << endl;
	}

	system("pause");
	return 0;
}
void PrintTabl(I_print i_prn[], int k)
{
	system("chcp 866>nul");
	const int m = 4;//число столбцов таблицы
	int wn[m] = { 12,18,18,10 };//ширина столбцов таблицы
	char *title[m] = { "Function","Integral","Square","n " };
	int size[m];
	for (int i = 0; i < m; i++)
		size[i] = strlen(title[i]);
	//шапка таблицы
	cout << char(218) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(194);
	cout << setw(wn[m - 1]) << char(191) << endl;

	cout << char(179);
	for (int j = 0; j < m; j++)		cout << setw((wn[j] - size[j]) / 2) << setfill(' ') << ' ' << title[j]
		<< setw((wn[j] - size[j]) / 2) << char(179);
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
double IntRect(PF f, double a, double b, double eps, int &n)
{
	double S = f(a)*(b-a), q, step, x;
	n = 1;
	do
	{
		q = S;
		S = 0;
		step = (b - a) / n;
		for (int i = 1; i <= n; i++)
		{
			S += f(a + step * (i - 0.5));
		}
		S *= step;
		n *= 2;
	} while (abs(S - q)/3 >= eps);
	int d = n;
	return S;
}
//---------------------------------------------------------------------------------------------Метод Трапеций------------------------------------------------------------------------------------------------------
double IntTrap(PF f, double a, double b, double eps, int &n)
{
	double S = 100, q, step;
	n = 1;
	do
	{
		q = S;
		S = 0;
		step = (b - a) / n;

		for (int i = 0; i < n; i++)
		{
			S += (f(a + step*i) + f(a + step * (i + 1))) / 2;
		}
		S *= step;
		n *= 2;
	} while (abs(S - q)/3 > eps);
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

