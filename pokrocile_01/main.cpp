/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA  -
    Ulohy:

    Poznamky k teorii:

************************************************************/
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;
void zlatyrez(int);
void komplikovana1(int);  //v prezentacii menej trivialna iteracna 1
double g[101];
void zlatyrez(int n) {
	g[n + 1] = g[n - 1] - g[n];
	if (n < 100) { zlatyez(n + 1); }
}

void komplikovana1(int n) {
	g[n - 1] = (4 + 0.1*cos(M_PI*n))*g[n] - g[n + 1];
	if (n > 0) { komplikovana1(n - 1); }
}

int main()
{
	int uloha;
	cout << "Choose from programs:" << endl << "1==Zlaty rez" << endl << "2==x_n+1-[4+0.1Cos(PI*n)X_n+X_n-z=0]" << endl;
	cin >> uloha;
	double x1 = 0.61803398;
	double x0 = 0.61803398;
	string DataName;
	switch (uloha) {
	case 1:
		//cout << "vlozte hodnotu x1" << endl;
		//cin >> x1;
		DataName = ("Data1.dat");
		g[0] = 1;
		g[1] = x1;
		zlatyrez(1);
	break;
	case 2:
		g[60] = 0;
		g[59] = 1;
		DataName = ("data2.dat");
		komplikovana1(59);
		for (int i = 60;i >= 0;i--) {
			g[i] = g[i] * x0 / g[0];
		}
		break;
	}
	ofstream fout("data.dat");	//zapis do suboru
	for (int i = 0;i < 100;i++) {
		cout << g[i] << endl;
		fout << i << "\t" << g[i] << endl;
	}
	system("xmgrace data.dat");
	return 0;
}
