#pragma once
//#ifndef _DZlib_h
//#define _DZlib_
#include <iostream>
#include <fstream>
using namespace std;
const int maxWords = 100, maxSentence = 100;

struct Sentence
{
	char* words[maxWords];	//массив слов
	int nWords;
	char* wordAttribute[maxWords];	//какие либо особенности слова
	Sentence();
	char*& operator[](int n);
};
ostream& operator<<(ostream& out, Sentence& sent)		//вывод
{
	for (int i = 0; i < sent.nWords; i++)
		out<< sent.words[i] << ' ';
	out << "\b." << endl << endl;
	return out;
}
Sentence::Sentence()		//обнуления
{
	nWords = 0;
	for (int i = 0; i < maxWords; i++)	//обнуление массива
		wordAttribute[i] = NULL;
}
Sentence& GetSentence(char* str)
{
	Sentence sent = *new Sentence;
	char* word;
	char* nextword;
	nextword = str;
	while (word = strtok_s(nextword, " ,.!?", &nextword))
	{
		sent.words[sent.nWords++] = word;
	}
	return sent;
}
struct Text
{
	Sentence sentence[maxSentence];	//массив предложений типа Sentences
	int nSentences;		//кол во предложений
	char* sentenceAttribute[maxSentence];	//какие либо особенности слова
	Text();
	char*& operator[](int n);
};
ostream& operator<<(ostream& out, Text& txt)	//вывод 
{
	for (int i = 0; i < txt.nSentences; i++)
		out << i + 1 << ") " << txt.sentence[i];
	out << endl;
	return out;
}
Text::Text()	//обнуления
{
	nSentences = 0;
	for (int i = 0; i < maxWords; i++)	//обнуление массива
		sentenceAttribute[i] = NULL;
}
Text& GetText(char* str)
{
	Text txt = *new Text;
	char* sent;
	char* nextsent;
	nextsent = str;
	while (sent = strtok_s(nextsent, ".!?", &nextsent))
	{
		txt.sentence[txt.nSentences++] = GetSentence(sent);
	}
	return txt;
}
Text& LastWord(Text& txt, int n)		//Последне слово предложения
{
	
	txt.sentenceAttribute[n] = txt.sentence[n].words[txt.sentence[n].nWords - 1];
	return txt;
}

char* inputText()
{
	system("chcp 1251>nul");
	char buf[10000];
	int count = 0;
	int ch;
	int i = 0;
	while ((ch = _getch()) != '\r')
	{		
			if (ch == char(8))
			{
				cout << "\b"; --count;
			}
			buf[count++] = char(ch);
			
			cout << char(ch);
		i++;
	}
	if (ch == '\r')
	{
		buf[count] = '\0';
	}
	char* str = new char[count];
	strcpy(str,buf);
	system("chcp 1251>nul");
	return str;
}

void DeleteWords(Text& txt)			//УДАЛЕНИЕ СЛОВ РАВНЫХ ПОСЛЕДНЕМУ
{
	int nWords;
	int nSents = txt.nSentences;


	for (int i = 0; i < nSents; i++)	//По предложениям
	{
		nWords = txt.sentence[i].nWords;
		for (int j = 0; j < nWords; j++)		//По словам в предложении
		{

			while (*(txt.sentence[i].words[j]) == *(txt.sentenceAttribute[i]))	// Условие равности с последним словом
			{
				if (j != nWords - 1)		//Исключаем возможность изменения последнего слова
				{
					nWords = --txt.sentence[i].nWords;						//Уменьшаем кол во слов
					for (int k = j; k < nWords; k++)
					{
						txt.sentence[i].words[k] = txt.sentence[i].words[k + 1];	//Сдвигаем массив
					}
					txt.sentence[i].words[nWords] = NULL;
				}
				else
					break;
			}

		}
	}
}

void Swap(Text& txt, int nWords, int nSents)		//ПЕРЕСТАНОВКА СЛОВ
{
	char* temp;
	temp = txt.sentence[nSents].words[nWords];
	txt.sentence[nSents].words[nWords] = txt.sentence[nSents].words[nWords - 1];
	txt.sentence[nSents].words[nWords - 1] = temp;
}
//#endif//_DZlib_