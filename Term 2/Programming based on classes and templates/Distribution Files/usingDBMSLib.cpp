#include "dbmsLib_v2_2.h"
using namespace std;
//namespace dbmsLib
//{
dbmsLib::DBDate nulDate("1.1.1");
//--------------------------------------------------
string TabNameExtension(string dbName){
	char buf[8];
	strcpy_s(buf,8,dbName.c_str()+dbName.size()-3);
	if(!strcmp("Bin",buf))
		return ".bin";
	else if(!strcmp("Txt",buf))
		return ".txt";
	else
		cout<<"TabNameExtension(): Ошибка в имени БД "<<dbName<<endl;
	system("pause");
	return dbName;	
}
//===========================================
/*Оформление заказа на отпуск товаров со склада. 
Добавить запись в таблицу Orders и по одной записи на каждый
продукт в заказе в таблицу OrderDetails и сделать необходимые 
изменения в таблице Products. 
Перед перед записью в таблицу OrderDetails сделать проверку 
наличия продуктов на складе.
*/
void ExecuteOrder(dbmsLib::DBTableSet& db,int screenWidth)
{ //Оформление одного заказа из нескольких продуктов
	//	string tabName = "Products";
	string dbName = db.GetDBName();
	string path="..\\"+dbName+"\\";
	dbmsLib::Row row=db["Orders"]->CreateRow();
	//Проверка существования введенного в row клиента 
	if((*db["Customers"]).IndexOfRecord(row["CustomerID"],"CustomerID").size()==0){
		cout<<"В БД нет данных о клиенте "<<*(string*)row["CustomerID"]<< endl;
		system("pause");
		return;
	}
	db["Orders"]->AddRow(row,db["Orders"]->GetSize());//запись заказа в таблицу
	db["Orders"]->PrintTable(screenWidth);//для информации при 
	db["Products"]->PrintTable(screenWidth);//оформлении заказа
	bool isContinue=false;
	do{
		row=db["OrderDetails"]->CreateRow();
		//Контроль и изменение количества товара на складе
		dbmsLib::Header::iterator it;
		vector<int> indexes=db["Products"]->IndexOfRecord(row["ProductID"],"ProductID");
		//Проверка существования в БД введенного в row продукта
		if(indexes.size()==0){
			cout<<"В БД нет данных о продукте  "<<*(string*)row["ProductID"]<< endl;
			system("pause");
			return;
		}
		for(int i=0;i<indexes.size();i++){
			if((*(int*)(*db["Products"])[indexes[i]]["UnitInStock"])>=*(int*)row["Quantity"]){
				*(int*)(*db["Products"])[indexes[i]]["UnitInStock"]-=*(int*)row["Quantity"];
				db["OrderDetails"]->AddRow(row,db["OrderDetails"]->GetSize());				
			}
			else{
				cout<<"Заказ не может быть выполнен, т.к. на складе только "<<
					*(int*)(*db["Products"])[indexes[i]]["UnitInStock"]
				<<" единиц товара "<<*(string*)row["ProductID"]<<endl;
				system("pause");
				return;
			}
		}
		//записываем изменения количества товара row["ProductID"] в файл с таблицей db["Products"],
		//используя прямой доступ к данным в файле (для иллюстрации прямого доступа к файлу).
		/*int pos=db["Products"].DataBegin()+indexes[0]*db["Products"].RowLength()+
		db["Products"].FieldPosition(string("UnitInStock"));*/
		//int pos=db["Products"]->FieldPosInFile(indexes[0],"UnitInStock");
		//	fInOut.seekp(pos);
		//	fInOut.write((char*)(int*)row["Quantity"],sizeof(int));		
		cout<<"Продолжить заказ? 1/0\n";
		cin>>isContinue;
	}while(isContinue);
	//	fInOut.close();
	db["OrderDetails"]->PrintTable(screenWidth);
	db["Products"]->PrintTable(screenWidth);

	//Записываем в БД изменения в таблицах "Orders","OderDetails" и "Products"
	/*db["Orders"]->WriteDBTable("..\\CompanyBin\\Orders.bin");
	db["OrderDetails"]->WriteDBTable("..\\CompanyBin\\OrderDetails.bin");
	db["Products"]->WriteDBTable("..\\CompanyBin\\Products.bin");*/
	db.WriteDB();
}
//---------------------------------------
/*Возвращает список книг, находяшихся на руках у студента,
или таблицу студентов, если данного студента нет в списке.
*/
dbmsLib::DBTable* StudentBooksList(dbmsLib::DBTableSet& db,int screenWidth)
{
	dbmsLib::Relation relation=db.GetRelation("StudentsAbonements");
	cout<<"Введите имя студента\n";
	string name;
	cin>>name;
	//cout<<"Введите StudentID\n";
	/*int id;
	cin>>id;
	Row selectRow;
	DBTable* selectStudents=db[relation.parentTable]->SelfRows("StudentID",Equal,&id);

	*/
	dbmsLib::Row selectRow;
	dbmsLib::DBTable* selectStudents=db[relation.parentTable]->SelfRows("Name",dbmsLib::Equal,&name);
	int studentID = -1;	
	selectStudents->PrintTable(screenWidth);
	cout<<"Введите ID студента или -1, если студента нет в списке\n";
	cin>>studentID;	
	vector<int> indexes=selectStudents->IndexOfRecord(&studentID,"StudentID");
	if(indexes.size() == 0){
		cout<<"Студент "<< name<<" StudentID= "<<studentID<<" не записан в библиотеку\n";
		return db["Students"];
	}
	selectRow=(*selectStudents)[indexes[0]];
	dbmsLib::DBTable* childRowsStAb=db.ChildRows(relation,selectRow);
	cout<<"Студент "<< name<<" StudentID= "<<studentID<<" брал книги:"<<endl;
	childRowsStAb->PrintTable(screenWidth);
	cout<<"На руках у студента "<< name<<":"<<endl;
	dbmsLib::DBTableBin booksAbSt("BooksAbSt",db["Books"]->GetHeader(),db["Books"]->GetPrimaryKey());
	indexes=childRowsStAb->IndexOfRecord(&nulDate,"DateOut");
	for(int i=0;i<indexes.size();i++)
		booksAbSt.AddRow(db.ParentRow(db.GetRelation("BooksAbonements"),(*childRowsStAb)[indexes[i]]),
		booksAbSt.GetSize());
	if(booksAbSt.GetSize()==0)
		cout<<"книг нет."<<endl;
	else
		booksAbSt.PrintTable(screenWidth);
	return &booksAbSt;
}
//----------menu( )---------------------------------  
int menu(string dbName,dbmsLib::DBDate today) 
{
	int action;
	cout<<"\n БД "<<dbName<< "\t Сегодня "<<today<< endl;
	cout<<"======= Практикум по программированию. Вариант 0 =======\n";
	cout<<"1 - чтение БД из файла\t\t 4 - тестирование \n";
	cout<<"2 - печать всех таблиц БД\t 5 - запись таблиц БД в файл\n";
	cout<<"3 - запись таблицы в файл\t 6 - список книг студента\n";
	cout<<"7 - выдача книг студенту\t 9 - чтение таблицы из файла\n"; 
	cout<<"10 - печать таблицы\t\t11 - изменение цены товара Hot Dog\n"; 
	cout<<"12 - отпуск товаров со склада\t13 - запись .txt-таблицы в .bin-файл\n"; 
	cout<<"14 - чтение в .txt-таблицу из .bin-файла\n";
	cout<<"\t\t\t8 - выход\n";
	cout<<"===========================================================\n";
	cout<<("Введите номер операции\n");
	cin>>action;
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(10,'\n');					
		cout<<("Ошибка формата. Повторите ввод номера операции\n");
		cin>>action;
	}			
	return action;
}
//=====================================================
void IncreasePriceHotDogBin(dbmsLib::DBTableSet& db){//!!!нужна ссылка, чтобы передать
	//изменения из функции в таблицу БД, а не в ее копию.
	//Прямой доступ к записям таблиц БД в файлах, без использования DBTableBin
	/*Структура двоичного файла с таблицей:
	длина имени таблицы - 4 байта
	имя таблицы - 24 байта;
	длина имени столбца primaryKey - 4 байта
	имя primaryKey - 24 байта;
	число столбцов в заголовке таблицы (nColumn) - 4 байта;
	Итого: начало заголовка таблицы - 60 байт;
	заголовок таблицы - nColumn*sizeof(ColumnDesc)= nColumn*72 байт;
	адрес первой записи - 60 + 72*nColumn + sizeof(int); //sizeof(int) - 
	это nRows.
	*/
	/*
	1. Сначала "вручную" делаем программу "Увеличить на 1.5 цену продукта Hot Dog",
	имея ввиду возможность использования её фрагментов для изменения полей в других
	табличных файлах БД, имеющих такую же структуру.
	2. Затем выделяем структуры данных и функции с целью повторного использования 
	для прямого доступа к полям других таблиц и отлаживаем их на примере программы
	"Увеличить на 1.5 цену продукта Hot Dog".
	3. Тестируем созданные структуры данных и функции на примерах изменения полей 
	в других табличных файлах БД, имеющих такую же структуру. 
	*/
	//1. Увеличить на 1.5 цену продукта Hot Dog 
	string tabName = "Products";
	string dbName = "CompanyBin";
	string path="..\\"+dbName+"\\";
	fstream fInOut;//открытие файлового потока на ввод-вывод
	fInOut.open((path+tabName+".bin").c_str(),ios::binary|ios::in|ios::out);
	if (!fInOut.is_open())	{ 
		cout<<"Ошибка открытия файла\n"<< endl; 
		system("pause");
		return;
	}
	char primaryKey[dbmsLib::LENGTH+1];
	fInOut.seekg(2*sizeof(int)+dbmsLib::LENGTH);		
	fInOut.read((char*)primaryKey,dbmsLib::LENGTH);
	primaryKey[dbmsLib::LENGTH]='\0';
	string primKey(primaryKey);
	int hdrSize=0;
	fInOut.read((char*)&hdrSize,sizeof(int));
	//Прочитать из файла заголовок таблицы и записать его в table.columnHeaders
	dbmsLib::ColumnDesc colDesc;
	dbmsLib::Header hdr;
	dbmsLib::Header::iterator hdrIter;
	//вычисление длины строки таблицы в байтах и
	//смещения от начала строки столбца primaryKey
	int rowLength=0;
	int primaryKeyBegin=0;
	int primaryKeyLength=0;
	for(int i=0; i<hdrSize; i++){
		fInOut.read((char*)&colDesc,sizeof(dbmsLib::ColumnDesc));
		hdr[colDesc.colName]=colDesc;//глубокое копирование
		//(в map<string,ColumnDesc> перегружена операция = )
		if(colDesc.colName==(string)primaryKey){
			primaryKeyBegin=rowLength;
			primaryKeyLength=GetLength(colDesc);
		}
		rowLength += GetLength(colDesc);
	}
	int nRows;//число строк в таблице
	fInOut.read((char*)&nRows,sizeof(int));
	int headerBegin = sizeof(int)*2 + dbmsLib::LENGTH*2 + sizeof(int);
	int dataBegin = headerBegin + sizeof(dbmsLib::ColumnDesc)*hdrSize + sizeof(int);
	cout<<"Параметры таблицы "<<tabName<<":\n";
	cout<<"Число столбцов hdrSize="<<hdrSize<<"  Число строк nRows="<<nRows<<endl;
	cout<<"rowLength="<<rowLength<<" байт; primaryKeyBegin="<<primaryKeyBegin<<
		" байт; primaryKeyLength= "<<primaryKeyLength<<" байт\n";		
	cout<<"headerBegin = "<<headerBegin<<" байт\n";
	cout<<"dataBegin = "<<dataBegin<<" байт\n";
	//Поиск в файле прямого доступа строки с ключом ProductID == "Hot Dog"
	dbmsLib::Row row;
	dbmsLib::Row::iterator rowIter;
	char buf[200];//буфер на строку таблицы

	int i=0;//порядковый номер строки "Hot Dog" в таблице "Products"
	for (i = 0; i < nRows; i++)
	{
		fInOut.seekg(dataBegin+i*rowLength+primaryKeyBegin);
		fInOut.read(buf,primaryKeyLength);
		buf[primaryKeyLength]='\0';
		if(!strcmp("Hot Dog",buf)){
			cout<<"i = "<<i<<" primaryKey = "<<buf<<endl;
			break;
		}
	}
	//определяем смещение поля "UnitPrice" в строке таблицы "Products"
	fInOut.seekg(dataBegin+i*rowLength);
	int unitPriceBegin=0;
	for(hdrIter=hdr.begin();hdrIter!=hdr.end();hdrIter++){
		if(hdrIter->first==(string)"UnitPrice")
			break;
		unitPriceBegin+=GetLength(hdrIter->second);
	}
	cout<<"unitPriceBegin="<<unitPriceBegin<<endl;
	//Вычисляем новую цену
	fInOut.seekg(dataBegin+i*rowLength+unitPriceBegin);
	double unitPrice=0;
	fInOut.read((char*)&unitPrice,sizeof(double));
	cout<<"oldPrice="<<unitPrice<<endl;
	unitPrice+=1.5;
	cout<<"newPrice="<<unitPrice<<endl;
	//записываем новую цену товара "Hot Dog" в файл БД.
	fInOut.seekp(dataBegin+i*rowLength+unitPriceBegin);
	fInOut.write((char*)&unitPrice,sizeof(double));
	fInOut.close();		
}
//=========================================
//Изменение цены товара в таблице и в файле с использованием прямого 
//доступа к данным в файле
void ChaingePrice(dbmsLib::DBTableSet &db, string tabName){
	//	DBTableBin products( tabName);//???будет нужна как буфер для восстановления
	//данных в случае ошибки перед записью изменений в db["Products"].
	//Будем делать проще: без буферизации, но с прямым доступом к данным при 
	//записи изменений в файл
	string fileName="..\\"+db.GetDBName()+"\\"+tabName+TabNameExtension(db.GetDBName());
	cout<<"Параметры таблицы "<<tabName<<":\n";
	string primKey("Hot Dog");//значение первичного ключа, чтобы не вводить
	vector<int> indexes=db[tabName]->IndexOfRecord(&primKey,"ProductID");
	int ind=indexes[0];//т.к. "Hot Dog" - primKey, то indexes.size()=1 
	//Вычисляем новую цену
	dbmsLib::Row row=(*db[tabName])[ind];
	double price=*(double*)(*db[tabName])[ind]["UnitPrice"];
	cout<<"oldPrice="<<price<<endl;
	//записываем новую цену товара "Hot Dog" в таблицу "Products", но не в БД.
	//В таблицу записываем строку целиком.
	price=price+1.5;
	row["UnitPrice"]=new double(price);//!!! Обязательно new
	db[tabName]->AddRow(row,ind);
	cout<<"newPrice="<<price<<endl;
	//записываем таблицу "Products" c измененной ценой товара "Hot Dog" в файл БД.
	db[tabName]->WriteDBTable(fileName);//полиморфный вызов виртуальной функции.
	//тип БД устанавливается при чтении из файла, используя соглашение по именованию.
	//-------------------------------------------------------------
	// Запись в бинарный файл с использованием прямого доступа
	//записываем новую цену товара "Hot Dog" в файл БД.
	//В файл можем записывать любое число байтов. 
	//Здесь записываем поле "UnitPrice" (8 байтов) в строку с номером ind.
	//int pos=db[tabName]->FieldPosInFile(ind,"UnitPrice");
	//fstream fInOut;//открытие файлового потока на ввод-вывод
	//fInOut.open(fileName.c_str(),ios::binary|ios::in|ios::out);
	//if (!fInOut.is_open())	{ 
	//	cout<<"Ошибка открытия файла\n"<< endl; 
	//	system("pause");
	//	return;
	//}
	//fInOut.clear();//!!!сбросить, на всякий случай, флаг EOF, 
	////который может установиться в результате чтения файла
	//fInOut.seekp(pos);
	//fInOut.write((char*)&price,sizeof(double));
	//fInOut.close();	
}
//==========================================
/*В методы класса DBTable, которые выполняют обмен данными с файлами БД:
db[tabName].WriteToFileBin(pathBin+tabName), db[tabName].ReadFromFileBin(pathBin+tabName)
db[tabName].WriteToFileTxt(pathTxt+tabName), db[tabName].ReadFromFileTxt(pathTxt+tabName)
db[tabName].WriteToFile(path+tabName) db[tabName].ReadFromFile(path+tabName),
в качестве параметра передается "относительный" путь к файлу. 
Эти методы зависят от способа хранения данных в файле.
Методам печати таблиц 
db[tabName].Print(screenWidth) и db[tabName].PrintTable(screenWidth)
требуется только имя таблицы, так как они берут данные из объектов DBTable, а не из файлов.
Для таблиц DBTableBin и DBTableTxt, имеющих одинаковую структуру, используется один и тот 
же метод печати db[tabName].PrintTable(screenWidth). Параметр screenWidth - 
ширина экрана в байтах.
*/
//-------------------------------------------------------------
void DeliveryBooksToStudents(dbmsLib::DBTableSet &db,int screenWidth){
	/*Выдача книг студенту в библиотеке:
	1. Записать студента в библиотеку, если он ещё не записан (табл. Students).
	2. Проверить наличие книги в библиотеке и на руках у студента. У него не должно быть 
	более одного экземпляра книги(табл. Books, Students и Abonements: BookId, StudentId ). 
	3. Перед выдачей сделать проверку наличия экземпляра книги в книгохранилище (табл. Books).
	4. Внести изменения в таблицы Books и Abonements. (Можно сначала создать запись в буфере,
	проверить выполнение условий, а затем,если все проверки ОК!, внести созданные записи в БД и
	выдать сообщение о результате выполнения операции.
	*/

	//Выдача нескольких книг студенту
	//	string tabName = "Students";
	cout<<"Введите имя студента\n";
	string name;
	cin>>name;
	string dbName = db.GetDBName();
	string path="..\\"+dbName+"\\";
	//Проверка наличия абонента в БД библиотеки 
	if((db["Students"]->IndexOfRecord(&name, "Name").size()==0)){
		//замените"Name"  на "StudentID"(номер читательского билета),
		//чтобы можно было добавить однофамильца
		cout<<"В БД нет данных о студенте "<<name<< endl;
		cout<<"Добавить студента в список абонентов Библиотеки? ('y'/'n')"<<endl;
		char choice;
		cin>>choice;
		if(choice=='y'){
			dbmsLib::Row row=db["Students"]->CreateRow();
			db["Students"]->AddRow(row,db["Students"]->GetSize());
		}else return;
	}
	db["Students"]->PrintTable(78);
	int studId;
	cout<<"Выберите и введите StudentID"<<endl;//так как могут быть однофамильцы
	cin>>studId;
	bool isContinue=false;
	do{
		db["Books"]->PrintTable(78);
		int bookId;
		cout<<"Выберите и введите BookID"<<endl;
		cin>>bookId;
		// Проверка наличия экземпляра книги в библиотеке и отсутствия её у студента
		vector<int> indexes=db["Books"]->IndexOfRecord(&bookId,"BookID");
		if(indexes.size()==0){
			cout<<"В библиотеке нет книг с индексом "<<bookId<<endl;
			return;
		}
		if((*(int*)(*db["Books"])[indexes[0]]["Quantity"])<=
			(*(int*)(*db["Books"])[indexes[0]]["Number"])){
				cout<<"В библиотеки нет свободных экземпляров книг с индексом "<<bookId<<endl;
				return;
		}
		// Проверка отсутствия экземпляра книги у студента: 
		// Студент не брал книгу или брал, но вернул её
		dbmsLib::DBTable* studIdBooks=db["Abonements"]->SelfRows("StudentID",dbmsLib::Equal,&studId);
		cout<<"Распечатка книг, которые выдавались студенту StudentID="<<studId<<endl;
		studIdBooks->PrintTable(screenWidth);
		dbmsLib::DBTable* studIdBookId=studIdBooks->SelfRows("BookID",dbmsLib::Equal,&bookId);
		vector<int> bookIdIndexes=studIdBookId->IndexOfRecord(&bookId,"BookID");
		if(studIdBookId->GetSize()!=0)
		{
			cout<<"Распечатка книг BookID="<<bookId<<" у студента StudentID="<<studId<<endl;
			studIdBookId->PrintTable(screenWidth);
			dbmsLib::DBDate returnDate("1.1.1");
			//проверка возврата книги bookId (студент может брать несколько раз и возвращать
			//одну и ту же книгу).
			for(int i=0; i<bookIdIndexes.size();i++)
				if(*((dbmsLib::DBDate*)(*studIdBookId)[bookIdIndexes[i]]["DateOut"])==returnDate){
					cout<<"Книга не может быть выдана, т.к. она есть у студента "<<name<<endl; 
					return;
				}
		}
		//Выдача книги и внесение соответствующих изменений в БД
		cout<<"Добавление записи в таблицу Abonements и внесение изменений в таблицу Books"<<endl;
		dbmsLib::Row row=db["Abonements"]->CreateRow();
		db["Abonements"]->AddRow(row,db["Abonements"]->GetSize());
		vector<int> bookIndexes=db["Books"]->IndexOfRecord(&bookId,"BookID");
		(*((int*)((*db["Books"])[bookIndexes[0]]["Number"])))++;//!!!
		cout<<"Информация о результатах оформления выдачи книги"<<endl;
		db["Abonements"]->PrintTable(screenWidth);
		db["Books"]->PrintTable(screenWidth);
		cout<<"Продолжить заказ? 1/0\n";
		cin>>isContinue;
	}while(isContinue);
	
	//db["OrderDetails"]->PrintTable(screenWidth,db.GetDBName());
	//db["Products"]->PrintTable(screenWidth,db.GetDBName());

	//Записываем в БД изменения в таблицах Abonements,Books и Students
	//db["Abonements"]->WriteDBTable(path+"Abonements.txt");
	//db["Books"]->WriteDBTable(path+"Books.txt");
//	db["Students"]->WriteDBTable(path+"Students.txt");
	db.WriteDB();

}
//-------------------------------------------------------------
void Testing(string dbName,string tabName){
	string path="..\\LibraryBin\\Books.bin";
	dbmsLib::DBTableBin books;
	books.ReadDBTable(path);
	books.PrintTable(64);
	fstream fInOut(path,ios::in|ios::out|ios::binary);
	int bookId=1;
	vector<int> bookIndexes=books.IndexOfRecord(&bookId,"BookID");	
	//записываем изменения в таблице Books в файл,
	//используя прямой доступ к данным в файле (для иллюстрации прямого доступа к файлу).
	int pos=books.FieldPosInFile(bookIndexes[0],"Number");
	fInOut.seekp(pos);
	int number=2;
	fInOut.write((char*)&number,sizeof(int));		
	fInOut.close();
	books.ReadDBTable(path);
	books.PrintTable(64);	
}
//--------------------------------------------------------
void main()
{
	system("chcp 1251 > nul");
//	cout<<"Введите имя БД\n";//закомментировано для удобства тестирования при отладке
	string dbName("LibraryBin");//("LibraryBin","CompanyBin","LibraryTxt",CompanyTxt);
//	cin>>dbName;
	cout<<dbName<<endl;
	dbmsLib::DBTableSet db(dbName);
	string path="..\\"+dbName+"\\";
	//	cout<<"Введите текущую дату dd.mm.yyyy\n";
	string str("21.04.2018");
	//	cin>>str;
	dbmsLib::DBDate today(str);
	//	cout<<"Введите ширину экрана в символах\n";
	int screenWidth=78;
	//	cin>>screenWidth;
	string tabName="Products";//"Students";"TableRelations";"Abonements";"Books"
	//"Products";"OrderDetails";"Orders";"Customers"
	string pathBin="..\\LibraryBin\\";//CompanyBin, LibraryBin
	while(true)
	{ 
		switch (menu(dbName,today))
		{
		case 1: db.ReadDB();//Чтение таблиц БД. 
			//БД хранится в папке "..\\"+dbName+". 
			//Имя БД оканчивается или на Txt, если таблицы БД хранятся в текстовых файлах,
			//или на Bin, если таблицы БД хранятся в бинарных файлах. Например,
			//"LibraryBin","CompanyBin","LibraryTxt","CompanyTxt".
			//Каждая таблица хранится в отдельном файле с именем = <имя таблицы>+<.txt | .bin>
			//Первая строка файла содержит имя таблицы и имя столбца с первичным ключем
			//Вторая строка файла - заголовок таблицы.
			//Все последующие строки - записи таблицы. 
			//В БД список имен файлов с таблицами хранится в файле с именем DBTables.txt, 
			//а описание связей между таблицами - в файле с именем DataRelations.txt
			break;
		case 2: db.PrintDB(screenWidth);//Печать всех таблиц БД (по 4 колонки в строке)
			break;
		case 3: db[tabName]->WriteDBTable(path+tabName+TabNameExtension( dbName));break;//pathBin
		case 4: Testing(dbName,tabName); break; 
		case 5: db.WriteDB(); break;
		case 6: StudentBooksList(db,screenWidth); break;
		case 7: DeliveryBooksToStudents(db,screenWidth); break;
		case 9:	db[tabName]->ReadDBTable(path+tabName+TabNameExtension( dbName)); break;
		case 10:db[tabName]->PrintTable(screenWidth); 
			//db.GetDBName() - для универсальности, чтобы можно было бы 
			//распечатывать DBTableTxt и DBTableBin. 
			break;
		case 11:ChaingePrice(db,tabName); break;
		case 12: ExecuteOrder(db,screenWidth);break;
		case 13:((dbmsLib::DBTableTxt*)db[tabName])->WriteTableBin(pathBin+tabName+".bin");break;
		case 14:((dbmsLib::DBTableTxt*)db[tabName])->ReadTableBin(pathBin+tabName+".bin");break;
		case 8: return;
		default: cout<<(" Надо вводить число от 1 до 8\n"); break;
		}    	
	}	
	system("pause");
}
