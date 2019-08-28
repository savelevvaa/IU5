#ifndef HEAD
#define HEAD
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

namespace myLyb
{
	class DBDate {
    private:
        static const int arrDays[13];
        friend ostream& operator<<(ostream& out, DBDate& date)
		{
			out << date.GetDay() << '.' << date.GetMonth() << '.' << date.GetYear();
			return out;
		}
        friend string DateToStr(DBDate &date)
		{
			stringstream ss;
			ss << date.GetDay() << '.' << date.GetMonth() << '.' << date.GetYear();
			string s;
			ss >> s;
			return s;
		}
        int day, month, year;
    public:
        DBDate(string date)
		{
			stringstream ss;
			char c;
			ss << date;
			ss >> day >> c >> month >> c >> year;
		}
        DBDate(int d, int m, int y)
		{
			day = d;
			month = m;
			year = y;
		}
        DBDate() : day(0), month(0), year(0) {}
        DBDate(DBDate &dat) : day(dat.day), month(dat.month), year(dat.year) {}
		int GetDay(){return day;}
		int GetMonth(){return month;}
        int GetYear(){return year;}
		bool IsLeapYear(int year){return !(year % 4 || (year % 100 == 0 && year % 400));}
        int GetDaysInMonth(int m, int y)
		{
			if (IsLeapYear(year) && month == 2)
				return arrDays[month] + 1;
			else
				return arrDays[month];
		}
        int DaysInCurYear()
		{
			int days = 0;
			for (int i = 1; i < month; i++)
			    days += arrDays[i];
			if (IsLeapYear(year) && month >= 2) {
			    if (month > 2)
			        days++;
			    else if (month == 2 && day == 29)
			        days++;
			}
			days += day;
			return days;
		}
		bool operator==(DBDate &date){return (date.day == day && date.month == month && date.year == year);}
        bool operator<(DBDate &date)
		{
			if (year == date.year) {
				if (month == date.month)
				    return day < date.day;
				return month < date.month;
			}
			return year < date.year;
		}
        bool operator>(DBDate &date)
		{
			if (year == date.year) {
				if (month == date.month)
				    return day > date.day;
				return month > date.month;
			}
			return year > date.year;
		}
        bool operator<=(DBDate &date)
		{
			if (year == date.year) {
				if (month == date.month)
				    return day <= date.day;
				return month < date.month;
			}
			return year < date.year;
		}
        bool operator>=(DBDate &date)
		{
			if (year == date.year) {
				if (month == date.month)
				    return day >= date.day;
				return month > date.month;
			}
			return year > date.year;
		}
		bool operator!=(DBDate &date){return day != date.day || month != date.month || year != date.year;}
        DBDate &operator+=(int days)
		{
			while (days != 0) {
				if (day == arrDays[month]) {
				    if (month == 12) {
				        year++;
				        month = 1;
				    } else {
				        if (IsLeapYear(year) && month == 2) {
				            if (--days == 0) {
				                day = 29;
				                break;
				            }
				        }
				        month++;
				    }
				    day = 1;
				} else
				    day++;
				days--;
			}
        return *this;
		}
        DBDate &operator-=(int days)
		{
			while (days != 0) {
				if (day == 1) {
				    if (month == 1) {
				        year--;
				        month = 12;
				        day = arrDays[month];
				    } else {
				        if (--month == 2 && IsLeapYear(year))
				            day = 29;
				        else
				            day = arrDays[month];
				    }
				} else
				    day--;
				days--;
			}
			return *this;
		}
        int operator-(DBDate &date);
    };

	enum TableDataType
	{
		NoType,
		Int32,
		Double,
		String,
		Date
	};

	enum Condition
	{
		Undefined,
		Equal,
		NotEqual,
		Less,
		Greater,
		LessOrEqual,
		GreaterOrEqual
	};

	const int LENGTH = 24;
	const int DELTA = 20;

	struct ColumnDesc
	{ 
		char colName[LENGTH];//им€ столбца
		TableDataType colType;//тип данных в столбце таблицы
		int length; //максимальное число символов в текстовом представлении 
		ColumnDesc(){};
		ColumnDesc( char * name, TableDataType type, int len)
		{ 
			strcpy_s(colName,name);
			colType=type;
			length=len; 
		} 
	}; 

	struct Strip
	{
		int nField;//число полей 
		int* fieldWidth;//ширина полей в полосе (массив)
	};

	

	typedef map<string, void*> Row;//тип данных в строке
	typedef map<string, ColumnDesc> Header;//тип заголовка

	void* GetValue(string value, string columnName, Header hdr)
	{
		switch (hdr[columnName].colType) {
            case Int32:
                return (int *) (new int(stoi(value)));
            case String:
                return (string *) (new string(value));
            case Double:
                return (double *) (new double(stod(value)));
            case Date:
                return (DBDate *) (new DBDate(value));
            case NoType:
                return (string *) (new string(value));
            default:
                return 0;
        }
	}
	bool comparator(TableDataType type, void *obj1, void *obj2, Condition cond) {
        switch (type) {
            case Int32:
                switch (cond) {
                    case Equal:
                        return *((int *) obj1) == *((int *) obj2);
                    case NotEqual:
                        return *((int *) obj1) != *((int *) obj2);
                    case Less:
                        return *((int *) obj1) < *((int *) obj2);
                    case Greater:
                        return *((int *) obj1) > *((int *) obj2);
                    case LessOrEqual:
                        return *((int *) obj1) <= *((int *) obj2);
                    case GreaterOrEqual:
                        return *((int *) obj1) >= *((int *) obj2);
                    case Undefined:
                        return false;
                }
            case String:
                switch (cond) {
                    case Equal:
                        return *((string *) obj1) == *((string *) obj2);
                    case NotEqual:
                        return *((string *) obj1) != *((string *) obj2);
                    case Less:
                        return *((string *) obj1) < *((string *) obj2);
                    case Greater:
                        return *((string *) obj1) > *((string *) obj2);
                    case LessOrEqual:
                        return *((string *) obj1) <= *((string *) obj2);
                    case GreaterOrEqual:
                        return *((string *) obj1) >= *((string *) obj2);
                    case Undefined:
                        return false;
                }
            case Double:
                switch (cond) {
                    case Equal:
                        return *((double *) obj1) == *((double *) obj2);
                    case NotEqual:
                        return *((double *) obj1) != *((double *) obj2);
                    case Less:
                        return *((double *) obj1) < *((double *) obj2);
                    case Greater:
                        return *((double *) obj1) > *((double *) obj2);
                    case LessOrEqual:
                        return *((double *) obj1) <= *((double *) obj2);
                    case GreaterOrEqual:
                        return *((double *) obj1) >= *((double *) obj2);
                    case Undefined:
                        return false;
                }
            case Date:
                switch (cond) {
                    case Equal:
                        return *((DBDate *) obj1) == *((DBDate *) obj2);
                    case NotEqual:
                        return *((DBDate *) obj1) != *((DBDate *) obj2);
                    case Less:
                        return *((DBDate *) obj1) < *((DBDate *) obj2);
                    case Greater:
                        return *((DBDate *) obj1) > *((DBDate *) obj2);
                    case LessOrEqual:
                        return *((DBDate *) obj1) <= *((DBDate *) obj2);
                    case GreaterOrEqual:
                        return *((DBDate *) obj1) >= *((DBDate *) obj2);
                    case Undefined:
                        return false;
                }
        }
        return false;
    }

	class DBTable
	{
	public:
		DBTable(){};
		TableDataType GetType(char* columnName);
		const char* TypeName(TableDataType type);
		virtual Header GetHeader() = 0;
		virtual vector<int> IndexOfRecord(void* keyValue,string keyColumnName)=0;
		virtual Row GetRow(int index) = 0;
		virtual Row operator[](int index) = 0;
		virtual string valueToString(Row& row,string columnName) = 0;
		virtual int GetSize() = 0;
		virtual ~DBTable(){};
		virtual void SetHeader(Header& hdr) = 0;
		virtual void ReadDBTable(string fileName) = 0;											
		virtual void WriteDBTable(string fileName) = 0;
		virtual void SetTableName(string tName) = 0;
		virtual void SetPrimaryKey(string key) = 0;
		virtual string GetTableName() = 0;
		virtual string GetPrimaryKey() = 0;
		virtual void SetFileName(string path) = 0;
		virtual string GetFileName() = 0;
		virtual void PrintTable(int screenWidth) = 0;
		virtual Row CreateRow() = 0;
		virtual void AddRow(Row row,int index) = 0;
		virtual DBTable* SelfRows(string colName,Condition cond, void* value) = 0;
	};


	class DBTableTxt : public DBTable {
    private:
        Header columnHeaders;
        string primaryKey;
        vector<Row> data;
        string tableName;
        string fileName;
        void CreateTableMaket(Strip *&strips, int &nStrips, int screenWidth)
		{
			Header::iterator iter, iterWhile;
			iter = columnHeaders.begin();
			int sum = 0, j;
			while (iter != columnHeaders.end()) {
			    if (iter->first.length() > iter->second.length)
			        sum += iter->first.length() + 3;
			    else
			        sum += iter->second.length + 3;
			    iter++;
			}
			nStrips = sum / screenWidth;
			strips = new Strip[++nStrips];
			iter = columnHeaders.begin();
			int len;
			for (int i = 0; i < nStrips; i++) {
				strips[i].nField = 0;
				strips[i].fieldWidth = new int[columnHeaders.size()];
				sum = 0, j = 0;
				do {

					if (iter->first.length() > iter->second.length)
					    len = iter->first.length() + 3;
					else
					    len = iter->second.length + 3;
			        strips[i].fieldWidth[j] = len;
			        j++;
			        sum += len;
			        iter++;
			        strips[i].nField++;
			    } while (sum + len <= screenWidth && iter != columnHeaders.end());
			}
		}

    public:
        DBTableTxt() {}
        DBTableTxt(string tabName) : tableName(tabName) {}
        DBTableTxt(string tabName, Header hdr, string primKey) : tableName(tabName), columnHeaders(hdr),
                                                                           primaryKey(primKey) {}
        ~DBTableTxt() {}
		TableDataType GetType(char* columnName);
        string valueToString(Row &row, string columnName)
		{
			stringstream ss;
			void *ptr = row[columnName];
			switch (columnHeaders[columnName].colType) {
			    case String:
			        return *((string *) ptr);
			    case Int32:
			        ss << *((int *) ptr);
			        return ss.str();
			    case Double:
			        ss << *((double *) ptr);
			        return ss.str();
			    case Date:
			        ss << *((DBDate *) ptr);
			        return ss.str();
			    default:
			        return *((string *) ptr);
			}
		}
		Header GetHeader()
		{
			return columnHeaders;
		}
        void ReadDBTable(string fileName)
		{
			stringstream ss;
			ifstream in(fileName);
			if (!in.is_open()) {
			    cout << "Error while opening file" << endl;
			    return;
			}
			char buf[1024];
			char delims[] = "|\n\r";
			in.getline(buf, 100);
			char *token, *next_token;
			next_token = buf;
			tableName = strtok_s(next_token, delims, &next_token);
			primaryKey = strtok_s(next_token, delims, &next_token);
			columnHeaders.clear();
			in.getline(buf, 200);
			next_token = buf;
			vector<ColumnDesc> stdArray;
			ColumnDesc colHdr;

			while (token = strtok_s(next_token, delims, &next_token))
			{
			    strcpy(colHdr.colName, token);
			    token = strtok_s(next_token, delims, &next_token);
			    if (strcmp(token, "Int32") == 0)
			        colHdr.colType = Int32;
			    else if (strcmp(token, "String") == 0)
			        colHdr.colType = String;
			    else if (strcmp(token, "Double") == 0)
			        colHdr.colType = Double;
			    else if (strcmp(token, "DBDate") == 0)
			        colHdr.colType = Date;
			    else
			        colHdr.colType = NoType;
			    token = strtok_s(next_token, delims, &next_token);
			    if (token)
			        colHdr.length = atoi(token);
					
				stdArray.push_back(colHdr);
			}
			Header hdr;
			for (unsigned int j = 0; j < stdArray.size(); j++) {
			    hdr[stdArray[j].colName] = stdArray[j];
			}
			SetHeader(hdr);
			data.clear();
			while (in.getline(buf, 200)) {
			    Row row = *(new Row());
			    int j = 0;
			    token = strtok_s(buf, delims, &next_token);
			    while (token) {
			        string value(token);
			        row[stdArray[j].colName] = GetValue(value, stdArray[j].colName, columnHeaders);
			        j++;
			        token = strtok_s(next_token, delims, &next_token);
			    }
			    data.push_back(row);
			}
		}
        void WriteTableBin(string fileName)
		{
			std::ofstream out(fileName, std::ios::binary);
			if (!out.is_open()) {
			    std::cout << "Error while opening file" << std::endl;
			    return;
			}
			int len = LENGTH;
			out.write((char *) &len, sizeof(int));
			char tabName[LENGTH];
			strcpy(tabName, tableName.c_str());
			out.write(tabName, LENGTH);
			out.write((char *) &len, sizeof(int));
			char primKey[LENGTH];
			strcpy(primKey, primaryKey.c_str());
			out.write(primKey, LENGTH);
			int nColumn = columnHeaders.size();
			int nRows = data.size();
			ColumnDesc *header = new ColumnDesc[nColumn];
			Header::iterator iter;
			iter = columnHeaders.begin();
			for (int j = 0; j < nColumn; j++) {
			    strcpy(header[j].colName, iter->second.colName);
			    header[j].length = iter->second.length;
			    header[j].colType = iter->second.colType;
			    iter++;
			}
			out.write((char *) &nColumn, sizeof(int));
			out.write((char *) header, nColumn * sizeof(ColumnDesc));
			out.write((char *) &nRows, sizeof(int));
			//int i = 0;
			void *ptr;
			for (int i = 0; i < nRows; i++) {
			    iter = columnHeaders.begin();
			    while (iter != columnHeaders.end()) {
			        ptr = data[i][iter->first];
			        switch (iter->second.colType) {
			            case Int32:
			                out.write((char *) ptr, sizeof(int));
			                break;
			            case String:
			                out.write(((std::string *) ptr)->c_str(), iter->second.length);
			                break;
			            case Double:
			                out.write((char *) ptr, sizeof(double));
			                break;
			            case Date:
			                out.write((char *) ptr, sizeof(DBDate));
			        }
			        iter++;
			    }
			}
		    out.close();
		}
        void WriteDBTable(string fileName)
		{
			ofstream out(fileName);
			out << tableName << '|' << primaryKey << endl;
			string typeNames[] = {
			        "NoType",
			        "Int32",
			        "Double",
			        "String",
			        "DBDate"
			};
			Header::iterator iter;
			iter = columnHeaders.begin();
			while (iter != columnHeaders.end()) {
			    out << iter->first << '|' << typeNames[iter->second.colType] << '|' << iter->second.length << '|';
			    iter++;
			}
			out.seekp(out.tellp());// - (long) 1);
			out << endl;
			for (int i = 0; i < data.size(); i++) {
			    iter = columnHeaders.begin();
			    while (iter != columnHeaders.end()) {
			        out << valueToString(data[i], iter->first) << '|';
			        iter++;
			    }
			    out.seekp(out.tellp());// - (long) 1);
			    out << endl;
			}
			out.close();
		}
        void PrintTable(int screenWidth)
		{
			Strip *strips;
			int nStrips;
			int k = 0;
			string typeNames[] = {
			        "NoType",
			        "Int32",
			        "Double",
			        "String",
			        "Date"
			};
			Header::iterator iter, iterWhile, iter1;
			cout << "Table " << tableName << endl;
			CreateTableMaket(strips, nStrips, screenWidth);
			iter = columnHeaders.begin();
			iterWhile = iter;
			for (int i = 0; i < nStrips; i++) {
			    cout << setw(screenWidth + 1) << setfill('=') << '\n' << flush;
			    for (int j = 0; j < strips[i].nField; j++) {
			        cout << setfill(' ') << setw(strips[i].fieldWidth[j]) << iterWhile->second.colName;
			        iterWhile++;
			    }
			    cout << endl;
			    iterWhile = iter;
			    for (int j = 0; j < strips[i].nField; j++) {
			        cout << setfill(' ') << setw(strips[i].fieldWidth[j])
			                  << typeNames[iterWhile->second.colType];
			        iterWhile++;
			    }
			    cout << endl << setw(screenWidth + 1) << setfill('-') << '\n' << flush;

				for (int j = 0; j < data.size(); j++) {
				    iter1 = iter;
				    for (k = 0; k < strips[i].nField; k++) {
				        cout << setw(strips[i].fieldWidth[k]) << setfill(' ')
				                  << valueToString(data[j], iter1->second.colName);
				        iter1++;
				    }
				    cout << endl;
				}
				cout << setw(screenWidth + 1) << setfill('=') << '\n' << endl;
				iter = iterWhile;
			}		
			for (int i = 0; i < nStrips; i++) {
				delete[](strips[i].fieldWidth);
			}
			delete[] strips;
			cout << setfill(' ');
		}

		void SetHeader(Header &hdr){columnHeaders = hdr;}
		void SetTableName(string tName){tableName = tName;}
		void SetPrimaryKey(string key){primaryKey = key;}
		void SetFileName(string path){fileName = path + tableName + ".txt";}
		string GetTableName(){return tableName;}
		string GetPrimaryKey(){return primaryKey;}
		string GetFileName(){return fileName;}
		Row GetRow(int index){return data[index];}
		Row operator[](int index){return data[index];}
        Row CreateRow()
		{
			Header::iterator iter;
			string s;
			Row row;
			iter = columnHeaders.begin();
			while (iter != columnHeaders.end()) {
			    cout << "¬ведите столбец " << iter->first << ' ' << endl;
			    cin >> s;
			    getline(cin, s);
			    row[iter->first] = GetValue(s, iter->first, columnHeaders);
			    iter++;
			}
			return row;
		}
        void AddRow(Row row, int index)
		{
			if ( index < data.size() )
			    data[index] = row;
			else
			    data.push_back(row);
		}
        void DeleteRow(int index)
		{
			vector<Row>::iterator iter;
			iter = data.begin();
			for (int i = 0; i < index - 1; i++)
			    iter++;
			data.erase(iter);
		}
        void DBTableClear()
		{
			data.clear();
			columnHeaders.clear();
			tableName = "";
			primaryKey = "";
			fileName = "";
		}
		int GetSize(){return data.size();}
        DBTable *SelfRows(string colName, Condition cond, void *value)
		{
			DBTable *tab = new DBTableTxt(tableName, columnHeaders, primaryKey);
			Row val;
			int k = 0;
			for (int i = 0; i < data.size(); i++) {
			    val = data[i];
			    if (comparator(columnHeaders[colName].colType, val[colName], value, cond)) {
			        tab->AddRow(val, k);
			        k++;
			    }
			}
			return tab;
		}
        vector<int> IndexOfRecord(void *keyValue, string keyColumnName)
		{
			vector<int> tmp;
			Row val;
			for (int i = 0; i < data.size(); i++) {
			    val = data[i];
			    if (comparator(columnHeaders[keyColumnName].colType, val[keyColumnName], keyValue, Equal)) {
			        tmp.push_back(i);
			    }
			}
			return tmp;
		}
		friend void ReadDBTable1(DBTableTxt& tab,string tabName);//tabName=path+tableName
		friend void WriteDBTable1(DBTableTxt& tab,string tabName);
		friend void PrintTable1(DBTableTxt& tab,int screenWidth);
		friend void WriteTableBin1(DBTableTxt& tab, string tabName);
		friend void ReadTableBin1(DBTableTxt& tab,string tabName);
    };

	class DBTableBin : public DBTable {
    private:
        char tabName[LENGTH];
        char primaryKey[LENGTH];
        char filName[80];
        int nColumn;
        ColumnDesc *header;
        int nRows;
        char **data;
        int maxRows;

        int RowLength();

        int DataBegin();

        int FieldPosition(string colName);

        int FieldLength(string colName);

        void ResizeData(int deltaRows)
		{
			maxRows += deltaRows;
			char **dataTmp = new char *[maxRows];
			for (int i = 0; i < nRows; i++)
			    dataTmp[i] = data[i];
			delete[] data;
			data = dataTmp;
		}

        void CreateTableMaket(Strip *&strips, int &nStrips, int screenWidth)
		{
			Header columnHeaders = GetHeader();
			Header::iterator iter, iterWhile;
			iter = columnHeaders.begin();
			int sum = 0, j;
			while (iter != columnHeaders.end()) {
			    if (iter->first.length() > iter->second.length)
			        sum += iter->first.length() + 3;
			    else
			        sum += iter->second.length + 3;
			    iter++;
			}
			nStrips = sum / screenWidth;
			strips = new Strip[++nStrips];
			iter = columnHeaders.begin();
			int len;
			for (int i = 0; i < nStrips; i++) {
				strips[i].nField = 0;
				strips[i].fieldWidth = new int[columnHeaders.size()];
				sum = 0, j = 0;
				do {

					if (iter->first.length() > iter->second.length)
					    len = iter->first.length() + 3;
					else
					    len = iter->second.length + 3;
			        strips[i].fieldWidth[j] = len;
			        j++;
			        sum += len;
			        iter++;
			        strips[i].nField++;
			    } while (sum + len <= screenWidth && iter != columnHeaders.end());
			}
		}

    public:
        DBTableBin() {}

        DBTableBin(string tName, Header hdr, string primKey)
		{
			strcpy(tabName, tName.c_str());
			SetHeader(hdr);
			strcpy(primaryKey, primKey.c_str());
			nRows = 0;
		}

        ~DBTableBin() {}

        int GetSize() { return nRows; }

		void SetTableName(string tName){ strcpy(tabName, tName.c_str()); }

        Header GetHeader()
		{
			Header hdr;
			for (int i = 0; i < nColumn; i++) {
			    hdr[header[i].colName] = header[i];
			}
			return hdr;
		}

        void SetHeader(Header &hdr)
		{
			Header::iterator iter;
			nColumn = hdr.size();
			iter = hdr.begin();
			header = new ColumnDesc[hdr.size()];
			for (int i = 0; i < nColumn; i++) {
			    strcpy(header[i].colName, iter->second.colName);
			    header[i].length = iter->second.length;
			    header[i].colType = iter->second.colType;
			    iter++;
			}
		}

        string valueToString(Row &row, string columnName)
		{
			stringstream ss;
			void *ptr = row[columnName];
			Header columnHeaders = GetHeader();
			switch (columnHeaders[columnName].colType) {
			    case String:
			        return *((string *) ptr);
			    case Int32:
			        ss << *((int *) ptr);
			        return ss.str();
			    case Double:
			        ss << *((double *) ptr);
			        return ss.str();
			    case Date:
			        ss << *((DBDate *) ptr);
			        return ss.str();
			    default:
			        return *((string *) ptr);
			}
		}

        Row operator[](int index)
		{
			Row *row = (Row *) data[index];
			return *row;
		}

        Row GetRow(int index)
		{
			Row *row = (Row *) data[index];
			return *row;
		}

        void ReadDBTable(string fileName)
		{
			ifstream in(fileName, ios::binary);
			if (!in.is_open()) {
			    cout << "Error while opening file" << endl;
			    return;
			}
			in.seekg(sizeof(int));
			in.read(tabName, LENGTH);
			in.seekg(sizeof(int), ios_base::cur);
			in.read(primaryKey, LENGTH);
			in.read((char *) &nColumn, sizeof(int));
			header = new ColumnDesc[nColumn];
			in.read((char *) header, nColumn * sizeof(ColumnDesc));
			in.read((char *) &nRows, sizeof(int));
			maxRows = nRows + DELTA;
			data = new char *[maxRows];
			int i, j;
			char *buf;
			string *bufstr;
			for (i = 0; i < nRows; i++) {
			    data[i] = new char[sizeof(Row)];
			    Row *row = new Row;
			    for (j = 0; j < nColumn; j++) {
			        switch (header[j].colType) {
			            case Int32:
			                buf = new char[sizeof(int)];
			                in.read(buf, sizeof(int));
			                (*row)[header[j].colName] = buf;
			                break;
			            case String:
			                buf = new char[header[j].length];
			                in.read(buf, header[j].length);
			                bufstr = new string(buf);
			                (*row)[header[j].colName] = bufstr;
			                break;
			            case Double:
			                buf = new char[sizeof(double)];
			                in.read(buf, sizeof(double));
			                (*row)[header[j].colName] = buf;
			                break;
			            case Date:
			                buf = new char[sizeof(DBDate)];
			                in.read(buf, sizeof(DBDate));
			                (*row)[header[j].colName] = buf;
			                break;
			        }
			    }
			    data[i] = (char *) row;
			}
			in.close();
		}

        void WriteDBTable(string fileName)
		{
			ofstream out(fileName, ios::binary);
			if (!out.is_open()) {
			    cout << "Error while opening file" << endl;
			    return;
			}
			int len = LENGTH;
			out.write((char *) &len, sizeof(int));
			out.write(tabName, LENGTH);
			out.write((char *) &len, sizeof(int));
			out.write(primaryKey, LENGTH);
			out.write((char *) &nColumn, sizeof(int));
			out.write((char *) header, nColumn * sizeof(ColumnDesc));
			out.write((char *) &nRows, sizeof(int));
			int i = 0, j;
			Row *row;
			void *ptr;
			for (i = 0; i < nRows; i++) {
			    row = (Row *) data[i];
			    for (j = 0; j < nColumn; j++) {
			        ptr = (*row)[header[j].colName];
			        switch (header[j].colType) {
			            case Int32:
			                out.write((char *) ptr, sizeof(int));
			                break;
			            case String:
			                out.write(((string *) ptr)->c_str(), header[j].length);
			                break;
			            case Double:
			                out.write((char *) ptr, sizeof(double));
			                break;
			            case Date:
			                out.write((char *) ptr, sizeof(DBDate));
			                break;
			        }
			    }
			}
			out.close();
		}

        void PrintTable(int screenWidth)
		{
			Strip *strips;
			int nStrips;
			int k = 0;
			string typeNames[] = {
			        "NoType",
			        "Int32",
			        "Double",
			        "String",
			        "DBDate"
			};
			Header columnHeaders = GetHeader();
			Header::iterator iter, iterWhile, iter1;
			cout << "Table " << tabName << endl;
			CreateTableMaket(strips, nStrips, screenWidth);
			iter = columnHeaders.begin();
			iterWhile = iter;
			for (int i = 0; i < nStrips; i++) {
			    cout << setw(screenWidth + 1) << setfill('=') << '\n' << flush;
			    for (int j = 0; j < strips[i].nField; j++) {
			        cout << setfill(' ') << setw(strips[i].fieldWidth[j]) << iterWhile->second.colName;
			        iterWhile++;
			    }
			    cout << endl;
			    iterWhile = iter;
			    for (int j = 0; j < strips[i].nField; j++) {
			        cout << setfill(' ') << setw(strips[i].fieldWidth[j])
			                  << typeNames[iterWhile->second.colType];
			        iterWhile++;
			    }
			    cout << endl << setw(screenWidth + 1) << setfill('-') << '\n' << flush;
					
			    for (int j = 0; j < nRows; j++) {
			        iter1 = iter;
			        for (k = 0; k < strips[i].nField; k++) {
			            cout << setw(strips[i].fieldWidth[k]) << setfill(' ')
			                      << valueToString(*((Row *) data[j]), iter1->second.colName);
			            iter1++;
			        }
			        cout << endl;
			    }
			    cout << setw(screenWidth + 1) << setfill('=') << '\n' << endl;
			    iter = iterWhile;
			}
			for (int i = 0; i < nStrips; i++) {
			    delete[](strips[i].fieldWidth);
			}
			delete[] strips;
			cout << setfill(' ');
		}

        void SetPrimaryKey(string key)
		{
			strcpy(primaryKey, key.c_str());
		}

        string GetTableName(){ return string(tabName); }

		string GetPrimaryKey(){ return string(primaryKey); }

        void SetFileName(string path)
		{
			strcpy(filName, (path + tabName + ".bin").c_str());
		}

		string GetFileName(){ return string(filName); }

        Row CreateRow()
		{
			int i;
			Row row;
			string s;
			Header hdr = GetHeader();
			Header::iterator iter;
			iter = hdr.begin();
			while (iter != hdr.end()) {
			    cout << "¬ведите столбец " << iter->first << ": ";
			    //getline(cin, s);
				cin >> s;
			    row[iter->first] = GetValue(s, iter->first, hdr);
			    iter++;
			}
			return row;
		}

        void AddRow(Row row, int index)
		{
			if (nRows == maxRows)
			   ResizeData(DELTA);
			if (index > nRows)
			    index = nRows;
			else
			    nRows++;
			Row *row1 = new Row(row);
			//delete[] data[index];
			data[index] = (char *) row1;
		}

        void DeleteRow(int index)
		{
			delete[] data[index];
			nRows--;
		}

        DBTable *SelfRows(string colName, Condition cond, void *value)
		{
			Header hdr = GetHeader();
			string s1(tabName), s2(primaryKey);
			DBTable *tab = new DBTableBin(s1, hdr, s2);
			Row val;
			int k = 0;
			for (int i = 0; i < nRows; i++) {
			    val = this->GetRow(i);
			    if (comparator(hdr[colName].colType, val[colName], value, cond)) {
			        tab->AddRow(val, k);
			        k++;
			    }
			}
			return tab;
		}

        vector<int> IndexOfRecord(void *keyValue, string keyColumnName)
		{
			Header hdr = GetHeader();
			vector<int> tmp;
			Row val;
			for (int i = 0; i < nRows; i++) {
			    val = this->GetRow(i);
			    if (comparator(hdr[keyColumnName].colType, val[keyColumnName], keyValue, Equal)) {
			        tmp.push_back(i);
			    }
			}
			return tmp;
		}
    };

	struct Relation 
	{
		string relationName;
		string parentTable;
		string parentPrimaryKey;
		string childTable;
		string childSecondaryKey;
	};

		void PrintRow(Row row, DBTable *tab);

	class DBTableSet {
    private:
        string dbName;
        map<string, DBTable *> db;
    public:
        DBTableSet() {};

		DBTableSet(string name){ dbName = name; }

        int ReadDB()
		{
			DBTable *tab;
			ifstream in("..\\"+dbName + "\\DBTables.txt");
			if (!in.is_open())
			    return 0;
			char buf[1024];
			char delims[] = "|\r\n";
			char *token, *next_token;
			string tabName;
			in.getline(buf, 80);
			next_token = buf;
			string dbType = dbName.substr(dbName.size() - 3, 3);
			while (token = strtok_s(next_token, delims, &next_token)) {
			    if (dbType == "Bin")
			        tab = new DBTableBin();
			    else if (dbType == "Txt")
			        tab = new DBTableTxt();
			    else {
			        in.close();
			        return 0;
			    }
				if (dbType == "Bin")
			        tab->ReadDBTable("..\\"+dbName + "\\" + token + ".bin");
			    else if (dbType == "Txt")
			        tab->ReadDBTable("..\\"+dbName + "\\" + token + ".txt");
			    //tab->ReadDBTable("..\\"+dbName + "\\" + token + ".txt");
			    tabName = token;
			    //tabName = tabName.substr(0, tabName.length()-4);
			    db[tabName] = tab;
			}
			in.close();
			return 1;
		}

        void PrintDB(int numcol)
		{
			auto iter = db.begin();
			while (iter != db.end()) {
			    iter->second->PrintTable(numcol);
			    iter++;
			}
		}

        void WriteDB()
		{
			string dbType = dbName.substr(dbName.size() - 3, 3);
			if(dbType == "Bin")
			    dbType = ".bin";
			else if(dbType == "Txt")
			    dbType = ".txt";
			else
			    return;
			string tabType;
			ofstream out("..\\"+dbName + "\\DBTables.txt");
			if (!out.is_open()) {
			    cout << "Error opening file" << endl;
			    return;
			}
			for (auto iter = db.begin(); iter != db.end(); iter++) {
			    iter->second->WriteDBTable(dbName + '/' + iter->first + dbType);
			    out << iter->first << '|';
			}
			out.seekp(out.tellp());
			out << endl;
			out.close();
		}

        string GetDBName() { return dbName; }

		DBTable *operator[](string tableName){ return db[tableName]; }

        Relation GetRelation(string relationName);

        Row ParentRow(Relation &relation, Row &childRow);

        DBTable *ChildRows(Relation &relation, Row &parentRow);
    };
}



#endif //HEAD