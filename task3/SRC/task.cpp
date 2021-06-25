#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct parsedstring
{
    int year, mounth, day, hour, minute, second, numuser, act, cntw;
};

struct parseddt
{
    int year, mounth, day, hour, minute, second;
};

parsedstring parsinglogstring(string s)
{
    parsedstring ps;
    string ye = "", mo = "", d = "", h = "", m = "", se = "", nu = "", a = "", cn = "";
    ye.insert(0,s,0,4);
    ps.year = atoi(ye.c_str());
    mo.insert(0,s,5,2);
    ps.mounth = atoi(mo.c_str());
    d.insert(0,s,8,2);
    ps.day= atoi(d.c_str());
    h.insert(0,s,11,2);
    ps.hour = atoi(h.c_str());
    m.insert(0,s,14,2);
    ps.minute = atoi(m.c_str());
    se.insert(0,s,17,2);
    ps.second = atoi(se.c_str());
    size_t posobr,poscbr;
    posobr = s.find("[username");
    poscbr = s.find("]",posobr);
    nu.insert(0,s,posobr+9,poscbr-posobr-9);
    ps.numuser = atoi(nu.c_str());
    size_t posact = s.find("top up");
    if(posact==string::npos)
        ps.act = 0;
    else
        ps.act = 1;
    size_t posl, poscn;
    posl = s.find("l",poscbr);
    poscn = s.rfind(" ",posl);
    cn.insert(0,s,poscn,posl-poscn);
    ps.cntw = atoi(cn.c_str());
    return ps;
}

parseddt parsingdt(string s)
{
    parseddt ps;
    string ye = "", mo = "", d = "", h = "", m = "", se = "", nu = "", a = "", cn = "";
    ye.insert(0,s,0,4);
    ps.year = atoi(ye.c_str());
    mo.insert(0,s,5,2);
    ps.mounth = atoi(mo.c_str());
    d.insert(0,s,8,2);
    ps.day= atoi(d.c_str());
    h.insert(0,s,11,2);
    ps.hour = atoi(h.c_str());
    m.insert(0,s,14,2);
    ps.minute = atoi(m.c_str());
    se.insert(0,s,17,2);
    ps.second = atoi(se.c_str());
    return ps;
}
bool minldt(parseddt l, parseddt r)
{
    if(l.year<r.year)
    {
        return true;
    }
    else if(l.year>r.year)
         {
            return false;
         }
         else
         {
            if(l.mounth<r.mounth)
            {
                return true;
            }
            else if(l.mounth>r.mounth)
                 {
                    return false;
                 }
                 else
                 {
                    if(l.day<r.day)
                    {
                        return true;
                    }
                    else if(l.day>r.day)
                         {
                            return false;
                         }
                         else
                         {
                             if(l.hour<r.hour)
                             {
                                 return true;
                             }
                             else if(l.hour>r.hour)
                                  {
                                      return false;
                                  }
                                  else
                                  {
                                      if(l.minute<r.minute)
                                      {
                                          return true;
                                      }
                                      else if(l.minute>r.minute)
                                            {
                                                return false;
                                            }
                                            else
                                            {
                                                if(l.second<r.second)
                                                {
                                                    return true;
                                                }
                                                else
                                                {
                                                    return false;
                                                }
                                            }
                                   }
                         }
                 }
         }
}


int main(int argc, char *argv[])
{
    string fo = "";
    setlocale(LC_ALL, "rus");
    if (argc<2)
    {
        cout << "Файл не может быть открытv!\n";
        return 1;
    }
    if (argc<4)
    {
        cout << "Укажите период!\n";
        return 2;
    }
    if (argc == 4)
    {
        fo = "log.csv";
    }
    if (argc == 5)
    {
        fo = string(argv[2]);
    }
    string sdtsa = string(argv[2]);//время начала интересующего периода
    string sdtea = string(argv[3]);//время конца интересующего периода
    string s = "";
    ifstream fout1(fo, ios_base::in);
    if(!getline(fout1,s))
    {
        fout1.close();
        ofstream fout1(fo, ios_base::out | ios_base::trunc);
        fout1 << "Попыток налить воду,Процент ошибок,Объем воды был налит,Объем воды был не налит,Попыток забрать воду,Процент ошибок,";
        fout1 << "Объем воды был забран,Объем воды был не забран,Объем воды в начале,Объем воды в конце" << endl;

    }
    fout1.close();
    string fi = string(argv[1]);
    ifstream fin1(fi, ios_base::in);
    ofstream fout(fo, ios_base::app);
    if (!fin1.is_open()) // если файл не открыт
        {
            cout << "Файл не может быть открыт!\n";
            return 3;
        }
    if (!fout.is_open()) // если файл не открыт
        {
            cout << "Файл не может быть открыт!\n";
            return 4;
        }
    string st = "", v = "", ncou = "";
    getline(fin1,s);
    getline(fin1,s);
    getline(fin1,s);
    getline(fin1,s);
    string sdts="";
    sdts.insert(0,s,0,19);//время начала лога
    while(getline(fin1,s)){}
    string sdte="";
    sdte.insert(0,s,0,19);//время конца лога
    bool start = minldt(parsingdt(sdte),parsingdt(sdtsa)),finish = minldt(parsingdt(sdtea),parsingdt(sdts));
    if(start||finish)
    {
        cout << "В заданном диапазоне записей нет!"<< endl;
        return 0;
    }
    fin1.close();
    int volume = 0, now_count = 0,try_count = 0;
    int attemptstop = 0, countertop = 0, voltop = 0, volntop = 0;
    int attemptsscp = 0, counterscp = 0, volscp = 0, volnscp = 0;
    int volumestart = volume, volumefin = volume;
    ifstream fin(fi, ios_base::in);
    getline(fin,s);
    getline(fin,s);
    int posp = s.find(" ");
    v.insert(0,s,0,posp);
    volume = atoi(v.c_str());
    getline(fin,s);
    posp = s.find(" ");
    ncou.insert(0,s,0,posp);
    now_count = atoi(ncou.c_str());
    volumestart = now_count;
    parsedstring ps;
    bool success;
    while(getline(fin,s))
    {
        st = "";
        st.insert(0,s,0,19);
        if((minldt(parsingdt(st),parsingdt(sdtsa)))||(minldt(parsingdt(sdtea),parsingdt(st))))
        {
            continue;
        }
        ps = parsinglogstring(s);
        try_count = now_count;
        if(ps.act)
        {
            try_count = try_count + ps.cntw;
            if(try_count>volume)
            {
                ++attemptstop;
                ++countertop;
                volntop += ps.cntw;
            }
            else
            {
                ++attemptstop;
                voltop += ps.cntw;
                now_count = try_count;
            }
        }
        else
        {
            try_count = try_count - ps.cntw;
            if(try_count < 0)
            {
                ++attemptsscp;
                ++counterscp;
                volnscp += ps.cntw;
            }
            else
            {
                ++attemptsscp;
                volscp += ps.cntw;
                now_count = try_count;
            }
        }
    }
    volumefin = now_count;
    cout << "Попыток налить воду: " << attemptstop << endl;
    fout << attemptstop << ",";
    double persertop = (double(countertop)/double(attemptstop))*100;
    cout << "Процент ошибок: " << persertop << "%" << endl;
    fout << persertop << ",";
    cout << "Объем воды был налит: " << voltop << endl;
    fout << voltop << ",";
    cout << "Объем воды был не налит: " << volntop << endl;
    fout << volntop << ",";
    cout << "Попыток забрать воду: " << attemptsscp << endl;
    fout << attemptsscp << ",";
    double perserscp = (double(counterscp)/double(attemptsscp))*100;
    cout << "Процент ошибок: " << perserscp << "%" << endl;
    fout << perserscp << ",";
    cout << "Объем воды был забран: " << volscp << endl;
    fout << volscp << ",";
    cout << "Объем воды был не забран: " << volnscp << endl;
    fout << volnscp << ",";
    cout << "Объем воды в начале: " << volumestart << endl;
    fout << volumestart << ",";
    cout << "Объем воды в конце: " << volumefin << endl;
    fout << volumefin << endl;
    fout.close();
    return 0;
}
