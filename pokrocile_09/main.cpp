/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA  -
    Ulohy:

    Poznamky k teorii:

************************************************************/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;
int main()
{
    srand(time(NULL));
    ofstream fout("data.dat");
    double T=2.0;
    double P [5];
    int sum;
    int n=32;
    bool pole [n][n];
    for  (int i=1;i<6;i++){         //Vypocet pola pravdepodobnosti
        P[i-1]=1/(1+exp((4*i-12)/(T)));
    }
    for (int i= 0;i<n;i++){         //Inicializacia pola
        for (int j=0;j<n;j++){
            if (rand()%2==0) {pole[i][j]=0;}
            else {pole[i][j]=1;}
        }
    }
    int x,y;
    int magnetizacia=0;
    for (int i=0;i<n;i++) {     //vypocet povodnej magnetizacie
        for (int j=0;j<n;j++) {
            if (pole[i][j]) {magnetizacia++;}
            else {magnetizacia--;}
        }
    }
    cout << "pociatocna manetizacia "<< magnetizacia<< endl << endl;
    int l,p,d,h;
    for (int i=0;i<160000*1000;i++){
        x=rand()%(n);
        y=rand()%(n);
        sum=0;
        if(x==0) {l=n-1;} else {l=x-1;}
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
            if (abs(magnetizacia)==n*n-n) {cout <<"pocet cyklov=" << i << endl; break;}
        }

    }
    for (int i= 0;i<n;i++){         //Vypis pola
        for (int j=0;j<n;j++){
            if (pole[i][j]) {cout<<" +";}
                else {cout << "  ";}
        }
    cout << endl;
    }
    cout << magnetizacia;
    return 0;
}
