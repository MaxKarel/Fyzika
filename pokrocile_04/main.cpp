/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA 4 - Numericky vypocet integralov
    Ulohy:
        1. Napíšte program pre výpočet periódy kyvadla (algoritmus podľa
        vlastného výberu).
        2. Napíšte program na výpočet numerickej hodnoty integralov erf a erfc
        pomocou Gauss-Legendre polynómu N = 32
    Obsah:
        Jednoduché algoritmy delenia intervalu
        Zložitejšie algoritmy delenia intervalu
        Integrovanie pomocou klasických ortogonálnych polynómov
        Perióda nelineárneho kyvadla
        Funkcie chýb
    Poznamky k teorii:
        Vypocet integralov je zalozeny na odhade plochy tenkeho pasika funkcie jednoduchym geometrickym tvarom.
        Vypocet periody kyvadla:
            periodu urcime z rovnosti energii na zaciatku a v priebehu ako integra dt= f(theta) dtheta
            integral vypocitame pomocou ortogonalnych a gauss-chebyshevovych polunomov


************************************************************/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>

using namespace std;
double T(double);
double F(double,double);

double F(double x,double phi0) {
    return ((sqrt(1-x*x))/sqrt(cos(phi0*x)-cos(phi0)));
}
double T(double phi0) {
    double perioda; // perioda kyvadla z niakym pociatocnym uhlom phi0
    double k = 32; //krok po ktorom prechadzam integral
    double I=0;
    double x;
    /*for (double i=0; i<phi0; i+=M_PI/k) {
        I+=M_PI/(k*sqrt(cos(i)-cos(phi0)));
    }
    //metoda bruteforce = tato metoda dava zauimave vysledky ktoryc dovodom je numericke nepresnosti
    */
    for (double i=0;i<k;i+=1) {
        x=cos((2.0*i-1)*M_PI/(2*k));
        I+=F(x,phi0);
    }
    I*=M_PI/k;
    perioda = 4*sqrt(1/(2*9.81))*I*phi0;
    return perioda;
}

int main()
{
    double T0 = 2*M_PI*sqrt(1/9.81);
    ofstream fout("data.dat");
    for (double i =0+M_PI/100; i<=M_PI; i+=M_PI/100) {
        fout << i/M_PI << "  " << T(i)/T0 << endl;
    }
    fout.close();
    system("xmgrace data.dat");
    return 0;
}
