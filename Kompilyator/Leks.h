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
		vector<TableOfIdent> I;	//������ ����
		vector<int> C;		//������ �����
		vector<string> L;	//������ ���������
		vector<string> K;	//������ �������� ����
		vector<char> R;		//������ ������������ ������������
		vector<string> D;	//������ ����������� ������������
		ifstream Read;
		int S;				//������� � �������� ��������
		int pos;			//������� � ������
		string buf, s;		//����� � ��������� ������ �� �����
		char T; int j;		//��� � � j ���� ��� � ����������, ������� ����� ��������� �� ���������� � ��������� ���
		bool flag_scp;		//���� �� � ������� ��� ������������ � ������ ���� ����������, �� �� ������� ������ T � j ��� ��� ��� �� ����������
		bool if_Bukva(char b);
		bool if_Cifra(char b);
		void Iterator();
		void Chislo();
		void Literal();
		//int toInt(string str);
		int Find(vector<TableOfIdent>& mass, string str);
		int Find(vector<string>& mass, string str);		//����� ������ � �������, ���� ���� �� ���������� �������, ���� ��� �� -1 
		int Find(vector<char>& mass, char str);			//����� ������� � �������, ���� ���� �� ���������� �������, ���� ��� �� -1 
		int Find(vector<int>& mass, int str);			//����� ����� � �������, ���� ���� �� ���������� �������, ���� ��� �� -1 
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
