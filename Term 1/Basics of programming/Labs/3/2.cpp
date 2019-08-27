#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	system("chcp 1251>nul");
	char povtor;
	int i;
	double S, a; // S сумма, a ввод

	do
	{
		cout << "¬ведите а: ";
		cin >> a;
		S = 1;
		i = 0;

		if (a < 0)
		{
			for (i = 3; i <= 9; i += 3)
			{
				S *= (i - 2);
			}
		}
		else
		{
			for (i = 2; i <= 8; i += 2)
			{
				S *= i * i;

			}
			S = S - a;
		}

		cout << fixed << setprecision(15) << S << endl;
		cout << "’отите продолжить? (y/n)" << endl;
		cin >> povtor;
	} while (povtor == 'y');



	system("pause");
	return 0;
}