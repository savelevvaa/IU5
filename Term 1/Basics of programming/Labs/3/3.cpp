#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	int n;
	char povtor;
	double x, y, a, k, s, eps;

	do
	{
		cout << "¬ведите погрешность: ";
		cin >> eps;
		cout << setw(2) << "x" << setw(10) << "S(x)" << setw(12) << "Y(x)" << setw(6) << "N" << endl;
		n = 0; s = 1; a = 1;
		for (x = 0; x <= 1; x = x + 0.2) // цикл с шагом 0.2
		{
			n = 0; s = 1; a = 1;
			y = exp(-1 * (x*x));
			do
			{
				k = -1 * ((x*x) / (n + 1));
				a = a * k;
				s += a;
				n++;
			} while (abs(y - s) > eps);
			cout << fixed << setprecision(1) << setw(3) << x << setprecision(8) << setw(12) << s << setprecision(8) << setw(12) << y << setw(3) << n - 1 << endl;

		}
		cout << " " << endl;
		cout << "’отите продолжить? (y/n) ";
		cin >> povtor;
		cout << " " << endl;
	} while (povtor == 'y');

	system("pause");
	return 0;
	//(x*x / 4 + x / 2 + 1)*exp(x / 2);
}//(n*n + 1)*x / (((n - 1)*(n - 1) + 1) * 2 * n);