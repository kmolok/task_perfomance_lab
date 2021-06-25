#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

struct point
{
    double X , Y , Z ;
};

struct sphere
{
    point c;
    double r;
};

struct line
{
    point d1, d2;
};

struct retpoints
{
    bool flag;
    point p1, p2;
};

point pointfromstring(string s)
{
    point ret = {0,0,0};
    size_t poscomma,poscomm,poscom;
    string sx = "";
    string sy = "";
    string sz = "";
    poscomma = s.find(",");
    sx.insert(0,s,1,poscomma-1);
    poscomm = s.find(",",poscomma+1);
    sy.insert(0,s,poscomma+2,poscomm-poscomma-2);
    poscom = s.find("]",poscomm+1);
    sz.insert(0,s,poscomm+2,poscom-poscomm-2);
    ret.X = atof(sx.c_str());
    ret.Y = atof(sy.c_str());
    ret.Z = atof(sz.c_str());
    return ret;
}

sphere find_sphere(string s)
{
    sphere sph;
    size_t posobr,poscbr;
    posobr = s.find("sphere: {");
    poscbr = s.find("}",posobr);
    string sp = "";
    sp.insert(0,s,posobr+9,poscbr-posobr-9);//sizeof("sphere: {") = 9
    sp += ",";
    posobr = sp.find("center: [");
    poscbr = sp.find("]",posobr);
    string ce = "";
    ce.insert(0,sp,posobr+8,poscbr-posobr-7);
    sph.c = pointfromstring(ce);
    posobr = sp.find("radius: ");
    poscbr = sp.find(",",posobr);
    string ra = "";
    ra.insert(0,sp,posobr+8,poscbr-posobr-8);
    sph.r = atof(ra.c_str());
    return sph;
}

line find_line(string s)
{
    line ln;
    size_t posobr,poscbr;
    posobr = s.find("line: {");
    poscbr = s.find("}",posobr);
    string sp = "";
    sp.insert(0,s,posobr+7,poscbr-posobr-7);
    sp += ",";
    posobr = sp.find("[");
    poscbr = sp.find("]",posobr);
    string p1 = "";
    p1.insert(0,sp,posobr,poscbr-posobr+1);
    ln.d1 = pointfromstring(p1);
    posobr = sp.find(", [");
    poscbr = sp.find("]",posobr);
    string p2 = "";
    p2.insert(0,sp,posobr+2,poscbr-posobr-1);
    ln.d2 = pointfromstring(p2);
    return ln;
}

retpoints find_collision(double rs, point lcs, point l1, point l2)
{
    double A, B, C, D, t1, t2;
    retpoints s;
    s.flag=false;
    A = (((l2.X-l1.X)*(l2.X-l1.X))+((l2.Y-l1.Y)*(l2.Y-l1.Y))+((l2.Z-l1.Z)*(l2.Z-l1.Z)));
    B = 2 * (((l1.X-lcs.X)*(l2.X-l1.X))+((l1.Y-lcs.Y)*(l2.Y-l1.Y))+((l1.Z-lcs.Z)*(l2.Z-l1.Z)));
    C = (((l1.X-lcs.X)*(l1.X-lcs.X))+((l1.Y-lcs.Y)*(l1.Y-lcs.Y))+((l1.Z-lcs.Z)*(l1.Z-lcs.Z)))-rs*rs;
    D = B * B - 4 * A * C;
    if(D>=0)
    {
        t1=(-B + sqrt(D))/(2*A);
        t2=(-B - sqrt(D))/(2*A);
        point q1 {(l1.X+(l2.X-l1.X)*t1),(l1.Y+(l2.Y-l1.Y)*t1),(l1.Z+(l2.Z-l1.Z)*t1)};
        point q2 {(l1.X+(l2.X-l1.X)*t2),(l1.Y+(l2.Y-l1.Y)*t2),(l1.Z+(l2.Z-l1.Z)*t2)};
        s = {true,q1,q2};
    }
        return s;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");
    if (argc<2)
    {
        cout << "Файл не может быть открыт!\n";
        return 1;
    }
    string fn = string(argv[1]);
    ifstream fin(fn);
    if (!fin.is_open()) // если файл не открыт
        {
            cout << "Файл не может быть открыт!\n";
            return 2;
        }
    retpoints rtp;
    string s = "";
    while(getline(fin,s))
    {
        sphere sp = find_sphere(s);
        line ln = find_line(s);
        rtp = find_collision(sp.r,sp.c,ln.d1,ln.d2);
        if (rtp.flag)
        {
            cout << "Точки столкновения: [" << rtp.p1.X << ", " << rtp.p1.Y << ", " << rtp.p1.Z << "] и [" << rtp.p2.X << ", " << rtp.p2.Y << ", " << rtp.p2.Z << "]" << endl;
        }
        else
        {
            cout << "Коллизий не найдено" << endl;
        }
    }
    fin.close();
    return 0;
}
