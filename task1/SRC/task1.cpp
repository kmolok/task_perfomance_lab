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
    cout << "����������� ��������� ������� ��� ������ ���������:"<<endl;
    cout <<"\"�����������_�����_�_10_�������_���������\" \"�������_�������_���������_����������\"" << endl;
    cout <<"���"<<endl;
    cout <<"\"������_�_��������_�������_���������\" \"�������_��������_�������_���������\" \"�������_�������_���������_����������\"" << endl;
    cout <<"��������: .\main.exe 123456789 01234567890abcdef" << endl;
    cout <<"result: 51f2021"<<endl;
    cout << "���: .\main.exe koty kotiky sobachki"<< endl;
    cout <<"result: kh"<<endl;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");
    if ((argc<3)||(argc>4))//check for the number of arguments
    {
        cout << "�� ������� ����������." << endl;
        showusage();
        return 1;
    }
    if(strlen(argv[2])==1)//validation of the number system
    {
        cout << "������� ������� ��������� �� ����� �������� �� ������������� �������." << endl;
        showusage();
        return 2;
    }
    if(argc==3)
    {
        if(atoi(argv[1])<0)//check for negative numbers
        {
            cout << "��������� ������������� �����." << endl;
            showusage();
            return 0;
        }
        if(atoi(argv[1])==0)//checking the translated number for the presence of only numeric characters
        {
            cout << "��������� ����� �� �������� ����������." << endl;
            showusage();
            return 0;
        }
        cout << "result: " << itoBase(atoi(argv[1]),string(argv[2])) << endl;
    }
    if(argc==4)
    {
        if(strlen(argv[3])==1)//validation of the number system
        {
            cout << "������� ������� ��������� �� ����� �������� �� ������������� �������." << endl;
            showusage();
            return 0;
        }
        for(size_t i = 0;i<(strlen(argv[1]));i++)//checking the occurrence of all characters of the translated string in the string with the original number system
        {
            if(string(argv[2]).find(argv[1][i])==string::npos)
            {
                cout << "� ����������� ������ ������� �������, ������������� � �������� �������� ������� ���������." << endl;
                showusage();
                return 0;
            }
        }
        cout << "result: " << itoBase(string(argv[1]),string(argv[2]),string(argv[3])) << endl;
    }
     return 0;
}
