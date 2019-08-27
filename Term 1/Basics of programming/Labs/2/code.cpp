#include <iostream>
using namespace std;
int main()
{
	system("chcp 1251>nul");
	int h, m, h1;
	int timeOfDay = 0;

	int hPadeg = 0, mPadeg = 0;
	cout << "Ââåäèòå âðåìÿ" << endl;                        // 1.×ÀÑ 2.×ÀÑÀ 3.×ÀÑÎÂ
	cin >> h >> m;                                       // 1.ÌÈÍÓÒ 2.ÌÈÍÓÒÀ 3.ÌÈÍÓÒÛ
	cout << h << ":" << m << endl;
	if (h >= 0 && h <= 24 && m >= 0 && m <= 59) {
		if (h == 12 && m == 0) {
			cout << "Ïîëäåíü" << endl;
			return 0;
		}
		if (h == 0 && m == 0) {
			cout << "Ïîëíî÷ü" << endl;
			return 0;
		}

		if (h >= 5 && h < 12) timeOfDay = 1;  // ÓÒÐÎ
		if (h >= 12 && h < 18) timeOfDay = 2;   // ÄÅÍÜ
		if (h >= 18 && h <= 23) timeOfDay = 3;  // ÂÅ×ÅÐ
		if (h >= 0 && h < 5) timeOfDay = 4;    // ÍÎ×Ü




		h1 = h;
		if (h > 12)
			h = h - 12;


		if (h == 1) hPadeg = 1; // ÷àñ
		if (h > 1 && h < 5) hPadeg = 2;  // ÷àñà
		if (h > 4 && h < 13) hPadeg = 3;  // ÷àñîâ

		mPadeg = 1; // ìèíóò
		if (m % 10 == 1 && m != 11) mPadeg = 2; // ìèíóòà
		if ((m % 10 > 1 && m % 10 < 5) && !(m > 11 && m < 15)) mPadeg = 3;// ìèíóòû

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

		cout << "Âðåìÿ: ";
		if (h != 0) {
			cout << h;
			switch (hPadeg)
			{
			case 1: cout << " ×àñ "; break;
			case 2: cout << " ×àñà "; break;
			case 3: cout << " ×àñîâ "; break;
			default: break;
			}

			if (m != 0) {
				cout << m;

				switch (mPadeg)
				{
				case 1: cout << " Ìèíóò "; break;
				case 2: cout << " Ìèíóòà "; break;
				case 3: cout << " Ìèíóòû "; break;
				default:break;
				}

				switch (timeOfDay)
				{
				case 1: cout << " Óòðà " << endl; break;
				case 2: cout << " Äíÿ " << endl; break;
				case 3: cout << " Âå÷åðà " << endl; break;
				case 4: cout << " Íî÷è " << endl; break;
				default: cout << " wrong " << endl; break;
				}
			}
			else {
				switch (timeOfDay)
				{
				case 1: cout << " Óòðà " << endl; break;
				case 2: cout << " Äíÿ " << endl; break;
				case 3: cout << " Âå÷åðà " << endl; break;
				case 4: cout << " Íî÷è " << endl; break;
				default: cout << " wrong " << endl; break;
				}
				cout << " Ðîâíî ";
			}
		}



		else {
			cout << "0 ×àñîâ ";
			if (m != 0) {
				cout << m;

				switch (mPadeg)
				{
				case 1: cout << " Ìèíóò "; break;
				case 2: cout << " Ìèíóòà "; break;
				case 3: cout << " Ìèíóòû "; break;
				default:break;
				}

				switch (timeOfDay)
				{
				case 1: cout << " Óòðà " << endl; break;
				case 2: cout << " Äíÿ " << endl; break;
				case 3: cout << " Âå÷åðà " << endl; break;
				case 4: cout << " Íî÷è " << endl; break;
				default: cout << " wrong " << endl; break;
				}
			}
			else {
				switch (timeOfDay)
				{
				case 1: cout << " Óòðà " << endl; break;
				case 2: cout << " Äíÿ " << endl; break;
				case 3: cout << " Âå÷åðà " << endl; break;
				case 4: cout << " Íî÷è " << endl; break;
				default: cout << " wrong " << endl; break;
				}
				cout << " Ðîâíî ";
			}




		}


	}
	else cout << "wrong" << endl;
	system("pause");
	return 0;

}
