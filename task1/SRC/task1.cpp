#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace std;

string itoBase(unsigned int nb, string base)
{
    int len = base.size();
    int div=-1, mod=-1,um = nb;
    stack<unsigned> remainder;
    while(div != 0)
    {
        mod = um % len;
        div = um / len;
        um = div;
        remainder.push(mod);
    }
    string ret="";
    while(!remainder.empty())
    {
       ret += base.at(remainder.top());
       remainder.pop();
    }
    return ret;
}

string itoBase(string nb, string baseSrc, string baseDst)
{
    size_t len = baseSrc.size();
    size_t lennb = nb.size();
    int res10=0;
    for(size_t i=0;i<lennb;++i)
    {
        res10 = res10 * len + baseSrc.find(nb.at(i));
    }
    return itoBase(res10,baseDst);
}

void showusage()
{
    cout << "Используйте следующие форматы для вызова программы:"<<endl;
    cout <<"\"Натуральное_число_в_10_системе_счисления\" \"алфавит_системы_счисления_назначения\"" << endl;
    cout <<"или"<<endl;
    cout <<"\"Строка_в_исходной_системе_счисления\" \"алфавит_исходной_системы_счисления\" \"алфавит_системы_счисления_назначения\"" << endl;
    cout <<"Например: .\main.exe 123456789 01234567890abcdef" << endl;
    cout <<"result: 51f2021"<<endl;
    cout << "Или: .\main.exe koty kotiky sobachki"<< endl;
    cout <<"result: kh"<<endl;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");
    if ((argc<3)||(argc>4))//check for the number of arguments
    {
        cout << "Не хватает аргументов." << endl;
        showusage();
        return 1;
    }
    if(strlen(argv[2])==1)//validation of the number system
    {
        cout << "Алфавит системы счисления не может состоять из единственного символа." << endl;
        showusage();
        return 2;
    }
    if(argc==3)
    {
        if(atoi(argv[1])<0)//check for negative numbers
        {
            cout << "Требуется положительное число." << endl;
            showusage();
            return 0;
        }
        if(atoi(argv[1])==0)//checking the translated number for the presence of only numeric characters
        {
            cout << "Введенное число не является десятичным." << endl;
            showusage();
            return 0;
        }
        cout << "result: " << itoBase(atoi(argv[1]),string(argv[2])) << endl;
    }
    if(argc==4)
    {
        if(strlen(argv[3])==1)//validation of the number system
        {
            cout << "Алфавит системы счисления не может состоять из единственного символа." << endl;
            showusage();
            return 0;
        }
        for(size_t i = 0;i<(strlen(argv[1]));i++)//checking the occurrence of all characters of the translated string in the string with the original number system
        {
            if(string(argv[2]).find(argv[1][i])==string::npos)
            {
                cout << "В переводимой строке имеются символы, отсутствующие в алфавите исходной системы счисления." << endl;
                showusage();
                return 0;
            }
        }
        cout << "result: " << itoBase(string(argv[1]),string(argv[2]),string(argv[3])) << endl;
    }
     return 0;
}
