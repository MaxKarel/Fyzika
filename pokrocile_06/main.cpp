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

        Ked riesim y''=12x^2 je dolezite si spravne vytvorit funkcie f_1 a f_2
          y=y1=x^4
          f1=y2=4x^3
          f2=y3=12x^4
          Pouzijem return yn+(k[0][1]+2.0*k[1][1]+2.0*k[2][1]+k[3][1])/6.0; tak dostanem funkciu ktora f(10)=4000
          a ked    return yn+(k[0][0]+2.0*k[1][0]+2.0*k[2][0]+k[3][0])/6.0; tak dostanem funkciu ktora f(10)=10000

        Harmonicky oscilator:

        Budeny nelinearny oscilator:

        Budeny harmonicky oscilator:

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
//double y1(double, double, double);

void xna4(); //priklad y=x^4
void harmonicky_oscilator();
void budeny_harmonicky_oscilator();
void budeny_nelinearny_oscilator();

double f1(double,double,double,double); // prva zlozka vekktorovej funkcie
double f2(double,double,double,double);
double f3(double,double,double,double);
void viacrovnic(double, double);
double k [4][3];
double y [3];


void viacrovnic(double h, double x){

    k[0][0]=h*f1(x,y[0],y[1],y[2]);
    k[0][1]=h*f2(x,y[0],y[1],y[2]);
    k[0][2]=h*f3(x,y[0],y[1],y[2]);
    k[1][0]=h*f1(x+0.5*h,y[0]+0.5*k[0][0],y[1]+0.5*k[0][1],y[2]+0.5*k[0][2]);
    k[1][1]=h*f2(x+0.5*h,y[0]+0.5*k[0][0],y[1]+0.5*k[0][1],y[2]+0.5*k[0][2]);
    k[1][2]=h*f3(x+0.5*h,y[0]+0.5*k[0][0],y[1]+0.5*k[0][1],y[2]+0.5*k[0][2]);
    k[2][0]=h*f1(x+0.5*h,y[0]+0.5*k[1][0],y[1]+0.5*k[1][1],y[2]+0.5*k[1][2]);
    k[2][1]=h*f2(x+0.5*h,y[0]+0.5*k[1][0],y[1]+0.5*k[1][1],y[2]+0.5*k[1][2]);
    k[2][2]=h*f3(x+0.5*h,y[0]+0.5*k[1][0],y[1]+0.5*k[1][1],y[2]+0.5*k[1][2]);
    k[3][0]=h*f1(x+h,y[0]+k[2][0],y[1]+k[2][1],y[2]+k[2][2]);
    k[3][1]=h*f2(x+h,y[0]+k[2][0],y[1]+k[2][1],y[2]+k[2][2]);
    k[3][2]=h*f3(x+h,y[0]+k[2][0],y[1]+k[2][1],y[2]+k[2][2]);
    y[0]=y[0]+(1.0/6.0)*(k[0][0]+2*k[1][0]+2*k[2][0]+k[2][0]);
    y[1]=y[1]+(1.0/6.0)*(k[0][1]+2*k[1][1]+2*k[2][1]+k[2][1]);
    y[2]=y[2]+(1.0/6.0)*(k[0][2]+2*k[1][2]+2*k[2][2]+k[2][2]);
}
double f1(double x,double y1,double y2,double y3){
    //return 4.0*x*x*x; // pre y=x^4
    return y2; // budeny nelinearny oscilator a harmoniccky oscilator
}
double f2(double x,double y1,double y2,double y3){
    //return 12.0*x*x;  // pre y=x^4
    //return -4.0*M_PI*M_PI*y1-0.1*y2; //harmonicky oscilator s trenim
    //return -4.0*M_PI*M_PI*y1; //harmonicky oscilator bez trenia
    return -0.05*y2 - y1*y1*y1 + 7.5*cos(x); // budeny nelinearny oscilator
    //return -0.1*2*M_PI*y2-4*M_PI*M_PI*y1+sin(0.99*2*M_PI*x);
}
double f3(double x,double y1,double y2,double y3){
    return y2*sin(0.99*2*M_PI*x);
}
int main()
{
    budeny_nelinearny_oscilator();
    return 0;
}
void xna4() {
    ofstream fout("data.dat");
    y[0]=0;
    y[1]=0;
    double h=0.2;
    for(double i=0;i<10.0;i+=h) {
        fout<<i<<'\t'<<y[0]<<endl;
        viacrovnic(h,i);
    }
    fout.close();
    system("xmgrace data.dat");
}
void harmonicky_oscilator() {
    ofstream fout("data.dat");
    y[0]=0;
    y[1]=1;
    double h=0.0001;
    for(double i=0;i<50.0;i+=h) {
        if (fmod(i,0.001)<=0.0001) {fout<<y[0]<<'\t'<<y[1]<<endl;}
        viacrovnic(h,i);
    }
    fout.close();
    system("xmgrace data.dat");
}
void budeny_harmonicky_oscilator() {
    ofstream fout("data.dat");
    y[0]=0;
    y[1]=0;
    y[3]=0;
    double h=0.0001;
    for(double i=0;i<50.0;i+=h) {
        if (fmod(i,0.001)<=0.0001) {fout<<y[0]<<'\t'<<y[1]<<endl;}
        viacrovnic(h,i);
    }
    fout.close();
    system("xmgrace data.dat");
}
void budeny_nelinearny_oscilator() {
    ofstream fout("data.dat");
    y[0]=0.0;
    y[1]=1.0;
    double h=2*M_PI/1000.0;
    //for (int j=0;j<1000;j++) {
    for(double i=0;i<1000.0;i+=h) {
        viacrovnic(h,i);
        if (fmod(i,0.005)<=0.003) {
            fout<<y[0]<<'\t'<<y[1]<<endl;
        }
    //}
    //fout<<y[0]<<'\t'<<y[1]<<endl;
    }
    fout.close();
    system("xmgrace data.dat");
}

//ukazkovy priklad pre jednu diferencialnu rovnicu
/*
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
*/
