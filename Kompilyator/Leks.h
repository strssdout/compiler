#pragma once
#ifndef _LEKS_H_
#define _LEKS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

struct TableOfIdent
{
	string name;
	int type;
	int ArraySize;
	int ArrayType;
};

class Leks
{
	private:
		vector<TableOfIdent> I;	//массив слов
		vector<int> C;		//массив чисел
		vector<string> L;	//массив литералов
		vector<string> K;	//массив ключевых слов
		vector<char> R;		//массив однолитерных разделителей
		vector<string> D;	//массив двулитерных разделителей
		ifstream Read;
		int S;				//позиция в конечном автомате
		int pos;			//позиция в строке
		string buf, s;		//буфер и считанная строка из файла
		char T; int j;		//эти Т и j теже что и возвращаем, добавил чтобы постоянно не передавать и упростить код
		bool flag_scp;		//если мы в прошлый раз подглядывали и сейчас надо подглянуть, то мы передаём старые T и j так как они не изменились
		bool if_Bukva(char b);
		bool if_Cifra(char b);
		void Iterator();
		void Chislo();
		void Literal();
		//int toInt(string str);
		int Find(vector<TableOfIdent>& mass, string str);
		int Find(vector<string>& mass, string str);		//поиск строки в массиве, если есть то возвращает позицию, если нет то -1 
		int Find(vector<char>& mass, char str);			//поиск символа в массиве, если есть то возвращает позицию, если нет то -1 
		int Find(vector<int>& mass, int str);			//поиск числа в массиве, если есть то возвращает позицию, если нет то -1 
		void Initialization();
		void Scaning();
	public:
		Leks(string file_name);
		void Scan(char& T, int& j);
		void Scp(char& T, int& j);
		void Open(string file_name);
		void Vivod_all_mass();
		string GetBuf();
		void AddType(int num, int type, int ArraySize = 0, int ArrayType = 0);
		vector<TableOfIdent> Get_I();
		vector<string> Get_L();
};

#endif
