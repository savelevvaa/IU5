#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "head 10_0.h"
using namespace std;


int menu()
{
	int choice;
	cout << "\n(1) Добавить слово\n(2) Удалить слово\n(3) Перевод Eng-Rus\n(4) Перевод Rus-Eng\n(5) Просмотр словаря\n(6) Запись словоря в файл\n(7) Чтение словаря из файла\n(8) Отчистить словарь\n(9) Завершить\n:> ";
	cin >> choice;
	cout << endl;
	return choice;
}



int main()
{
	system("chcp 1251>nul");
	int nWords = 0;
	Dictionary elem;
	Dictionary* dict = NULL;



	cout << "\t\t\tАнгло-Русский словарь" << endl << endl;

	while (1)
	{
		switch (menu())
		{
		case 1:				//ДОБАВЛЕНИЕ СЛОВА
		{
			int exit = 0;
			while (exit != 2)
			{
				int lang;
				cout << endl << "Язык? ( (1)Rus,(2)Eng )\n:>";
				cin >> lang;
				cout << endl;
				if (lang == 1)
				{
					cout << "Введите слово(Rus): ";
					cin >> elem.rus;
					cout << "Введите перевод(Eng): ";
					cin >> elem.eng;
				}
				if (lang == 2)
				{
					cout << "Введите слово(Eng): ";
					cin >> elem.eng;
					cout << "Введите перевод(Rus): ";
					cin >> elem.rus;
				}
				cout << endl;
				addWord(dict, nWords, elem);
				memset(elem.rus, 0, 31);
				memset(elem.eng, 0, 31);
				cout << "Ещё одно? ( (1)Да (2)Нет )\n:> ";
				cin >> exit;
			}
			break;
		}
		case 2:				//УДАЛЕНИЕ СЛОВА
		{
			int var;
			int exit = 0;
			while (exit != 2)
			{
				int lang;
				cout << endl << "Язык? ( (1)Rus,(2)Eng )\n:> ";
				cin >> lang;
				if (lang == 1)
				{
					cout << "Введите слово(Rus): ";
					cin >> elem.rus;
					var = 1;
				}
				if (lang == 2)
				{
					cout << "Введите слово(Eng): ";
					cin >> elem.eng;
					var = 2;
				}
				cout << endl;
				searchWord(dict, nWords, var, elem);
				if (var == 0)
				{
					deleteWord(dict, nWords, elem);
					cout << "\t***Выполнено\n\n";
				}
				memset(elem.rus, 0, 31);
				memset(elem.eng, 0, 31);
				cout << "Ещё одно? ( (1)Да (2)Нет )\n:> ";
				cin >> exit;
			}
			break;
		}
		case 3:				//ПЕРЕВОД С ENG
		{
			int exit = 0;
			while (exit != 2)
			{
				bool log = 0;
				cout << endl << "Введите слово(Eng): ";
				cin >> elem.eng;
				cout << "Перевод: ";
				for (int i = 0; i < nWords; i++)
				{
					if (*(elem.eng) == *(dict[i].eng))
					{
						cout << dict[i].rus << ", ";
						log = 1;
					}
				}
				cout << "\b\b.\n\n";
				if (log == 0)
					cout << "Слова в словаре не найдено...\n\n";
				cout << "Ещё одно? ( (1)Да (2)Нет )\n:> ";
				cin >> exit;
			}
			memset(elem.eng, 0, 31);
			break;
		}
		case 4:				//ПЕРЕВОД С RUS
		{
			int exit = 0;
			while (exit != 2)
			{
				bool log = 0;
				cout << endl << "Введите слово(Rus): ";
				cin >> elem.rus;
				cout << "Перевод: ";
				for (int i = 0; i < nWords; i++)
				{
					if (*(elem.rus) == *(dict[i].rus))
					{
						cout << dict[i].eng << ", ";
						log = 1;
					}
				}
				cout << "\b\b.\n\n";
				if (log == 0)
					cout << "Слова в словаре не найдено...\n\n";
				cout << "Ещё одно? ( (1)Да (2)Нет )\n:> ";
				cin >> exit;
			}
			memset(elem.rus, 0, 31);
			break;
		}
		case 5:				//ПЕЧАТЬ СЛОВАРЯ
		{
			if (nWords != 0)
			{
				sorting(dict,nWords);
				cout << "Словарь: " << endl;
				for (int i = 0; i < nWords; i++)
					cout << dict[i];
			}
			else
				cout << "Словарь пуст..." << endl;
			break;
		}
		case 6:				//ЗАПИСЬ В ФАЙЛ
		{
			ofstream fout("write.txt");
			for (int i = 0; i < nWords; i++)
			{
				fout << dict[i];
			}
			cout << "\t***Выполнено\n";
			fout.close();
			break;
		}
		case 7:				//ЧТЕНИЕ ИЗ ФАЙЛА
		{
			if (nWords != 0) delete[] dict;
			ifstream fin("read.txt", ios::in);
			char line[100];
			while (fin.getline(line, 100))
				nWords++;
			nWords /= 2;
			dict = new Dictionary[nWords];
			fin.clear();
			fin.seekg(0);
			for (int i = 0; i < nWords; i++)
			{
				fin >> dict[i].rus;
				fin >> dict[i].eng;
			}
			cout << "\t***Выполнено\n";
			fin.close();
			break;
		}
		case 8:				//ЗАВЕРШИТЬ
		{
			cleanDict(dict, nWords);
			break;
		}
		case 9:
		{
			delete[] dict;
			return 0;
		}
		default: cout << "\nВыберете существующую операцию..." << endl;
		}
	}

	system("pause");
	return 0;
}