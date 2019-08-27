#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	int n, i, j = 1;
	double y, x, a, k;
	char exit;
	do
	{
		cout << j << ")";
		y = 1;
		cout << "   Введите n [ 1 ; +бесконечность ] : ";
		cin >> n;
		cout << "     Введите x : ";
		cin >> x;

		if (n < 1)
		{
			cout << "     Неверное n " << endl;
			system("pause");
			return 0;
		}
		a = -(x * x) / 2;
		y = 1 + a; k = 1;
		for (i = 2; i < n; i++)
		{
			k = -(x * (i - 1)) / (2 * i);			//(i * x)/((2*i)+2);


			a = a * k;
			y += a;
			if (i == 3) cout << "     При n = " << i << setw(10) << "y = " << y << endl;
			else
				if (i == 5) cout << "     При n = " << i << setw(10) << "y = " << y << endl;
				else
					if (i == 10) cout << "     При n = " << i << setw(9) << "y = " << y << endl;
		}
		cout << " " << endl;
		cout << fixed << "     При n = " << i - 1 << setw(9) << "y = " << y << endl;
		cout << " " << endl;
		cout << setw(10) << "     Продолжить? (y/n) ";
		cin >> exit;
		cout << " " << endl;
		j++;

	} while (exit == 'y');

	system("pause");
	return 0;

}