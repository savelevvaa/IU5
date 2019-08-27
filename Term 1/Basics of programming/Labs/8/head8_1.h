#include <iostream> 
#include <iomanip>
#include <fstream>
#include <Windows.h>
using namespace std;

void createKeys(char *fName, char *&keys, int &nKey) 
{
	ifstream fin(fName, ios::in);
	
	char line[1000];
	char *word, *nextWord;
	char delims[] = "!:;'\".?, \n";
	nKey = 0;
	while (fin.getline(line, 1000)) {
		nextWord = line;
		while (word = strtok_s(nextWord, delims, &nextWord))
			nKey++;
	}
	fin.clear();
	fin.seekg(0);
	keys = new char[nKey];
	int n = 0;
	while (fin.getline(line, 1000)) {
		nextWord = line;
		while (word = strtok_s(nextWord, delims, &nextWord)) {
			keys[n] = 0;

			for (int i = 0; i < strlen(word); i++) {
				keys[n] += word[i];
			}
			n++;
		}
	}
}

void Keys(char*& keys, int n, int a, int b)									//заполнение массива ключей
{
	keys = new char[n];
	for (int i = 0; i < n; i++)
	{
		keys[i] = rand() % a - b;
	}
}

int cnt_digits(int num) { return (num /= 10) ? 1 + cnt_digits(num) : 1; }	//определяет кол-во цифр в числе ( для setw() )

template < class T> void printKeys(T* keys, int n)							//печать массива ключей
{
	cout << "Ключи: " << endl;
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (keys[i] > max)
		{
			max = keys[i];
		}
	}
	int w = 2 + cnt_digits(max);
	int colomn;
	int c = 0;
	colomn = 77 / w;  
	cout << endl;
	cout << setw(3) << "№  ";
	for (int j = 0; j < colomn; j++) cout << setw(w) << (j + 1);
	cout << "\n_______________________________________________________________________________\n";
		
	for (int i = 0; i < n; i++)
	{
		if (i % colomn == 0)
		{
			cout << endl;													
			cout << setw(3) << c << "|";
			c++;
		}
		cout << setw(w) << (int)keys[i];
	}
		cout << endl << endl;
}

void scripting(char* txt, char* scrtxt, int* keys, int n)					//шифрование
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (txt[i] == char(j))											//ищем символ в таблице ASCII
			{
				scrtxt[i] = char(j + keys[i]);								//сдвигаем по таблице ASCII и меняем символ
			}
		}
	}
}

void descripting(char* txt, char* scrtxt, int* keys, int n)					//дешифрование
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (scrtxt[i] == char(j))										//ищем символ в таблице ASCII
			{
				txt[i] = char(j - keys[i]);									//сдвигаем по таблице ASCII в обратную сторону,										
			}																//пользуясь тем же ключом и "расшифровываем" символ
		}
	}
}

template <class T> void print(T* arr, int n, int t)							//печать текста
{
	for (int i = 0; i < n; i++)
	{
		Sleep(t);
		cout << arr[i];
	}
	cout << endl << endl;
}

//void createKeys1(const char *fName, int *&keys, int nKeys2)
//{
//	char *token;				//текущее слово
//	char *nextToken;			//следующее слово
//	char line[1000];			//массив для строки
//	char delims[] = " .,\n";	//исключения
//	int n = 0;					//счётчик
//	int value = 0;				// сумма символов слова
//	ifstream fin(fName);
//	fin.open(fName, ifstream::app);
//	if (!fin.is_open())														//проверка на открытие
//		cout << "Ошибка открытия файла!" << endl;
//
//	keys = new int[nKeys2];
//
//	for (n = 0; n <= nKeys2;)
//	{
//		while (fin.getline(line, 1000))										//пока "берём" строку
//		{
//			if (n > nKeys2) break;
//			nextToken = line;
//			while (token = strtok_s(nextToken, delims, &nextToken))			//пока есть слова
//			{
//				if (n > nKeys2) break;
//				keys[n] = 0;
//				value = 0;
//				for (int i = 0; i < strlen(token); i++)
//				{
//					value += (int)token[i];									//считаем сумму символов слова
//				}
//				keys[n] = value % 256;										//присваеваем эту сумму по модулю 256 n-ому элементу массива
//				n++;
//
//			}
//		}
//		fin.clear();
//		fin.seekg(0);
//	}
//	cout << n - 1 << endl;
//	fin.close();
//}