#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <fstream>
#include <ctime>
#include <Windows.h>
#include "head8_1.h"
using namespace std;

struct Stats
{
	ifstream fin1, fin2;
	unsigned char letter;					//введённая буква
	int variant;				//кол-во закодированний
	int quantity;
	int codes[256];	//содержит коды символов
	Stats();  
	void stats(char* fName1, char* fName2, int n, int &skip);	//поиск совпадений и шифрований
	void Cout(int skip);		//печать

};
Stats::Stats()	//обнуления
{
	for (int i = 0; i < 256; i++)	//обнуление массива
		codes[i] = NULL;
}
void Stats::stats(char* fName1, char* fName2, int n, int& skip)
{

	fin1.open(fName1);
	fin2.open(fName2);
	quantity = 0;
	char ch1, ch2;
	cout << "Введите символ: ";
	cin >> letter;
	for (int i = 0; fin1.get(ch1); i++)
	{
		fin2.get(ch2);
		if (letter == ch1)
		{
			int j = (unsigned char)ch2;
			codes[j] += 1;
			skip = 1;
			quantity++;
		}
	}

	fin1.close();
	fin2.close();
}

void Stats::Cout(int skip)
{
	if (skip == 0)	//буква встречалась в тексте
	{
		cout << "Символ в тексте не встречается! " << endl << endl;
		
	}
	else
	{
		cout << "Кол-во символов '" << letter << "' в исходном тексте: " << quantity << endl << endl;
		int w = 3;
		cout << setw(3) << "№   ";
		for (int j = 0; j < 16; j++) cout << setw(w) << (j + 1);
		cout << "\n____________________________________________________\n";

		for (int i = 0; i < 256; i++)
		{
			if (i % 16 == 0)
			{
				cout << endl;
				cout << setw(3) << (i / 16) + 1 << "|";
			}
			cout << setw(w) << codes[i];
		}
		cout << endl << endl;
		for (int i = 0; i < 256; i++)
		{
			if (codes[i] != 0)
			{
				cout << "char(" << i << ") " << char(i) << "  -  " << codes[i] << endl;
			}
		}
			for (int i = 0; i < 256; i++)
		{
			codes[i] = NULL;
		}
		cout << endl << endl;
	}
}

int menu(int d)
{
	int choice;
	if(d == 1)
		cout << "(1)Зашифровать (2)Дешифровать (3)Рандобный массив ключей (4)Расположение Лабы\n(5)Завершить (6)Ключи (7)Статистка \> ";
	if(d == 2)
		cout << "(1)Зашифровать (2)Дешифровать (3)Массив сумм (4)Расположение Лабы\n(5)Завершить (6)Ключи (7)Статистка \> ";
	cin >> choice;
	cout << endl;
	return choice;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	srand(NULL);
	int n;						//размерность массива
	int exit1 = 1, exit2 = 1;	//выход из циклов while				
	int a, b;					//границы РАНДОМА
	char *keys;					//указатель на массив ключей
	int count = 1;				// счётчик проходов "заного"
	int menuDeff = 1;			//ДЛЯ МЕНЮ
	int skip = 1;
	char FName1[12] = "Massege.txt";	//файл чтения
	char FName2[12] = "Code.txt";	//файл записи шифра
	char FName3[12] = "Result.txt";	//файл записи расшифровки
	Stats letter;
	cout << "\t\t\t\tШифрование\n\n";
	cout << "Файлы по умолчанию? ( (1)Да (2)Нет ): ";
	cin >> n;
	if (n == 2)
	{
		cout << "Введите название файла чтения: ";
		cin >> FName1;
		cout << "Введите название файла записи: ";
		cin >> FName2;
	}

	ifstream fin(FName1, ios::binary);						//чтение
	ofstream fout(FName2, ios::binary);						//запись
	if (!fin.is_open())
	{
		cout << "Проблема открытия файла Чтения...\n";
		system("pause");
		return 1;
	}
	else
	{
		cout << "Файлы открыты!\n";
	}

	createKeys(FName1, keys, n);		//создаём массив ключей
	fin.close();
	fout.close();
	while (exit2 == 1)
	{
		cout << "////////////////////////////////////////////////////////////////////////////////";
		cout << "((" << count << "))" << endl;
		exit1 = 1;
		while (exit1 == 1)
		{	
			switch (menu(menuDeff))
			{
			case 1:	//зашифровать
			{
				fin.open(FName1,ios::binary);
				fout.open(FName2,ios::binary);
				int nKey = 0;
				char ch = fin.get();
				while(fin)
				{
					
					fout.put(ch^keys[nKey%256]);
					ch = fin.get();
					nKey++;
				}
				if (nKey) cout << "*** Зашифрованно\n\n";
				fin.close();
				fout.close();
				break;
			}
			case 2:	//расшифровать
			{
				fin.open(FName2, ios::binary);
				fout.open(FName3, ios::binary);
				int nKey = 0;
				char ch = fin.get();
				while (fin)
				{

					fout.put(ch^keys[nKey % 256]);
					ch = fin.get();
					nKey++;
				}
				if (nKey) cout << "*** Расшифрованно\n\n";
				fin.close();
				fout.close();
				break;
			}
			case 3:	//с начала(новый массив ключей)
			{
				if (menuDeff == 1)
				{
					exit1 = 0;
					menuDeff = 2;
					count++;
					cout << "Введите интервал случайности(a, b): ";
					cin >> a >> b;
					Keys(keys, n, a, b);
					break;
				}
				if(menuDeff==2)
				{
					menuDeff = 1;
					exit1 = 0;
					count++;
					createKeys(FName1, keys, n);
					break;
				}
			}
			case 4:	//завершить
			{
				system("notepad");
				cout << argv[0] << endl << endl;
				break;

			}
			case 5:	//адрес программы(.exe)
			{
				exit1 = 0;
				exit2 = 0;
				cout << "Конец!" << endl << endl;
				break;
			}
			case 6:	//вывод массива ключей
			{
				printKeys(keys, n);					//печать массива ключей
				break;
			}
			case 7:	//стастистика
			{
				int skip;
				char ex;
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*Статистика* \n";
				do {
					skip = 0;
					letter.stats(FName1, FName2, n, skip);
					letter.Cout(skip);
					cout << "Выйти?(y/n) ";
					cin >> ex;
					cout << endl;
				} while (ex != 'y');
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
				break;
			}
			}
		}
	}
	
	delete[] keys;
	system("pause");
	return 0;
}

