#include "Leks.h"

Leks::Leks(string file_name) {
	Open(file_name);
    S = 1;
    pos = 0;
    flag_scp = false;
    Initialization();
}

void Leks::Scan(char& T, int& j)
{
    flag_scp = false;
    Scaning();
    T = this->T;
    j = this->j;
}

void Leks::Scp(char& T, int& j)
{
    if (flag_scp) {
        T = this->T;
        j = this->j;
        return;
    }
    flag_scp = true;
    string str = s;
    int old_pos = pos;
    Scaning();
    T = this->T;
    j = this->j;
    if (str != s) pos = 0;
    else pos = old_pos;
}

void Leks::Scaning()
{
    char b;
    while (true) {
        bool flag_comment = false;
        while (pos < (int)s.length() && !flag_comment) {
            b = s[pos];
            pos++;
            switch (S) {
                case 0: {
                    int temp = Find(R, '$');
                    if (temp != -1) {
                        T = 'R';
                        j = temp;
                        pos--;
                        return;
                    }
                    else {
                        Read.close();
                        cout << endl << "Ошибка!" << endl <<
                            "Лексическая ошибка. Символ конца файла <$> не добавлен в список однолитерных разделителей." << endl;
                        exit(0);
                    }
                    break;
                }
                case 1: {
                    if (if_Bukva(b)) {
                        S = 2;
                        buf = b;
                    }
                    else if (if_Cifra(b)) {
                        S = 3;
                        buf = b;
                    }
                    else if (b == '\'') {
                        S = 4;
                        buf = "";
                    }
                    else if (b == '/') {
                        S = 6;
                        buf = b;
                    }
                    else if (b == '$') {
                        S = 0;
                        buf = b;
                        pos--;
                    }
                    else if (Find(R, b) != -1) {
                        S = 9;
                        buf = b;
                    }
                    else if (b == ' ') {
                        //ничего не делаем
                    }
                    else {
                        Read.close();
                        cout << endl << "Ошибка!" << endl <<
                            "Лексическая ошибка. Встречен неизвестный символ <" << b << ">." << endl;
                        exit(0);
                    }
                    break;
                }
                case 2: {
                    if (if_Cifra(b) || if_Bukva(b)) {
                        buf += b;
                    }
                    else {
                        Iterator();
                        pos--;
                        S = 1;
                        return;
                    }
                    break;
                }
                case 3: {
                    if (if_Cifra(b)) {
                        buf += b;
                    }
                    else {
                        Chislo();
                        pos--;
                        S = 1;
                        return;
                    }
                    break;
                }
                case 4: {
                    if (b == '$') {
                        Read.close();
                        cout << endl << "Ошибка!" << endl << 
                            "Лексическая ошибка. Ожидалось закрытие литерала." << endl;
                        exit(0);
                    }
                    else if (!(b == '\'')) {
                        buf += b;
                    }
                    else {
                        S = 5;
                    }
                    break;
                }
                case 5: {
                    if (b == '\'') {
                        buf += b;
                        S = 4;
                    }
                    else {
                        Literal();
                        pos--;
                        S = 1;
                        return;
                    }
                    break;
                }
                case 6: {
                    if (b == '/') {
                        flag_comment = true;
                        S = 1;
                    }else if (b == '*') {
                        S = 7;
                    }else {
                        int temp = Find(R, buf[0]);
                        if (temp != -1) {
                            T = 'R';
                            j = temp;
                            S = 1;
                            pos--;
                            return;
                        }
                        else {
                            Read.close();
                            cout << endl << "Ошибка!" << endl <<
                                "Лексическая ошибка. Встречен неизвестный символ <" << buf[0] << ">." << endl;
                            exit(0);
                        }
                    }
                    break;
                }
                case 7: {
                    if (b == '*') {
                        S = 8;
                    }
                    break;
                }
                case 8: {
                    if (b == '/') {
                        S = 1;
                    }
                    else {
                        S = 7;
                    }
                    break;
                }
                case 9: {
                    int temp = Find(D, buf + b);
                    if (temp != -1) {
                        T = 'D';
                        j = temp;
                        S = 1;
                        return;
                    }
                    else {
                        T = 'R';
                        j = Find(R, buf[0]);
                        S = 1;
                        pos--;
                        return;
                    }
                    break;
                }
            }
        }

        if (!flag_scp || (flag_scp && (S == 7 || S == 8 || S == 1))) {
            if (!getline(Read, s)) {		//считваем строку и записываем в s
                Read.close();
                if (S == 7 || S == 8) {
                    cout << endl << "Ошибка!" << endl <<
                        "Лексическая ошибка. Не закрыт многострочный комментарий." << endl;
                    exit(0);
                }
                cout << endl << "Ошибка!" << endl <<
                    "Лексическая ошибка. Нет символа конца файла <$>." << endl;
                exit(0);
            }
            pos = 0;
        }
        

        switch (S) {
            case 2: {
                Iterator();
                S = 1;
                return;
                break;
            }
            case 3: {
                Chislo();
                S = 1;
                return;
                break;
            }
            case 4: {
                cout << endl << "Ошибка!" << endl <<
                    "Лексическая ошибка. Литерал не был закрыт." << endl;
                exit(0);
            }
            case 5: {
                Literal();
                S = 1;
                return;
                break;
            }
            case 6: {
                int temp = Find(R, buf[0]);
                if (temp != -1) {
                    T = 'R';
                    j = temp;
                    S = 1;
                    return;
                }
                else {
                    Read.close();
                    cout << endl << "Ошибка!" << endl <<
                        "Лексическая ошибка. Встречен неизвестный символ <" << buf[0] << ">." << endl;
                    exit(0);
                }
                break;
            }
            case 8: {
                S = 7;
                break;
            }
            case 9: {
                T = 'R';
                j = Find(R, buf[0]);
                S = 1;
                return;
                break;
            }
        }
    }
}

void Leks::Open(string file_name)
{
	Read.open(file_name);		//открытие файла
    if (!(Read.is_open())) {
        cout << "\nFile not find\n";
    }
    else {
        if (!getline(Read, s)) {		//считваем строку и записываем в s
            cout << "\nFile is empty\n";
            Read.close();
        }
    }

}

bool Leks::if_Bukva(char b) {
    if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z')) return true;
    else return false;
}

bool Leks::if_Cifra(char b) {
    if (b >= '0' && b <= '9') return true;
    else return false;
}

void Leks::Iterator()
{
    //
    //cout << buf << endl;
    //
    int temp = Find(K, buf);
    if (temp == -1) {
        T = 'I';
        temp = Find(I, buf);
        if (temp == -1) {
            TableOfIdent tempStruct;
            tempStruct.name = buf;
            tempStruct.type = 0;
            tempStruct.ArraySize = 0;
            tempStruct.ArrayType = 0;
            I.push_back(tempStruct);
            j = I.size() - 1;
        }
        else j = temp;
    }
    else {
        T = 'K';
        j = temp;
    }
}

void Leks::Chislo()
{
    //
    //cout << buf << endl;
    //
    T = 'C';
    int int_str = atoi(buf.c_str());
    int temp = Find(C, int_str);
    if (temp == -1) {
        C.push_back(int_str);
        j = C.size() - 1;
    }
    else j = temp;
}

void Leks::Literal()
{
    //
    //cout << buf << endl;
    //
    T = 'L';
    int temp = Find(L, buf);
    if (temp == -1) {
        L.push_back(buf);
        j = L.size() - 1;
    }
    else j = temp;
}

int Leks::Find(vector<TableOfIdent>& mass, string str)
{
    for (int i = 0; i < (int)mass.size(); i++) {
        if (mass[i].name == str) return i;
    }
    return -1;
}

int Leks::Find(vector<string>& mass, string str)
{
    for (int i = 0; i < (int)mass.size(); i++) {
        if (mass[i] == str) return i;
    }
    return -1;
}

int Leks::Find(vector<char>& mass, char str)
{
    for (int i = 0; i < (int)mass.size(); i++) {
        if (mass[i] == str) return i;
    }
    return -1;
}

int Leks::Find(vector<int>& mass, int str)
{
    for (int i = 0; i < (int)mass.size(); i++) {
        if (mass[i] == str) return i;
    }
    return -1;
}

void Leks::Initialization() {
    //СЧИТЫВАНИЕ КЛЮЧЕВЫХ СЛОВ ИЗ ФАЙЛА
    string s;
    ifstream Key_words("Ключевые слова.txt");
    while (getline(Key_words, s)) { 	// пока не достигнут конец файла класть очередную строку в переменную (s)
        if (Find(K, s) == -1) {	        //проверка на повторение
            K.push_back(s);
        }
    }
    Key_words.close();

    ifstream OdnoLit("Однолитерные разделители.txt");
    while (getline(OdnoLit, s)) {
        if (Find(R, s[0]) == -1) {
            R.push_back(s[0]);
        }
    }
    OdnoLit.close();

    ifstream DvuLit("Двулитерные разделители.txt");
    while (getline(DvuLit, s)) {
        if (Find(D, s) == -1) {
            D.push_back(s);
        }
    }
    DvuLit.close();
}

void Leks::Vivod_all_mass() {
    cout << endl << endl << endl;

    cout << endl << endl << "Итераторы:" << endl;

    for (int i = 0; i < (int)I.size(); i++)
        cout << I[i].name << " ";

    cout << endl << endl << "Числа:" << endl;

    for (int i = 0; i < (int)C.size(); i++)
        cout << C[i] << " ";

    cout << endl << endl << "Литералы:" << endl;

    for (int i = 0; i < (int)L.size(); i++)
        cout << L[i] << " ";

    cout << endl << endl << "Ключевые слова:" << endl;

    for (int i = 0; i < (int)K.size(); i++)
        cout << K[i] << " ";

    cout << endl << endl << "Однолитерные разделители:" << endl;

    for (int i = 0; i < (int)R.size(); i++)
        cout << R[i] << " ";

    cout << endl << endl << "Двулитерные разделители:" << endl;

    for (int i = 0; i < (int)D.size(); i++)
        cout << D[i] << " ";
}

string Leks::GetBuf()
{
    return buf;
}

void Leks::AddType(int num, int type, int C_num, int ArrayType)
{
    I[num].type = type;
    if (type != -2) {
        I[num].ArraySize = 0;
        I[num].ArrayType = 0;
    }
    else {
        I[num].ArraySize = C[C_num];
        I[num].ArrayType = ArrayType;
    }
}

vector<TableOfIdent> Leks::Get_I()
{
    return I;
}

vector<string> Leks::Get_L()
{
    return L;
}
