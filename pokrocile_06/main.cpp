/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA 6 - Diferencialne Rovnice
    Ulohy:
        1. Vyrieste jednoduchu diferencialnu rovnicu dy/dx=4x^3 pomocou RK
        2. Vyrieste sustavu DR pomocou RK (harmonicky oscilator)
        3. Vyrieste jeden z fyziklnych problemov pomocou RK:
            a. Budený harmonický oscilátor s trením
            b. Nelineárne kyvadlo
            c. Brownov pohyb
            d. Metóda streľby
    Poznamky k teorii:
        diferencialne rovnice vime priblizne pocitat cez iteracne schemy: kde najjednoduchsie pribliznie je y_n+1=y_n+ maly_krok*derivacia
        Lepsi sposob je pouzit Runge-Kutta algoritmy.
        Sucet premennych k su v podstate maly_krok*derivacia.

        Pociatocne podmienky stanovim ako hodnoty funkci v bode x0

        Ked riesim y''=12x^2 je dolezite si spravne vytvorit funkcie f_1/2
          y=y1=x^4
          f1=y2=4x^3
          f2=y3=12x^4
          Pouzijem return yn+(k[0][1]+2.0*k[1][1]+2.0*k[2][1]+k[3][1])/6.0; tak dostanem funkciu ktora f(10)=4000
          a ked    return yn+(k[0][0]+2.0*k[1][0]+2.0*k[2][0]+k[3][0])/6.0; tak dostanem funkciu ktora f(10)=10000

        Harmonicky oscilator:

        Budeny nelinearny oscilator:


************************************************************/
#include <iostream>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;
double f(double,double); //derivacia rovnice x^4
double k1,k2,k3,k4;
double y1(double, double, double);

void xna4(); //priklad y=x^4
void harmonicky_oscilator();
void budeny_nelinearny_oscilator();

double f1(double,double); // prva zlozka vekktorovej funkcie
double f2(double,double);
double f3(double,double);
void viacrovnic(double, double);
double k [4][3];
double ynn [4];

void viacrovnic(double h, double xn){
    for (int i=0;i<4;i++) {
        for (int j=0;j<2;j++) {
            switch (i) {
            case 0: switch (j) {
                    case 0: k[i][j]=h*f1(xn,ynn[j]);
                            break;
                    case 1: k[i][j]=h*f2(xn,ynn[j]);
                            break;
                    case 2: k[i][j]=h*f3(xn,ynn[j]);
                            break;
                    }
                    break;
            case 1: switch (j) {
                    case 0: k[i][j]=h*f1(xn+0.5*h,ynn[j]+0.5*k[0][j]);
                            break;
                    case 1: k[i][j]=h*f2(xn+0.5*h,ynn[j]+0.5*k[0][j]);
                            break;
                    case 2: k[i][j]=h*f3(xn+0.5*h,ynn[j]+0.5*k[0][j]);
                            break;
                    }
                    break;
            case 2: switch (j) {
                    case 0: k[i][j]=h*f1(xn+0.5*h,ynn[j]+0.5*k[1][j]);
                            break;
                    case 1: k[i][j]=h*f2(xn+0.5*h,ynn[j]+0.5*k[1][j]);
                            break;
                    case 2: k[i][j]=h*f3(xn+0.5*h,ynn[j]+0.5*k[1][j]);
                            break;
                    }
                    break;
            case 3: switch (j) {
                    case 0: k[i][j]=h*f1(xn+h,ynn[j]+k[2][j]);
                            break;
                    case 1: k[i][j]=h*f2(xn+h,ynn[j]+k[2][j]);
                            break;
                    case 2: k[i][j]=h*f3(xn+h,ynn[j]+k[2][j]);
                            break;
                    }
                    break;
            }
        }
    }

    for (int i=0;i<2;i++) {
        ynn[i]=ynn[i]+(k[0][i]+2.0*k[1][i]+2.0*k[2][i]+k[3][i])/6.0;
    }
}
double f1(double x, double y){
    //return 4.0*x*x*x; // pre y=x^4
    //return ynn[1]; //harmonicky oscilator
    return ynn[1]; // budeny nelinearny oscilator
}
double f2(double x, double y){
    //return 12.0*x*x;  // pre y=x^4
    //return -4.0*M_PI*M_PI*ynn[0]+0.8*ynn[1]; //harmonicky oscilator s trenim
    //return -4.0*M_PI*M_PI*ynn[0]; //harmonicky oscilator bez trenia
    return 7.5*sin(x)-0.05*ynn[1]-pow(ynn[0],3); // budeny nelinearny oscilator
}
double f3(double x, double y){
    return -y;
}
int main()
{
    budeny_nelinearny_oscilator();
    return 0;
}


void xna4() {
    ofstream fout("data.dat");
    ynn[0]=0;
    ynn[1]=0;
    double h=0.2;
    for(double i=0;i<10.0;i+=h) {
        fout<<i<<'\t'<<ynn[0]<<endl;
        viacrovnic(h,i); //priklad pre viac rovnic
        //yn=y1(yn,h,i); //priklad pre jednu dif rovnicu
    }
    fout.close();
    system("xmgrace data.dat");
}
void harmonicky_oscilator() {
    ofstream fout("data.dat");
    ynn[0]=0;
    ynn[1]=1;
    double h=0.001;
    for(double i=0;i<5.0;i+=h) {
        fout<<ynn[0]<<'\t'<<ynn[1]<<endl;
        viacrovnic(h,i);

    }
    fout.close();
    system("xmgrace data.dat");
}
void budeny_nelinearny_oscilator() {
    ofstream fout("data.dat");
    ynn[0]=0;
    ynn[1]=1;
    double h=2*M_PI/1000;
    for(double i=0;i<2000.0;i+=h) {
        if (fmod(i,M_PI)<=0.001) {
            fout<<ynn[0]<<'\t'<<ynn[1]<<endl;
        }
        viacrovnic(h,i);

    }
    fout.close();
    system("xmgrace data.dat");
}

//ukazkovy priklad pre jednu diferencialnu rovnicu
double y1(double yn, double h, double xn){
    k1=h*f(xn,yn);
    k2=h*f(xn+0.5*h,yn+0.5*k1);
    k3=h*f(xn+0.5*h,yn+0.5*k2);
    k4=h*f(xn+h,yn+k3);
    return yn+(k1+2.0*k2+2.0*k3+k4)/6.0;
}
double f(double x, double y){
    return 4.0*x*x*x;
}
