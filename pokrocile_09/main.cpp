/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA 9 - 2D Isingov model - Glauberova dynamika
    Ulohy:
        1. Napiste program pre Glauberov algoritmus
        2. Simulujte casovy vyvoj
        3. Odhadnite kriticky tepelny bod
    Poznamky k teorii:
        Pole P je pole pravdepodobnosti otocenia sa spinu zavisiace od natocenia okolnych spinov
        okolo kritickej teploty ocakavame celkovu magnetizaciu okolo 0
        template veliciny (pole a magnetizacia) sluzia aby kazda teplota mala rovnaku zaciatocnu podmienku
************************************************************/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
const int n=100;
int l,p,d,h,y,x,sum;  //lavo,pravo,hore,dole
int magnetizacia=0;
bool pole [n][n];
double P [5];

void one_spin(); // funkcia ktora zmeni jeden spin a vrati hodnotu magnetizacie
using namespace std;
int main()
{
    //srand(time(NULL));
    ofstream fout("data.dat");
    double T;
    bool template_grid[n][n];
    double template_magnetizacia=0;
    for  (int i=1;i<6;i++){         //Vypocet pola pravdepodobnosti
        P[i-1]=1/(1+exp((4*i-12)/(T)));
    }
    for (int i= 0;i<n;i++){         //Inicializacia pola a mag
        for (int j=0;j<n;j++){
            if (rand()%2==0) {template_grid[i][j]=0; template_magnetizacia++;}
            else {template_grid[i][j]=1; template_magnetizacia--;}
        }
    }

    cout << template_magnetizacia << "=template magnetizacia" <<endl;
    for (double i=2.0; i<2.4;i+=0.01) {
        magnetizacia=template_magnetizacia;
        for (int j=0;j<n;j++) {
            for (int k=0;k<n;k++) {pole[j][k]=template_grid[j][k];}
        }
        for  (int j=1;j<6;j++){         //Vypocet pola pravdepodobnosti
            P[j-1]=1/(1+exp((4*j-12)/(i)));
        }
        for (int j=0;j<1e7;j++){
            one_spin(); //
        }
        if(abs(magnetizacia)<n*n/100) {fout << "kriticky bod==" << i << "  "<< magnetizacia/n/(double)n<<endl;break;}
    }
    for (int i= 0;i<n;i++){         //Vypis pola
        for (int j=0;j<n;j++){
            if (pole[i][j]) {fout<<" +";}
                else {fout << "  ";}
        }
    fout << endl;
    }
    return 0;
}
void one_spin() {
    x=rand()%(n);
    y=rand()%(n);
    sum=0;
    if(x==0) {l=n-1;} else {l=x-1;}  // sluzi na prepojenie krajovych bodov
    if(x==n-1) {p=0;} else {p=x+1;}
    if(y==0) {h=n-1;} else {h=y-1;}
    if(y==n-1) {d=0;} else {d=y+1;}
    if (pole[l][y]) {sum++;}
    if (pole[x][h]) {sum++;}
    if (pole[p][y]) {sum++;}
    if (pole[x][d]) {sum++;}
    if (!pole[x][y]) {sum=-sum+4;}
    if (P[sum]>(rand())/(double)RAND_MAX){
        pole[x][y]=!pole[x][y];
        if (pole[x][y]) {magnetizacia+=2;}
        else {magnetizacia-=2;}
    }
}
