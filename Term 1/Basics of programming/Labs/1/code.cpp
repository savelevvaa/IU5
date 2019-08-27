#include <iostream>
using namespace std;
int main()
{
	system("chcp 1251>nul");
	int h, m, h1;
	int timeOfDay = 0;

	int hPadeg = 0, mPadeg = 0;
	cout << "Введите время" << endl;                        // 1.ЧАС 2.ЧАСА 3.ЧАСОВ
	cin >> h >> m;                                       // 1.МИНУТ 2.МИНУТА 3.МИНУТЫ
	cout << h << ":" << m << endl;
	if (h >= 0 && h <= 24 && m >= 0 && m <= 59) {
		if (h == 12 && m == 0) {
			cout << "Полдень" << endl;
			return 0;
		}
		if (h == 0 && m == 0) {
			cout << "Полночь" << endl;
			return 0;
		}

		if (h >= 5 && h < 12) timeOfDay = 1;  // УТРО
		if (h >= 12 && h < 18) timeOfDay = 2;   // ДЕНЬ
		if (h >= 18 && h <= 23) timeOfDay = 3;  // ВЕЧЕР
		if (h >= 0 && h < 5) timeOfDay = 4;    // НОЧЬ




		h1 = h;
		if (h > 12)
			h = h - 12;


		if (h == 1) hPadeg = 1; // час
		if (h > 1 && h < 5) hPadeg = 2;  // часа
		if (h > 4 && h < 13) hPadeg = 3;  // часов

		mPadeg = 1; // минут
		if (m % 10 == 1 && m != 11) mPadeg = 2; // минута
		if ((m % 10 > 1 && m % 10 < 5) && !(m > 11 && m < 15)) mPadeg = 3;// минуты

/*		if (m>4 && m<21) mPadeg = 1;
		if (m%10 ==
		if (m>21 && m<25) mPadeg = 3;
		if (m>24 && m<31) mPadeg = 1;
		if (m>31 && m<35) mPadeg = 3;
		if (m>34 && m<41) mPadeg = 1;
		if (m>41 && m<45) mPadeg = 3;
		if (m>44 && m<51) mPadeg = 1;
		if (m>51 && m<55) mPadeg = 3;
		if (m>54 && m<61) mPadeg = 1;
		*/

		cout << "Время: ";
		if (h != 0) {
			cout << h;
			switch (hPadeg)
			{
			case 1: cout << " Час "; break;
			case 2: cout << " Часа "; break;
			case 3: cout << " Часов "; break;
			default: break;
			}

			if (m != 0) {
				cout << m;

				switch (mPadeg)
				{
				case 1: cout << " Минут "; break;
				case 2: cout << " Минута "; break;
				case 3: cout << " Минуты "; break;
				default:break;
				}

				switch (timeOfDay)
				{
				case 1: cout << " Утра " << endl; break;
				case 2: cout << " Дня " << endl; break;
				case 3: cout << " Вечера " << endl; break;
				case 4: cout << " Ночи " << endl; break;
				default: cout << " wrong " << endl; break;
				}
			}
			else {
				switch (timeOfDay)
				{
				case 1: cout << " Утра " << endl; break;
				case 2: cout << " Дня " << endl; break;
				case 3: cout << " Вечера " << endl; break;
				case 4: cout << " Ночи " << endl; break;
				default: cout << " wrong " << endl; break;
				}
				cout << " Ровно ";
			}
		}



		else {
			cout << "0 Часов ";
			if (m != 0) {
				cout << m;

				switch (mPadeg)
				{
				case 1: cout << " Минут "; break;
				case 2: cout << " Минута "; break;
				case 3: cout << " Минуты "; break;
				default:break;
				}

				switch (timeOfDay)
				{
				case 1: cout << " Утра " << endl; break;
				case 2: cout << " Дня " << endl; break;
				case 3: cout << " Вечера " << endl; break;
				case 4: cout << " Ночи " << endl; break;
				default: cout << " wrong " << endl; break;
				}
			}
			else {
				switch (timeOfDay)
				{
				case 1: cout << " Утра " << endl; break;
				case 2: cout << " Дня " << endl; break;
				case 3: cout << " Вечера " << endl; break;
				case 4: cout << " Ночи " << endl; break;
				default: cout << " wrong " << endl; break;
				}
				cout << " Ровно ";
			}




		}


	}
	else cout << "wrong" << endl;
	system("pause");
	return 0;

}
