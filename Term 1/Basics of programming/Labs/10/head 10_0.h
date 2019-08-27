#pragma once
#include <iostream>
#include <fstream>
using namespace std;
const int l_word = 31;

struct Dictionary
{
	char rus[l_word];
	char eng[l_word];
	int index;
};

ostream& operator<<(ostream& out, Dictionary& dict)		//вывод
{
	//out << "\t" << dict.rus << " - " << dict.eng;
	out << "\t" << dict.rus << " - " << dict.eng << endl;
	return out;
}

ofstream& operator<<(ofstream& out, Dictionary& dict)		//Запись в файл
{
	out << dict.rus << "-" << dict.eng << endl;
	return out;
}

void addWord(Dictionary*& dict, int &n, Dictionary elem)
{
	Dictionary *dict1 = new Dictionary[++n];
	memcpy(dict1, dict, (n - 1) * sizeof(Dictionary));
	if (n - 1 != 1)
		delete[] dict;
	dict1[n - 1] = elem;
	dict = dict1;
}
int Compare1(Dictionary *dict1, int i, int j)
{
	int ans;
	ans = strcmp(dict1[i].rus,dict1[i + j].rus);
	return ans;
}
void sorting(Dictionary*& dict, int nWords)
{
	int ans;

	for(int i = 0; i < nWords; i++)
	{
		for(int j = 1; j < nWords-i; j++)
		{
			ans = Compare1(dict,i, j);
			if(ans > 0)
			{
				Dictionary temp;
				strcpy(temp.rus,dict[i].rus);
				strcpy(temp.eng,dict[i].eng);
				strcpy(dict[i].rus,dict[i + j].rus);
				strcpy(dict[i].eng,dict[i + j].eng);
				strcpy(dict[i + j].rus,temp.rus);
				strcpy(dict[i + j].eng,temp.eng);
			}
		}
	}
}


bool Compare(Dictionary *dict, Dictionary elem, int i, int var)
{
	int ans;
	if(var == 1)
		ans = strcmp(dict[i].rus,elem.rus);
	if(var == 2)
		ans = strcmp(dict[i].eng,elem.eng);
	return ans;
}
void searchWord(Dictionary*& dict, int &n, int& var, Dictionary& elem)
{
	if (var == 1)
		for (int i = 0; i < n; i++)
			if (Compare(dict, elem, i, var) == 0)
			//if (*(dict[i].rus) == *(elem.rus))
			{
				elem.index = i;
				var = 0;
				break;
			}
	if (var == 2)
		for (int i = 0; i < n; i++)
			if (*(dict[i].eng) == *(elem.eng))
			{
				elem.index = i;
				var = 0;
				break;
			}
	if (var != 0)
		cout << "Такого слова нет...\n\n";
}
void deleteWord(Dictionary*& dict, int &n, Dictionary elem)
{
	n--;
	for (int i = elem.index; i < n; i++)
	{
		dict[i] = dict[i + 1];
	}
	memset(dict[n].rus, 0, 31);
	memset(dict[n].eng, 0, 31);
	//dict[n] =  NULL ;
	Dictionary *dict1 = new Dictionary[n];
	memcpy(dict1, dict, n * sizeof(Dictionary));
	if (n - 1 != 1)
		delete[] dict;
	dict = dict1;
}

void cleanDict(Dictionary*& dict, int &n)
{
	n = 0;
	delete[] dict;
	cout << "\t***Выполнено\n";
}