#include <iostream>
#include "NagyEgesz.h"

using namespace std;     

NagyEgesz operator+(int a, const NagyEgesz& b)
{
    return b + a;
}

int main()
{
    int a1 = 100000;
    int b1 = -12345;
    int c1[20] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 0 ,0 };
    int d1[11] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    NagyEgesz a(a1);
    NagyEgesz b(b1);
    NagyEgesz c(-1, 20, c1);
    NagyEgesz d(-1, 11, d1);
    NagyEgesz e(-17);
    NagyEgesz f(0);

    cout << "a= " << a;
    cout << "b= " << b;
    cout << "c= " << c;
    cout << "d= " << d;
    cout << "e= " << e;
    cout << "f= " << f << endl;

    cout << "a + b = " << 6 + a;
    cout << "a - b = " << a - b;
    cout << "++a = " << ++a;
    cout << "a-- = " << a--;
    cout << "a= " << a;
    cout << "a * b = " << a * b;
    cout << "c = " << c;
    cout << "c / a = " << c / a;
    cout << "d = " << d;
    cout << "c * d = " << c * d;
    cout << "a / e = " << a / e;
    cout << "-a = " << -a;
    try
    {
        cout << "d / f = " << d / f;
    }
    catch (NagyEgesz::NullavalValoOsztas)
    {
        cout << "Nullaval probaltal osztani" << endl;
    }

    return 0;
}
