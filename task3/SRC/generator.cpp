#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

string ctimetomystring(string s)
{
    string year = "";
    year.insert(0,s,20,4);
    string mounth = "";
    mounth.insert(0,s,4,3);
    if(mounth == "Jan")
        mounth = "01";
    else if(mounth == "Feb")
        mounth = "02";
    else if(mounth == "Mar")
        mounth = "03";
    else if(mounth == "Apr")
        mounth = "04";
    else if(mounth == "May")
        mounth = "05";
    else if(mounth == "Jun")
        mounth = "06";
    else if(mounth == "Jul")
        mounth = "07";
    else if(mounth == "Aug")
        mounth = "08";
    else if(mounth == "Sep")
        mounth = "09";
    else if(mounth == "Oct")
        mounth = "10";
    else if(mounth == "Nov")
        mounth = "11";
    else if(mounth == "Dec")
        mounth = "12";
    string day = "";
    day.insert(0,s,8,2);
    string hour = "";
    hour.insert(0,s,11,2);
    string minute = "";
    minute.insert(0,s,14,2);
    string second = "";
    second.insert(0,s,17,2);
    string ns = year + "-" + mounth + "-" + day + "T" + hour + ":" + minute + ":" + second;
    return ns;
}


int main(int argc, char *argv[])
{
    srand(clock());
    setlocale(LC_ALL, "rus");
    if (argc<2)
    {
        cout << "Файл не может быть открыт!\n";
        return 1;
    }
    string fn = string(argv[1]);
    ofstream fout(fn, ios_base::out | ios_base::trunc);
    if (!fout.is_open()) // если файл не открыт
        {
            cout << "Файл не может быть открыт!\n";
            return 2;
        }
    int clk,un,act,cnt,volume = 200,now_count = 32,try_count =0 ;
    string s = "META DATA:";
    fout << s << endl << volume << " (объем бочки)" << endl << now_count << " (текущий объем воды в бочке)" ;
    time_t rawtime;
    time ( &rawtime );

    string st = string(ctime(&rawtime));
    cout << st << endl;
    st = string(ctime(&rawtime));
    cout << st << "test" << endl<<endl<<endl;
    string nst = ctimetomystring(st);
    for(int i = 0;i<16000;++i)
    {
        st = ctimetomystring(string(ctime(&rawtime)));
        st = st + ".";
        clk = (rand()*RAND_MAX)%900;
        un = (rand()*RAND_MAX)%20;
        act = (rand()*RAND_MAX)%2;
        cnt = (rand()*RAND_MAX)%volume;
        rawtime += clk;
        st = st + to_string(clk) + "Z" + " - [username";
        st = st + to_string(un) + "]" ;
        st = st + " - wanna ";
        if(act)
        {
            st = st + "top up ";
        }
        else
        {
            st = st + "scoop ";
        }
        st = st + to_string(cnt) + "l ";
        try_count = now_count;
        if(act)
        {
            try_count += cnt;
            if(try_count>volume)
            {
                st = st + "(феил)";
            }
            else
            {
                st = st + "(успех)";
                now_count = try_count;
            }
        }
        else
        {
            try_count -= cnt;
            if(try_count<0)
            {
                st = st + "(феил)";
            }
            else
            {
                st = st + "(успех)";
                now_count = try_count;
            }
        }
        cout << st << endl;
        fout << endl << st;
    }
    fout.close();
    return 0;
}
