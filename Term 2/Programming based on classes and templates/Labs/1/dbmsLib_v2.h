//файл DBMSFuncsLib.h
#pragma once
#ifndef _DBMSFuncsLib_
#define _DBMSFuncsLib_
#include <iostream>
#include <strstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;
namespace DBMSFuncs
{
//-----------------класс DBDate----------------------------
  class DBDate
  {	
		static const int arrDays[13];
		friend string DateToStr(DBDate& date);
		friend ostream& operator<<(ostream& out,DBDate& date);
		int day, month, year;
	public:
		DBDate(string date);//формат строки: dd.mm.yyyy
		DBDate(int d,int m,int y);
		DBDate():day(0),month(0),year(0){};//конструктор по умолчанию
		DBDate(DBDate& dat):day(dat.day),month(dat.month),year(dat.year){}
		int GetDay();
		int GetMonth();
		int GetYear();
		bool IsLeapYear (int year); //год высокосный?
		int GetDaysInMonth(int month,int year);//Количество дней в месяце
		int DaysInCurYear();//Количество дней от начала года до текущей даты
		bool operator==(DBDate& date);
		bool operator<(DBDate& date); 
		bool operator>(DBDate& date);
		bool operator<= (DBDate& date);
		bool operator>= (DBDate& date);
		bool operator!= (DBDate& date);
		DBDate& operator+=(int days);//Прибавляет к текущей дате days дней
		DBDate& operator-=(int days);//Вычитает из текущей даты days дней
		int operator-(DBDate& date);	//Количество дней между текущей датой и date
									//Если текущая дата > date, результат < 0.
  };
//======TableDataType-перечисление типов полей таблиц БД====== 
enum TableDataType {
 NoType,
 Int32,
 Double,
 String,
 Date
};
//const int DELTA = 10;//запас в 10 строк для новых записей в таблицу. 
//Если запас израсходован, то для его восстановления нужно записать 
//таблицу в файл и снова прочитать её.
const int LENGTH = 24;//размер полей для имени таблицы и имени столбца. 
//Для выравнивания длин имён используются ведущие пробелы.
//ColumnDesc - описание данных в столбце таблицы 
//данные типа string имеют одинаковую длину (length) внутри одного столбца, 
//но в разных столбцах их длина может отличаться. 
  struct ColumnDesc { 
	char colName[LENGTH];//имя столбца
	TableDataType colType;//тип данных в столбце таблицы
	int length; //максимальное число символов в текстовом представлении 
	//данных столбца, включая обязятельный '\0' для типа String
	ColumnDesc(){};
	ColumnDesc( char * name, TableDataType type, int len){ 
		strcpy_s(colName,name);
		colType=type;
		length=len; 
	} 
}; 
  struct Strip{//полоса распечатки таблицы
			int nField;//число полей 
			int* fieldWidth;//ширина полей в столбцах полосы  
		};					//с учетом интервалов и длины имени столбца
  typedef map<string, void*> Row;
  typedef map<string, ColumnDesc> Header;
  enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};
  TableDataType GetType(string columnName,Header hdr );
  string GetTabNameFromPath(string path);
  string ignoreBlanc(const string str);
  void* GetValue(string value, string columnName,Header hdr);
  bool comparator(TableDataType type,void *obj1,Condition condition,void *obj);
  class DBTableTxt;
 // Row CreateRow(DBTableTxt tab);
  //--------------------класс DBTableTxt-----------------------------
  class DBTableTxt
  {
	private:
		string tableName;
		string primaryKey;//имя столбца, являющегося первичным ключом (значения полей
	//в этом столбце должны быть уникальными). Необходим только в "основных" таблицах. При 
	//удалении записи из таблицы значение первичного ключа в новых записях не повторяется.
	//Во "вспомогательных" таблицах, включаемых в реляционные БД для создания связей
	//между таблицами типа "многие-ко-многим", он не используется (в файле его нет). 
	//Примеры "вспомогательных" таблиц: Abonements, OrderDetails. В них записи 
	//идентифицируются комбинацией ключей связываемых таблиц. 
	//Значение по умолчанию "NoPrimaryKey" будем использовать как признак того, что объект
	//DBTableTxt связан с вспомогательной таблицей. 
	//Имя таблицы и имя первичного ключа таблицы будем хранить в первой строке
	//табличного файла. Вторая строка табличного файла содержит заголок таблицы.
	//В файле "DBTables" будем хранить имена файлов с таблицами БД.
		string fileName;
		Header columnHeaders;
		vector<Row> data;
	public:
		DBTableTxt(){}
		DBTableTxt(string tabName): tableName(tabName){}
		~DBTableTxt(){}
 		string valueToString(Row& row,string columnName);
		void ReadTableTxt(string tabName);//tabName=path+tableName
		void ReadTableBin(string tabName);//чтение таблицы из бинарного файла
		void PrintTable(int screenWidth/*,string dbName*/);
		void WriteTableTxt(string tabName);//tabName=path+tableName	
		void WriteTableBin(string tabName);//запись таблицы в бинарный файл
		int GetSize();
		Row& operator[](int ind);				
		string GetTableName();
		string GetPrimaryKey(){return primaryKey;}
		Header GetHeader();
		void SetHeader(Header& hdr);
		void SetFileName(string path){fileName=path+"//"+tableName+".txt";} 
		string GetFileName(){return fileName;}
		Row CreateRow();
		void AddRow(Row row);
		DBTableTxt SelfRows(string columnName,Condition cond, void* value);
		//Макет распечатки таблицы:
		//screenWidth - ширина экрана (входной параметр)
		//nStrips - число полос в распечатке (выходной параметр)
		//strips[nStrips] - описание полос таблицы: 
		//число столбцов и ширина каждого столбца в полосе (выходной параметр)
		void CreateTableMaket(Strip* &strips,int &nStrips,int screenWidth);
		friend void WriteDBTableTxt1(DBTableTxt& tab,string fileName);
		friend void WriteDBTableBin1(DBTableTxt& tab,string fileName);
		friend void PrintDBTable1(DBTableTxt& tab,int screenSize);
		friend void ReadDBTableTxt1(DBTableTxt& tab,string fileName);
		friend void ReadDBTableBin1(DBTableTxt& tab,string fileName); 
		friend DBTableTxt SelfRows1(DBTableTxt& tab,string columnName,Condition cond, void* value);
  };
 //-----------------------класс Relation----------------------
  class Relation//описывает связь двух таблиц
    {
		public:
			Relation();
			string relationName;
			string parentTable;
			string parentPrimaryKey;
			string childTable;
			string childSecondaryKey;
    };
//-------------------------класс DBTableSet---------------------
 class DBTableSet
 {
    private:
		string dbName;
	    map<string, DBTableTxt> db;
	public: 
			DBTableSet(){};
			DBTableSet(string name);
			int ReadDB();
			void PrintDB(int screenWidth);
			void WriteDB();
			string GetDBName(){return dbName;}
			DBTableTxt& operator[](string tableName) { return db[tableName]; }
			Relation GetRelation(string relationName);
			Row ParentRow(Relation& relation,Row& childRow);
			DBTableTxt ChildRows(Relation& relation,Row& parentRow);
  };
}
#endif //_DBMSFuncsLib_