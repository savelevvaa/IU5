#include <iostream>
using namespace std;

int main()  // сумма первых n чисел делящихся на 5 и не делящихся на m
{

	system("chcp 1251>nul");
	char povtor;

	do {

		int n, m, sum = 0; // n множ-во нат. чисел, m "неделитель"

		cout << "Введите n: ";
		cin >> n;
		cout << "Введиет m: ";
		cin >> m;

		if (n < m)
		{
			cout << "N должно быть меньше M!!!";
			system("pause");
			return 0;
		}
		for (int i = 1; i < n; i++)
		{
			if (i % 5 == 0 && i%m != 0)
			{
				sum += i;
				cout << sum << ", ";
			}
		}
		cout << "Результат: " << sum << endl;

		cout << "Продолжить!? (y/n)" << endl;
		cin >> povtor;

	} while (povtor == 'y');

	system("pause");

	return 0;

}