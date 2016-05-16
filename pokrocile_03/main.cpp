/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA 3 - Nelinearne iteracne schemy, chaos, fraktaly
    Ulohy:
        1. napíšte program pre nelineárnu schému (May)
        2. zostrojte pravdepodobnostné rozdelenie p(x), ukážte jeho
        self-podobnosť
        3. nájdite fraktálnu dimenziu
    Poznamky k teorii:
        ak je iteracna schema x_n+1=f(x_n) tak pri istych funkciach f a
        spravnych konstantach osciluje hodnota x_n okolo niakych hodnot.
        Pomocou pola h mozeme vidiet, ktore hodnoty sa najcastejsie opakuju (su periodicke).
        Pomocou pola N mozeme sledovat fraktalnu dimenziu pola h. Postupne delime interval M na 2^m casti
        a pripocitame do pola N vzdu ked ta cast obsahuje aspon jednu nenulovu hodnotu


************************************************************/
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <complex>
using namespace std;
const int M = 1000000;
double funkcia(double, double);

int main()
{
    /*double help;
    ifstream fin("data.dat");
    for (int i=0;i<M;i++){
        fin >> help;
        fin >> h[i];
    }
    fin.close();*/
    int index;
    double h[M]; // pocetnost zaokruhlenych hodnot x_n
    for (int i=0;i<M;i++) {h[i]=0;}
    ofstream fout("data.dat");
    double xp;
    double x=0.5;
    for (int i=0;i<10E7;i++) {
        xp = funkcia(3.56995,x);
        index = (int(xp*M)+1);
        h[index]++;
        x=xp;
    }
    for (int i=0;i<M;i++) {
        fout << (double)i/M << "\t" <<h[i] <<endl;
    }
    int N[23];
    ofstream fout2("data2.dat");
    for (int m=2;m<=16;m++) {
        N[m]=0;
        for (int j=0;j<=pow(2,m)-1;j++) {
            for (int k=int(j*(M/pow(2,m)));k<=int((j+1)*(M/pow(2,m)));k++) {
                if (h[k]>0) {
                    N[m]++;
                    break;
                }
            }
        }
        fout2 << log(pow(2,m)) << "\t" << log(N[m])<<endl;
    }
    fout2.close();
    system("xmgrace data2.dat");
    return 0;
}
double funkcia(double l, double x) { //lambda
    return l*x*(1-x);
}
