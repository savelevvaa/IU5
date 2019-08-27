#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	int j = 1, l = 0;
	char exit1, exit2, koef;
	double f1, f2;
	cout << "Найти корень уравнения x-cos(x)\n 'Методом простой итерациии'\n 'Методом Ньютона'\n 'Методом половинного деления' \n";
	do {
		int i, k;
		double x, a, b, c, eps;
		cout << " \n" << j << "." << l << ")\n" << " \n";
		cout << "Введите точность вычислений: ";
		cin >> eps;
		cout << "Введите границы на оси Ox (a,b): ";
		cin >> a >> b;
		cout << " \n";
		if (a == b)														//проверяем интервал
		{
			cout << "a не должно быть равно b, начните заного!";
			system("pause");
			return 0;
		}
		if (a > b)
		{
			cout << "a должно быть меньше b, начните заного!";
			system("pause");
			return 0;
		}																//проверяем интервал *

		i = 0;															//метод Ньютона
		x = a;
		f1 = a - cos(a);
		f2 = b - cos(b);
		if (((f1*f2) < 0))
		{
		do
		{
			x = x - ((x - cos(x)) / (sin(x) + 1));
			i++;
		} while (abs(x - cos(x)));
		cout << "(*) Метод Ньютона: \n" << " \n";
		cout << "    Корень: " << setprecision(10) << x << endl;
		cout << "    Найден за " << i << " шаг(-a;-ов.) \n" << " \n";
		}
		else
			{
				cout << "(*) Метод простой итерации: \n" << " \n";
				cout << "    Корней НЕТ, или возможен случай что x = 0 \n" << " \n";
			}


		i = 0;															//метод простой итерации
		x = a;
		f1 = a - cos(a);
		f2 = b - cos(b);
		if (((f1*f2) < 0))
		{
		do
		{
			x = x - (x - cos(x));
			i++;
		} while (abs(x - cos(x)) > eps);
		cout << "(*) Метод простой итерации: \n" << " \n";
		cout << "    Корень: " << setprecision(10) << x << endl;
		cout << "    Найден за " << i << " шаг(-а;-ов.) \n" << " \n";
		}
		else
			{
				cout << "(*) Метод простой итерации: \n" << " \n";
				cout << "    Корней НЕТ, или возможен случай что x = 0 \n" << " \n";
			}


		i = 0;															//метод половинного деления
		double z;
		f1 = a - cos(a);
		f2 = b - cos(b);
		if (((f1*f2) < 0))
		{
		do
		{
			c = (a + b) / 2;
			if (((a - cos(a))*(c - cos(c)) > 0))
				a = c;
			else
				b = c;
			z = (a + b) / 2;
			i++;
		} while (abs(b - a) > eps);
		x = z;
		cout << "(*) Метод половинного деления: \n" << " \n";
		cout << "    Корень: " << setprecision(10) << x << endl;
		cout << "    Найден за " << i << " шаг(-а;-ов.)\n" << " \n";
		}
		else
			{
				cout << "(*) Метод простой итерации: \n" << " \n";
				cout << "    Корней НЕТ, или возможен случай что x = 0 \n" << " \n";
			}

		cout << "    Хотите повторить? (y/n) ";
		cin >> exit1;
		l++;
	} while (exit1 == 'y');
	cout << "Хотите попробовать с коэфициентом k? (y/n): ";
	cin >> koef;
	cout << " \n";

	if (koef == 'y')
	{
		l = 0;
		j = 2;
		int n = 1000;
		double f1, f2;
		cout << "Найти корень уравнения x-k*cos(x)\n 'Методом простой итерациии'\n 'Методом Ньютона'\n 'Методом половинного деления' \n";
		do {
			int i, k;
			double x, a, b, c, eps;
			cout << " \n" << j << "." << l << ")\n" << " \n";
			cout << "Введите точность вычислений: ";
			cin >> eps;
			cout << "Введите коэфициент k: ";
			cin >> k;
			cout << "Введите границы на оси Ox (a,b): ";
			cin >> a >> b;
			cout << " \n";
			if (a == b)																//проверка интервала k
			{
				cout << "a не должно быть равно b, начните заного!";
				system("pause");
				return 0;
			}
			if (a > b)
			{
				cout << "a должно быть меньше b, начните заного!";
				system("pause");
				return 0;
			}																		//проверка интервала k *

																					//метод Ньютона (k)
			i = 0;
			x = a;
			f1 = a - (k*cos(a));
			f2 = b - (k*cos(b));
			if (((f1*f2) < 0))
			{
				do
				{
					x = x - ((x - (k*cos(x))) / ((k*sin(x)) + 1));
					i++;
				} while ((abs(x - (k*cos(x)))) && (i < n));
				cout << "(*) Метод Ньютона: \n" << " \n";
				cout << "    Корень: " << setprecision(10) << x << endl;
				cout << "    Найден за " << i << " шаг(-a;-ов.) \n" << " \n";
			}
			else
			{
				cout << "(*) Метод простой итерации: \n" << " \n";
				cout << "    Корней НЕТ, или возможен случай что x = 0 \n" << " \n";
			}


			i = 0;																	//метод простой итерации (k)
			x = a;
			f1 = a - (k*cos(a));
			f2 = b - (k*cos(b));
			if (((f1*f2) < 0))
			{
				do
				{
					x = x - (x - (k*cos(x)));
					i++;
				} while ((abs(x - (k*cos(x))) > eps) && (i < 12));
				cout << "(*) Метод простой итерации: \n" << " \n";
				cout << "    Корень: " << setprecision(10) << x << endl;
				cout << "    Найден за " << i << " шаг(-а;-ов.) \n" << " \n";
			}
			else
			{
				cout << "(*) Метод простой итерации: \n" << " \n";
				cout << "    Корней НЕТ, или возможен случай что x = 0 \n" << " \n";
			}

			i = 0;																	//метод половинного деления (k)
			double z;
			f1 = a - (k*cos(a));
			f2 = b - (k*cos(b));
			if (((f1*f2) < 0))
			{
				do
				{
					c = (a + b) / 2;
					if (((a - (k*cos(a)))*(c - (k*cos(c))) > 0))
						a = c;
					else
						b = c;
					z = (a + b) / 2;
					i++;
				} while (abs(b - a) > eps);
				x = z;
				cout << "(*) Метод половинного деления: \n" << " \n";
				cout << "    Корень: " << setprecision(10) << x << endl;
				cout << "    Найден за " << i << " шаг(-а;-ов.)\n" << " \n";
			}
			else
			{
				cout << "(*) Метод простой итерации: \n" << " \n";
				cout << "    Корней НЕТ, или возможен случай что x = 0 \n" << " \n";
			}

			cout << "    Хотите повторить? (y/n) ";
			cin >> exit2;
			l++;
		} while (exit2 == 'y');
	}
	system("pause");

	return 0;
}