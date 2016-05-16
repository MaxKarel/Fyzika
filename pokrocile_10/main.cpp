/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA  -
    Ulohy:

    Poznamky k teorii:

************************************************************/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <climits>
#include <cstdlib>
//g++ main.cc -L $HOME/misc/lib/lapack-3.3.0 -llapack -lblas -lgfortran -o main

using namespace std;
const int N = 8; // velkost pola
void GNL (double *); // generate line vertical or horizontal
void WMAT (double (&pomoc)[N][N]); //write matrix
int main()
{
    srand(time(NULL));
    double V[N-1]; //verikalne spojenia na niektorom stlpci
    double psi [N-1]; //spojenia so zaciatkom
    double H[N]; //horizontalne spojenia
    double P0[N][N]; //spojenia medzi bodmi na zvyslej ciare
    double P[N][N];
    for (int i=0;i<N-1;i++) {psi[i] = 1.0;} //inicializacia kazdy zaciatocny bod je spojeny na zaciatok
    double temp;
    for (int i = 0 ; i < N; i++) {
        for (int j = 0;j < N; j++) {
            temp=1;
            for (int k=i;k<j;k++) {
                temp=temp*V[k];
            }
            P[i][j]=temp;
        }
    }
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            if (i>j) {
                P[i][j]=P[j][i];
            }
        }
    }
    WMAT(P);
    cout <<endl;
    for (int i=0;i<N;i++) {
        GNL(H);

    }

}
void WMAT(double (&pomoc)[N][N]) {
    for (int i = 0;i<N;i++){
        for (int j = 0;j<N;j++) {

            cout << pomoc[i][j] << " ";
        }
        cout << endl;
    }
}
void GNL(double*p) {      //generate new line
    for (int i = 0;i < N - 1;i++) {
        if (rand()/ (double)RAND_MAX > 0.5) {p[i]=0;} else {p[i]=1;}
    }
}
