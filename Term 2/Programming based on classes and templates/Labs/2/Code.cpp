#include "Head.h"
#include "Friend Fucns.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;


int DBMenu()
{
	int choise = 0;
	cout<<"1) LibraryTxt\t 3) LibraryBin\n";
	cout<<"2) ProductMagTxt 4) ProductMagBin\n";
	cout << "Ваш выбор:> ";
	cin>>choise;
		
	return choise;
}


int menu(string dbName)
{
	int choice;
	cout << "_______________________________________________________________________________\n";
	cout << "\n*** База Данных " << dbName << endl;
	cout << "===============================================================================\n";
	cout << "                             Лабораторные работы                          \n\n";
	cout << "DBTableTxt:\t\t Friend Funcs:\t\t DBTableBin:\n";
	cout << "1) Чтение\t\t 7) Read1\t\t 11) Чтение bin\n";
	cout << "2) Печать\t\t 8) Print1\t\t 12) Печать bin\n";
	cout << "3) Запись в файл\t 9) Write1\t\t 13) Запись bin\n";
	cout << "4) Добавить строку\t\t\t\t 14) Добавить строку bin\n";
	cout << "5) Изменить запись\t\t\t\t\n";  
	cout << "6) Выход\t\t 10) Сменить БД\n";
	cout << "\nДля DBTableSet:\n";
	cout << "15) Чтение\n";
	cout << "16) Печать\n";
	cout << "17) Запись\t\t 18) Тестирование\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << ("Введите номер операции:> ");
	cin >> choice;
	cout << "_______________________________________________________________________________\n\n";

	while(cin.fail())
	{
		cin.clear();
		cin.ignore(10,'\n');					
		cout<<("Ошибка формата. Повторите ввод номера операции\n");
		cin>>choice;
	}			
	return choice;
}

int main()
{
	system("chcp 1251>nul");
	string dataBases[4] = {"LibraryTxt", "ProductMagTxt", "LibraryBin", "ProductMagBin"};
	string dbName;
	myLyb::DBTableTxt tab;
	myLyb::DBTableBin tabBin;
	myLyb::Row row;
	string temp2, temp3, tabName, path = "..\\";
	int temp1, a = 0;

	
	int screenWidth = 80;
	int DBType = DBMenu();
	dbName = dataBases[DBType-1];
	myLyb::DBTableSet DataBase(dbName);

	while(true)
	{
		switch(menu(dbName))
		{
		case 1:				// ЧТЕНИЕ
		{
			if(DBType == 1 || DBType == 2)
			{
				cout << "\nEnter tab Name: ";
				cin >> tabName;
				tab.ReadDBTable(path+dbName+"\\"+tabName+".txt");
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 2:				// ПЕЧАТЬ
		{
			if(DBType == 1 || DBType == 2)
			{
				tab.PrintTable(80);
				system("pause");
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 3:				// ВНЕСТИ ИЗМЕНЕНИЯ В ФАЙЛ
		{
			if(DBType == 1 || DBType == 2)
			{
				tab.WriteDBTable(path+dbName+"\\"+tabName);
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 4:				// ДОБАВИТЬ СТРОКУ
		{
			if(DBType == 1 || DBType == 2)
			{
				row = tab.CreateRow();
				tab.AddRow(row, tab.GetSize());
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 5:				// ИЗМЕНИТЬ ЗАПИСЬ
		{
			if(DBType == 1 || DBType == 2)
			{
				cout << "Введите номер строки(начиная с 0):> ";
				cin >> temp1;
				cout << "Введите название столбца:> ";
				cin >> temp2;
				cout << "Введите изменения:> ";
				cin >> temp3;
				if(tab.GetHeader()[temp2].colType == 1)
				{
					a = atoi(temp3.c_str());
					tab[temp1][temp2] = &a;
				}
				else
					tab[temp1][temp2] = &temp3;
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 6:				// ВЫХОД

			system("pause");
			return 0;
			break;

		case 7:				// READ1
		{
			cout << "\nEnter tab Name: ";
			cin >> tabName;
			//ReadDBTable1(tab,path+tabName+".txt");
			
			break;
		}
		case 8:			//PRINT1
		{
			PrintTable1(tab, 80);
			cout << endl << "^^^ screenWidth 80 ^^^" << endl;
			system("pause");
			/*PrintTable1(tab, 50);
			cout << endl << "^^^ screenWidth 50 ^^^" << endl;
			system("pause");
			PrintTable1(tab, 35);
			cout << endl << "^^^ screenWidth 25 ^^^" << endl;
			system("pause");	*/
			break;
		}
		case 9:			//WRITE1
		{
			//WriteDBTable1(tab,path+tabName);	
			break;
		}
		case 10:			//Сменить БД
		{
			DBType = DBMenu();
			dbName = dataBases[DBType-1];
			myLyb::DBTableSet DataBase(dbName);
			break;
		}
		case 11:
		{
			if(DBType == 3 || DBType == 4)
			{
				cout << "\nEnter tab Name: ";
				cin >> tabName;
				tabBin.ReadDBTable(path+dbName+"\\"+tabName+".bin");
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 12:
		{
			if(DBType == 3 || DBType == 4)
			{
				tabBin.PrintTable(80);
				system("pause");
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 13:
		{
			if(DBType == 3 || DBType == 4)
			{
				tabBin.WriteDBTable(path+dbName+"\\"+tabName+".bin");
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 14:				// ДОБАВИТЬ СТРОКУ Bin
		{
			if(DBType == 3 || DBType == 4)
			{
				row = tabBin.CreateRow();
				tabBin.AddRow(row, tabBin.GetSize());
			} else
			{
				cout << "Несоответствие БД...\n";
				system("pause");
			}
			break;
		}
		case 15:				//DBTableSet
		{
			DataBase.ReadDB();
			break;
		}
		case 16:
		{
			DataBase.PrintDB(screenWidth);
			system("pause");
			break;
		}
		case 17:
		{
			DataBase.WriteDB();
			break;
		}
		case 18:
		{
			tab.WriteTableBin(path+dbName+"\\"+tabName+".bin");
			break;
		}
		default:
		{
			cout << "Неверный ввод, попробуйте сначала...\n" << endl;
			system("pause");
			break;
		}

		}
	}
}