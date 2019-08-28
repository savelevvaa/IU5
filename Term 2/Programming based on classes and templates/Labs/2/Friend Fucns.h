#pragma once
#ifndef FRIENF_FUNCS_H
#define FRIENF_FUNCS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;
using namespace myLyb;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myLyb::ReadDBTable1(myLyb::DBTableTxt& tab,string fileName)
//void DBMSFuncs1::ReadDBTableTxt1(myLyb::DBTableTxt& tab,string fileName)
{
	

	ifstream fin(fileName.c_str(), ios::in);
	if(fin.fail())
	{
		cout << "\nЧто-то пошло не так... Ошибка открытия файла!\n" << endl;
		return;
	}
	tab.SetFileName(fileName);

	vector<ColumnDesc> strArray;//буфер для чтения строки заголовка таблицы из файла
	char line[200];
	char *token, *next_token, delims[] = "|";
	fin.getline(line, 200); //чтение первой строки
	next_token=line;
	token = strtok_s(next_token, delims, &next_token);
	tab.tableName = token;
	token = strtok_s(next_token, delims, &next_token);
	tab.primaryKey = token;
	

	fin.getline(line, 200); //чтение заголовка таблицы
	next_token=line;
	
	ColumnDesc colHdr;//буфер для чтения заголовка одного столбца таблицы

	while( (token = strtok_s( next_token, delims, &next_token)) != NULL ) //цикл по словам (лексемам) в строке
	{
		strcpy_s(colHdr.colName,token);
		token = strtok_s( next_token, delims, &next_token);
		//colHdr.colType=GetType(token);
		token = strtok_s( next_token, delims, &next_token);
		colHdr.length=atoi(token);
		strArray.push_back(colHdr);	//выделяет память с помощью new, копирует в 	
									//неё заголовок столбца (colHdr) и добавляет указатель на копию  в конец вектора		
	}
	Header hdr;
	for (unsigned int  j = 0; j < strArray.size() ;  j ++)
	{
	         hdr[strArray[j].colName]=strArray[j];// !!! использование операции индексации
	}
	tab.SetHeader(hdr);

	tab.data.clear();//вызов метода контейнера vector (для обеспечения повторного чтения)
	while (fin.getline(line, 200))
	{		
		Row row=*(new Row());	//буфер для формирования строки таблицы выделяется память под корневой узел map
		int j = 0;
		token = strtok_s( line, delims, &next_token);
		
		while(token) //цикл по столбцам (словам) в строке
		{
			string value=token;
			//добавление поля в строку с преобразованием типа
			//strArray[j] - имя столбца в заголовке таблицы
		row[strArray[j].colName]= GetValue(value,strArray[j].colName,tab.columnHeaders);		
		j=j++;						//индекс следующего столбца в векторе strArray
			token = strtok_s( next_token, delims, &next_token);
		}
		tab.data.push_back(row);//добавить строку данных в таблицу
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myLyb::WriteDBTable1(myLyb::DBTableTxt& tab,string fileName)
//void DBMSFuncs1::WriteDBTableTxt1(myLyb::DBTableTxt& tab,string fileName)
{
	ofstream fout(fileName+".txt", ios::out);
	if(fout.fail())
	{
		cout << "\nЧто-то пошло не так... Ошибка открытия файла!\n" << endl;
		return;
	}
	string Type[] = {"NoType","Int32","Double","String","Date"};	//массив строк для enum
	Header::iterator iter, iterWhile;								//итераторы
	fout << tab.tableName << "|" << tab.primaryKey << endl;			//запись названия таблицы и primaryKey
	iter = tab.columnHeaders.begin();			//итератор в начало 
	iterWhile = iter;
	int n = 0;
	while(iterWhile!=tab.columnHeaders.end())						//запись второй строки в файл с названиями заголовков 
	{
		fout << iter->second.colName << "|" << Type[iter->second.colType] << "|" << iter->second.length;
		iter++;
		iterWhile++;
		n++;			//считает кол-во столбцов
		if(iterWhile!=tab.columnHeaders.end())
			fout << "|";
	}
	fout << "\n";
	for(int i = 0; i < tab.data.size(); i++)	//цикл по строкам таблицы
	{
		iter = tab.columnHeaders.begin();
		for(int j = 0; j < n; j++)				//цикл по элементам i-й строки j-го столбца
		{
			fout << tab.valueToString(tab[i],iter->second.colName);
			if(n-1 != j)
				fout << "|";
			iter++;
		}
		fout << endl;
	}
	
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myLyb::PrintTable1(myLyb::DBTableTxt& tab, int screenSize)
//void DBMSFuncs1::PrintDBTable1(myLyb::DBTableTxt& tab, int screenSize)
{
	int n = 0;
	string Type[] = {"NoType","Int32","Double","String","Date"};	//массив строк для enum
	Header::iterator iter, iterSave, iterTake;
	int Edge;
	Strip* strips;
	int nStrips;
	tab.CreateTableMaket(strips, nStrips, screenSize);

	for(int i = 0; i < nStrips; i++)//ЦИКЛ ПО ПОЛОСАМ ПЕЧАТИ ТАБЛИЦЫ
	{
		Edge = screenSize - 1;//для печати вертикальной черты разграничения 
		if(i == 0)
			cout << "\nТаблица " << tab.tableName << endl;
		else
			cout << "\nПродолжение таблицы " << tab.tableName << endl;

		for(int j = 0; j < Edge; j++)	//цикл верт. черты
			cout << "=";
		cout << endl;

		if(i == 0)
			iter = tab.columnHeaders.begin();
		else
			iter = iterTake;
		for(int j = 0; j < strips[i].nField; j++)//Печать ПЕРВОЙ строки заголовка таблицы
		{
			cout << setw(strips[i].fieldWidth[j]) << iter->second.colName;
			iter++;
		}
		iterSave = iter;//Запоминаем значение итератора
		cout << endl;

		if(i == 0)
			iter = tab.columnHeaders.begin();
		else
			iter = iterTake;
		for(int j = 0; j < strips[i].nField; j++)//Печать ВТОРОЙ строки заголовка таблицы
		{
			cout << setw(strips[i].fieldWidth[j]) << Type[iter->second.colType];
			iter++;
		}
		cout << endl;

		for(int j = 0; j < Edge; j++)	//цикл верт. черты
				cout << "-";
		cout << endl;

		for(int j = 0; j < tab.data.size(); j++)	//цикл по строкам таблицы
		{
			if(i == 0)
				iter = tab.columnHeaders.begin();
			else
				iter = iterTake;
			for(int k = 0; k < strips[i].nField; k++)				//цикл по элементам строки j-го столбца
			{
				cout << setw(strips[i].fieldWidth[k]) << tab.valueToString(tab[j],iter->second.colName);
				iter++;
			}
			cout << endl;
		}

		for(int j = 0; j < Edge; j++)	//цикл верт. черты
			cout << "=";
		cout << endl;
		iterTake = iterSave;
	}
}

#endif //FRIENF_FUNCS_H