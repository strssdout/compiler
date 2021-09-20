#include <iostream>
#include <string>
#include <conio.h>
#include <iostream>
#include <cstdlib> 
#include "Leks.h"

using namespace std;

void E(); void E_(); void T_(); /*void E_1(); void T_1();*/ void F(); void Lg(); void Tl(); void Fl(); void Zn(string &S);
void Prog(); void Bob(); void TypeB(int &type); void Bop(); void Op(); void Vol(); void Ist(); void Bis(); void Rd(); void Wr();
void GenerateKod_Data(vector<TableOfIdent> I, vector<string> L);
void GenerateKod_Proc();
string GetMarkerNumber();
bool E_Follow();
void ERR(int kod);

int MarkerCounter = 0;
int j;
char T;

string input_file_name = "in.txt";
string output_file_name = "out.txt";

Leks MyLeks(input_file_name);
ofstream fout;


int main() {
	system("chcp 1251");
	system("cls");

	cout << "Начало программы" << endl;

	fout.open(output_file_name);

	Prog();

	cout << "конец." << endl;

	fout.close();

	_getch();
}


void Prog() {

	//генерация кода 
	fout << ".model small\n"
		<< ".stack 100h\n"
		<< ".code\n"
		<< "start:\n"
		<< "  mov ax, @data\n"
		<< "  mov ds, ax\n\n";

	MyLeks.Scan(T,j);
	if (T == 'I') {						//Название
		MyLeks.AddType(j, -3, 0, 0);	//Помечаем -3
	}
	else {
		ERR(1);
	}
	Bob();
	MyLeks.Scan(T,j);
	if (T == 'K' && j == 38) {

	}
	else ERR(8);
	Bop();

	//генерация кода 
	fout << "\nExit:\n"
		<< "  mov ah, 4Ch\n"
		<< "  int 21h\n";

	GenerateKod_Proc();
	GenerateKod_Data(MyLeks.Get_I(), MyLeks.Get_L());

	fout << "end start\n";
}

void Bob()
{
	MyLeks.Scan(T, j);
	if (!(T == 'K' && j == 37)) {	//Declare
		ERR(2);
	}
	MyLeks.Scp(T, j);
	while (!(T == 'K' && j == 38))
	{
		int type;
		TypeB(type);
		MyLeks.Scan(T, j);
		if (T == 'I') {						//I([E] | eps)
			int I_j = j;
			MyLeks.Scp(T, j);
			if (T == 'R' && j == 15) {
				MyLeks.Scan(T, j);
				MyLeks.Scan(T, j);
				int C_j = j;
				if (T == 'C') {
				}
				else ERR(4);
				MyLeks.Scan(T, j);
				if (!(T == 'R' && j == 14)) {
					ERR(5);
				}
				MyLeks.AddType(I_j, -2, C_j, type);	//массив, -2 указывает что это массив
			}
			else {
				MyLeks.AddType(I_j, type);	//переменная
			}
		}
		else {
			ERR(6);
		}
		MyLeks.Scp(T, j);
		while (!((T == 'K' && j == 38) || (T == 'R' && j == 2))) {
			MyLeks.Scan(T, j);
			if (!(T == 'R' && j == 1)) {	//запятая
				ERR(7);
			}
			MyLeks.Scan(T, j);
			if (T == 'I') {						//I([E] | eps)
				int I_j = j;
				MyLeks.Scp(T, j);
				if (T == 'R' && j == 15) {
					MyLeks.Scan(T, j);
					MyLeks.Scan(T, j);
					int C_j = j;
					if (T == 'C') {}
					else ERR(4);
					MyLeks.Scan(T, j);
					if (!(T == 'R' && j == 14)) {
						ERR(5);
					}
					MyLeks.AddType(I_j, -2, C_j, type); //массив, -2 указывает что это массив
				}
				else {
					MyLeks.AddType(I_j, type, 0, 0);	//переменная
				}
			}
			else {
				ERR(6);
			}
			MyLeks.Scp(T, j);
		}
		if (T == 'R' && j == 2) {
			MyLeks.Scan(T, j);
		}
	}
}

void TypeB(int &type) {
	MyLeks.Scan(T, j);
	if (T == 'K') {
		switch (j) {
		case 39:  	// int
			type = 39;
			break;
		case 40:	// bool
			type = 40;
			break;
		case 41:	// char
			type = 41;
			break;
		default:
			ERR(3);
			break;
		}
	}
	else {
		ERR(3);
	}

}

void Bop() {
	MyLeks.Scan(T,j);
	if (!(T == 'R' && j == 16)) {	//{
		ERR(0);
	}
	MyLeks.Scp(T,j);
	while (!(T == 'R' && j == 17)) {	//}
		Op();
		MyLeks.Scp(T,j);
		if (T == 'R' && j == 17) {	//}

		}
		else if (T == 'R' && j == 2) {
			MyLeks.Scan(T,j);
		}
		else ERR(0);
		MyLeks.Scp(T,j);
	}
	MyLeks.Scan(T,j);
}

void Op() {
	MyLeks.Scp(T,j);
	if (T == 'K') {
		switch (j) {
		case 42:  	//  'let'
			Vol();
			break;
		case 15:	//  'if'
			Ist();
			break;
		case 35:	//  'while'
			Bis();
			break;
		case 43:	//  'Read'
			Rd();
			break;
		case 44:	//  'Write'
			Wr();
			break;
		default:
			ERR(0);
			break;
		}
	}
	else if (T == 'R' && j == 16) {	//{
		Bop();
	}
	else {
		Vol();
	}
}

void Vol() {
	MyLeks.Scp(T,j);
	if (T == 'K' && j == 42) {	//let
		MyLeks.Scan(T,j);
	}
	MyLeks.Scan(T,j);
	int a = j;	//для генерации кода, сохранение локальной переменной
	if (T == 'I') {
		fout << "  ;Let{\n"
			<< "  XOR BX, BX\n";
		fout << "  PUSH BX\n";

		MyLeks.Scp(T, j);
		if (T == 'R' && j == 15) {	//[
			MyLeks.Scan(T, j);
			E();

			fout << "  ;\n"
				<< "  POP BX\n"
				<< "  POP AX\n";
			if (MyLeks.Get_I()[a].ArrayType == 39) { //int
				fout << "  SAL BX, 1\n";	//умножение на 2, потому что int занимает 2 байта
			}
			fout << "  PUSH BX\n";

			MyLeks.Scan(T, j);
			if (!(T == 'R' && j == 14)) {	//]
				ERR(0);
			}
		}
	}
	else {
		ERR(0);
	}
	MyLeks.Scan(T,j);
	if (!(T == 'R' && j == 12)) {	//=
		ERR(0);
	}
	E();
	fout << "  ;\n"
		<< "  POP AX\n"
		<< "  POP BX\n"
		<< "  MOV " << MyLeks.Get_I()[a].name << "[BX], AX\n"
		<< "  ;}\n";
}

void Ist() {
	MyLeks.Scan(T,j);
	if (!(T == 'K' && j == 15)) {	//if
		ERR(0);
	}

	//генерация кода 
	fout << "  ;if(\n";

	Lg();

	//генерация кода 
	string M1 = GetMarkerNumber();
	string M2 = GetMarkerNumber();
	fout << "  POP AX\n"
		<< "  CMP AX, 0\n"
		<< "  JNZ " << M1 << "\n"
		<< "  JMP " << M2 << "\n"
		<< M1 << ":\n"
		<< "  ;)\n";

	MyLeks.Scan(T,j);
	if (!(T == 'K' && j == 29)) {	//then
		ERR(0);
	}

	//генерация кода 
	fout << "  ;then{\n";

	Op();

	//генерация кода 
	string M3 = GetMarkerNumber();
	fout << "  JMP " << M3 << "\n"
		<< M2 << ":\n"
		<< "  ;}\n";

	MyLeks.Scp(T,j);
	if (T == 'K' && j == 8) {	//else
		//генерация кода 
		fout << "  ;else{\n";
		

		MyLeks.Scan(T,j);
		Op();

		//генерация кода 
		fout << "  ;}\n";
	}
	//генерация кода 
	fout << M3 << ":\n";
}

void Bis() {
	MyLeks.Scan(T,j);
	if (!(T == 'K' && j == 35)) {	//while
		ERR(0);
	}

	//генерация кода 
	string M1 = GetMarkerNumber();
	fout << "  ;while(\n"
		<< M1 << ":\n";

	Lg();

	//генерация кода 
	string M2 = GetMarkerNumber();
	string M3 = GetMarkerNumber();
	fout << "  POP AX\n"
		<< "  CMP AX, 0\n"
		<< "  JNZ " << M3 << "\n"
		<< "  JMP " << M2 << "\n"
		<< M3 << ":\n"
		<< "  ;){\n";
	

	Op();

	//генерация кода
	fout << "  JMP " << M1 << "\n"
		<< M2 << ":\n"
		<< "  ;}\n";

}

void Rd() {
	MyLeks.Scan(T,j);
	if (!(T == 'K' && j == 43)) {	//Read
		ERR(0);
	}

	//генерация кода 
	fout << "  MOV DX, offset buffer\n"
		<< "  MOV AH, 0Ah\n"
		<< "  INT 21h\n"
		<< "  MOV DX, offset crlf\n"
		<< "  MOV AH, 9\n"
		<< "  INT 21h\n"
		<< "  XOR DI, DI\n";

	MyLeks.Scan(T,j);
	if (!(T == 'R' && j == 9)) {		//(
		ERR(0);
	}
	MyLeks.Scp(T,j);
	while (!(T == 'R' && j == 8)) {	//)
		MyLeks.Scan(T,j);
		int a = j;	
		if (T == 'I') {
			//генерация кода {
			fout << "  ;I{\n"
				<< "  XOR BX, BX\n";
			fout << "  PUSH BX\n";
			//}

			MyLeks.Scp(T,j);
			if (T == 'R' && j == 15) {	//[
				MyLeks.Scan(T,j);
				E();

				//генерация кода {
				fout << "  ;\n"
					<< "  POP BX\n";
				fout << "  POP AX\n";
				if (MyLeks.Get_I()[a].ArrayType == 39) { //int
					fout << "  SAL BX, 1\n";	//умножение на 2, потому что int занимает 2 байта
				}
				fout << "  PUSH BX\n";
				//}

				MyLeks.Scan(T,j);
				if (!(T == 'R' && j == 14)) {	//]
					ERR(0);
				}
			}
		}
		else {
			ERR(0);
		}

		//генерация кода {
		fout << "  ;\n"
			<< "  CALL read_chislo\n"
			<< "  POP BX\n"
			<< "  MOV " + MyLeks.Get_I()[a].name + "[BX],AX\n";
		//}

		MyLeks.Scp(T,j);
		if (T == 'R' && j == 1) {	//запятая
			MyLeks.Scan(T,j);
			MyLeks.Scp(T,j);
			if (T == 'R' && j == 8) {	//)
				ERR(0);
			}
		}
		else {
			MyLeks.Scp(T,j);
		}
	}
	if (T == 'R' && j == 8) {	//)
		MyLeks.Scan(T,j);
	}
	else {
		ERR(0);
	}
}

void Wr() {
	MyLeks.Scan(T,j);
	if (!(T == 'K' && j == 44)) {	//Write
		ERR(0);
	}

	//генерация кода {
	fout << "  XOR DI, DI\n";
	//}

	MyLeks.Scan(T,j);
	if (!(T == 'R' && j == 9)) {		//(
		ERR(0);
	}
	MyLeks.Scp(T,j);
	while (!(T == 'R' && j == 8)) {	//)
		if (T == 'I' || T == 'C' || (T == 'R' && j == 9)) {
			E();

			//генерация кода {
			fout << "  POP AX\n"
				<< "  CALL write_chislo\n";
			//}

		}
		else if (T == 'L') {
			MyLeks.Scan(T,j);

			//генерация кода {
			string M1 = GetMarkerNumber();
			string M2 = GetMarkerNumber();
			fout << "  XOR SI, SI\n"
				<< M1 + ":\n"
				<< "  MOV AL, @L" + to_string(j) + "[SI]\n"
				<< "  CMP AL, '$'\n"
				<< "  JZ " + M2 + "\n"
				<< "  MOV buffer_write[DI], AL\n"
				<< "  INC SI\n"
				<< "  INC DI\n"
				<< "  JMP " + M1 + "\n"
				<< M2 + ":\n";
			//}

		}
		else {
			ERR(0);
		}
		MyLeks.Scp(T,j);
		if (T == 'R' && j == 1) {	//запятая
			MyLeks.Scan(T,j);
			MyLeks.Scp(T,j);
			if (T == 'R' && j == 8) {	//)
				ERR(0);
			}
		}
		else {
			MyLeks.Scp(T,j);
		}
	}
	if (T == 'R' && j == 8) {	//)
		MyLeks.Scan(T,j);
	}
	else {
		ERR(0);
	}

	//генерация кода {
	fout << "  MOV buffer_write[di],'$'\n"
		<< "  MOV DX, offset buffer_write\n"
		<< "  MOV AH, 9\n"
		<< "  INT 21h\n"
		<< "  MOV DX, offset crlf\n"
		<< "  MOV AH, 9\n"
		<< "  INT 21h\n";
	//}

}

void E() {
	E_();
	MyLeks.Scp(T,j);
	while (!E_Follow()) {
		if (T == 'R' && j == 19) {
			MyLeks.Scan(T,j);
			E_();
			fout << "  ;add\n"
				<< "  POP AX\n"
				<< "  POP BX\n"
				<< "  AND AX, BX\n"
				<< "  PUSH AX\n";
		}
		else {
			ERR(0);
		}
		MyLeks.Scp(T,j);
	}
}

void E_() {
	T_();
	MyLeks.Scp(T, j);
	while (!(E_Follow() || (T == 'R' && j == 19))) {
		if (T == 'R' && j == 6) {
			MyLeks.Scan(T, j);
			T_();
			fout << "  ;add\n"
				<< "  POP AX\n"
				<< "  POP BX\n"
				<< "  ADD AX, BX\n"
				<< "  PUSH AX\n";
		}
		else if (T == 'R' && j == 7) {
			MyLeks.Scan(T, j);
			T_();
			fout << "  ;sub\n"
				<< "  POP BX\n"
				<< "  POP AX\n"
				<< "  SUB AX, BX\n"
				<< "  PUSH AX\n";
		}
		else {
			ERR(0);
		}
		MyLeks.Scp(T, j);
	}
}

void T_() {
	F();
	MyLeks.Scp(T,j);
	while (!(E_Follow() || (T == 'R' && (j == 6 || j == 7 || j == 19)))) {
		if (T == 'R' && j == 4) {
			MyLeks.Scan(T,j);
			F();
			fout << "  ;mul\n"
				<< "  POP AX\n"
				<< "  POP BX\n"
				<< "  MUL BX\n"
				<< "  PUSH AX\n";
		}
		else if (T == 'R' && j == 5) {
			MyLeks.Scan(T,j);
			F();
			fout << "  ;div\n"
				<< "  POP BX\n"
				<< "  POP AX\n"
				<< "  XOR DX, DX\n"
				<< "  DIV BX\n"
				<< "  PUSH AX\n";
		}
		else {
			ERR(0);
		}
		MyLeks.Scp(T,j);
	}
}

void F() {
	MyLeks.Scan(T,j);
	if (T == 'I') {
		int a = j;	//для генерации кода, сохранение локальной переменной
		fout << "  ;get ident{\n"
			<< "  XOR BX, BX\n";
		MyLeks.Scp(T,j);
		if (T == 'R' && j == 15) {	//[
			MyLeks.Scan(T,j);
			E();

			fout << "  ;\n"
				<< "  POP BX\n";
			if (MyLeks.Get_I()[a].ArrayType == 39) { //int
				fout << "  SAL BX, 1\n";	//умножение на 2, потому что int занимает 2 байта
			}

			MyLeks.Scan(T,j);
			if (!(T == 'R' && j == 14)) {	//]
				ERR(0);
			}
		}
		fout << "  MOV AX, " << MyLeks.Get_I()[a].name << "[BX]\n"
			<< "  PUSH AX\n"
			<< "  ;}\n";
	}
	else if (T == 'C') {
		fout << "  ;get numeric\n"
			<< "  MOV AX, " << MyLeks.GetBuf() << "\n"
			<< "  PUSH AX\n";
	}
	else if (T == 'R' && j == 9) {
		E();
		MyLeks.Scan(T,j);
		if (T == 'R' && j == 8) {

		}
		else {
			ERR(0);
		}
	}
	else {
		ERR(0);
	}
}

void Lg() {
	Tl();
	MyLeks.Scp(T,j);
	while (!((T == 'R' && (j == 8 || j == 13 || j == 2 || j == 16)) || (T == 'K' && (j == 29)))) {
		if (T == 'K' && j == 22) {	//or
			MyLeks.Scan(T,j);
			Tl();
			//генерация кода {
			string M1 = GetMarkerNumber();
			string M2 = GetMarkerNumber();
			fout << "  ;or\n"
				<< "  POP BX\n"
				<< "  POP AX\n"
				<< "  CMP AX, 1\n"
				<< "  JE " << M2 << "\n"
				<< "  CMP BX, 1\n"
				<< "  JE " << M2 << "\n"
				<< "  PUSH 0\n"
				<< "  JMP " << M1 << "\n"
				<< M2 << ": PUSH 1\n"
				<< M1 << ":\n";
			//}
		}
		else {
			ERR(0);
		}
		MyLeks.Scp(T,j);
	}
}
void Tl() {
	Fl();
	MyLeks.Scp(T,j);
	while (!((T == 'R' && (j == 8 || j == 13 || j == 2 || j == 16)) || (T == 'K' && (j == 29 || j == 22)))) {
		if (T == 'K' && j == 0) {	//and
			MyLeks.Scan(T,j);
			Fl();
			//генерация кода 
			string M1 = GetMarkerNumber();
			string M2 = GetMarkerNumber();
			fout << "  ;and\n"
				<< "  POP BX\n"
				<< "  POP AX\n"
				<< "  CMP AX, 0\n"
				<< "  JE " << M2 << "\n"
				<< "  CMP BX, 0\n"
				<< "  JE " << M2 << "\n"
				<< "  PUSH 1\n"
				<< "  JMP " << M1 << "\n"
				<< M2 << ": PUSH 0\n"
				<< M1 << ":\n";
		}
		else {
			ERR(0);
		}
		MyLeks.Scp(T,j);
	}
}
void Fl() {
	MyLeks.Scan(T,j);
	if (T == 'K' && j == 31) {			//True
		//генерация кода 
		fout << "  ;true\n"
			<< "  PUSH 1\n";
	}
	else if (T == 'K' && j == 10) {		//False
		//генерация кода 
		fout << "  ;false\n"
			<< "  PUSH 0\n";
	}
	else if (T == 'I') {						//I([E] | eps)
		//генерация кода 
		int a = j;	
		fout << "  ;get ident{\n"
			<< "  XOR BX, BX\n";
		MyLeks.Scp(T, j);
		if (T == 'R' && j == 15) {	//[
			MyLeks.Scan(T, j);
			E();

			//генерация кода {
			fout << "  ;\n"
				<< "  POP BX\n";
			if (MyLeks.Get_I()[a].ArrayType == 39) { //int
				fout << "  SAL BX, 1\n";	//умножение на 2, потому что int занимает 2 байта
			}
			//}

			MyLeks.Scan(T,j);
			if (!(T == 'R' && j == 14)) {
				ERR(0);
			}
		}

		//генерация кода {
		TableOfIdent temp = MyLeks.Get_I()[a];
		if (temp.ArrayType == 39 || temp.type == 39) {
			string M1 = GetMarkerNumber();
			string M2 = GetMarkerNumber();
			fout << "  ;if not null - true\n"
				<< "  CMP " << temp.name << "[BX], 0\n"
				<< "  JE " << M2 << "\n"
				<< "  PUSH 1\n"
				<< "  JMP " << M1 << "\n"
				<< M2 << ": PUSH 0\n"
				<< M1 << ":\n";
		}
		//}
	}
	else if (T == 'R' && j == 18) {		//#E Zn E#
		//генерация кода {
		string S = "";	//переменная для оператора сравнения
		//}

		E();
		Zn(S);
		E();

		//генерация кода {
		string M1 = GetMarkerNumber();
		string M2 = GetMarkerNumber();
		fout << "  ;comparison\n"
			<< "  POP BX\n"
			<< "  POP AX\n"
			<< "  CMP AX, BX\n"
			<< "  " << S << " " << M2 << "\n"
			<< "  PUSH 1\n"
			<< "  JMP " << M1 << "\n"
			<< M2 << ": PUSH 0\n"
			<< M1 << ":\n";
		//}

		MyLeks.Scan(T,j);
		if (!(T == 'R' && j == 18)) {
			ERR(0);
		}
	}
	else if (T == 'R' && j == 9) {		//(Lg)
		Lg();
		MyLeks.Scan(T,j);
		if (!(T == 'R' && j == 8)) {
			ERR(0);
		}
	}
	else {
		ERR(0);
	}
}

void Zn(string &S) {
	MyLeks.Scan(T,j);
	if (T == 'R') {
		switch (j) {
		case 10:  	// >
			S = "JLE";
			break;
		case 11:	// <
			S = "JGE";
			break;
		default:
			ERR(0);
			break;
		}
	}
	else if (T == 'D') {
		switch (j) {
		case 0:		// ==
			S = "JNE";
			break;
		case 1:		// >=
			S = "JL";
			break;
		case 2:		// <=
			S = "JG";
			break;
		case 3:		// <>
			S = "JE";
			break;
		default:
			ERR(0);
			break;
		}
	}
	else {
		ERR(0);
	}
}

void GenerateKod_Data(vector<TableOfIdent> I, vector<string> L) {
	string S;

	fout << ".data\n";
	for (size_t i = 0; i < I.size(); i++)
	{
		if (I[i].type == -3) {	//проверка на имя программы
			continue;
		}

		S = "  " + I[i].name + "   D";
		if (I[i].type == 39 || (I[i].type == -2 && I[i].ArrayType == 39)) {
			S += "W   ";
		}
		else {
			S += "B   ";
		}

		if (I[i].type == -2) {
			S += to_string(I[i].ArraySize);
			S += "   DUP";
		}

		S += "  (?)\n";

		fout << S;
	}
	for (size_t i = 0; i < L.size(); i++)
	{
		S = "  @L" + to_string(i) + "   DB \"" + L[i] + "$\"\n";
		fout << S;
	}
	fout << "  crlf db 0Dh, 0Ah, '$'\n"
		<< "  buffer_write db 20 dup (?),'$'\n"
		<< "  buffer db 20\n"
		<< "  blength db ?\n"
		<< "  bcontents db 20 dup (?)\n";
}

void GenerateKod_Proc()
{
	fout << "read_chislo proc \n" 
		<< "  xor ax, ax\n"
		<< "  mov cl, blength\n"
		<< "  xor ch, ch\n"
		<< "  xor bx, bx\n"
		<< "  mov si, cx\n"
		<< "  mov cl, 10\n"
		<< "Read1:\n"
		<< "  cmp di, si\n"
		<< "  ;if error\n"
		<< "  ja End1\n"
		<< "  mov bl, byte ptr bcontents[di]\n"
		<< "  inc di\n"
		<< "  sub bl, '0'\n"
		<< "  jb Read1\n"
		<< "  cmp bl, 9\n"
		<< "  ja Read1\n"
		<< "Read2:\n"
		<< "  mul cx\n"
		<< "  add ax, bx\n"
		<< "  mov bl, byte ptr bcontents[di]\n"
		<< "  sub bl, '0'\n"
		<< "  jb End1\n"
		<< "  cmp bl, 9\n"
		<< "  ja End1\n"
		<< "  inc di\n"
		<< "  jmp Read2\n"
		<< "End1:\n"
		<< "  ret\n"
		<< "read_chislo endp\n";

	fout << "write_chislo proc \n"
		<< "  mov cx, 10000\n"
		<< "  xor bp, bp\n"
		<< "  xor si, si\n"
		<< "Loop1 :\n"
		<< "  xor dx, dx\n"
		<< "  div cx\n"
		<< "  ; проверка на первые нули\n"
		<< "  cmp ax, 0\n"
		<< "  jnz WriteInBuf\n"
		<< "  cmp bp, 0\n"
		<< "  jnz WriteInBuf\n"
		<< "  jmp Div10\n"
		<< "WriteInBuf :\n"
		<< "  mov bp, 1; взводим флаг\n"
		<< "  add ax, '0'\n"
		<< "  mov byte ptr buffer_write[di], al\n"
		<< "  inc si\n"
		<< "  inc di\n"
		<< "Div10 :\n"
		<< "  cmp cx, 1\n"
		<< "  jz ifZero\n"
		<< "  mov ax, cx\n"
		<< "  mov cx, dx\n"
		<< "  xor dx, dx\n"
		<< "  mov bx, 10\n"
		<< "  div bx\n"
		<< "  mov bx, ax\n"
		<< "  mov ax, cx\n"
		<< "  mov cx, bx\n"
		<< "  jmp Loop1\n"
		<< "ifZero :\n"
		<< "  cmp si, 0\n"
		<< "  jnz End2\n"
		<< "  mov byte ptr buffer_write[di], '0'\n"
		<< "  inc di;\n"
		<< "End2:\n"
		<< "  ret\n"
		<< "write_chislo endp\n";
}

string GetMarkerNumber()
{
	MarkerCounter++;
	return "@M" + to_string(MarkerCounter);
}

bool E_Follow() {
	if ((T == 'R' && (j == 8 || j == 13 || j == 14 || j == 10 || j == 11 || j == 16 || j == 17 || j == 2 || j == 1 || j == 18)) ||
		(T == 'D' && (j == 0 || j == 1 || j == 2 || j == 3))) {
		return true;
	}
	else {
		return false;
	}
}

void ERR(int kod) {
	cout << endl << "Ошибка!" << endl;
	cout << "Встречен: " << MyLeks.GetBuf() << endl;
	switch(kod){
		case 0: {
			break;
		}
		case 1: {
			cout << "Ожидалось название программы!" << endl;
			break;
		}
		case 2: {
			cout << "Ожидался Declare!" << endl;
			break;
		}
		case 3: {
			cout << "Неизвестный тип данных!" << endl;
			break;
		}
		case 4: {
			cout << "Ожидалось число!" << endl;
			break;
		}
		case 5: {
			cout << "Ожидалось закрытие квадратной скобки!" << endl;
			break;
		}
		case 6: {
			cout << "Ожидался идентификатор!" << endl;
			break;
		}
		case 7: {
			cout << "Ожидалась запятая, точка с запятой или main!" << endl;
			break;
		}
		case 8: {
			cout << "Ожидался main!" << endl;
			break;
		}
		/*
		case 0: {
			cout << "Ожидалось название программы!" << endl;
			break;
		}*/
	}
	exit(0);
}
