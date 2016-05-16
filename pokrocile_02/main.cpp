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
#include <complex>
using namespace std;

double c = 299000000; //rychlostsvetla

double jednaVrstva(double);
double jednaVrstva2(double);  // pre meniace sa n
int main()
{
	ofstream fout("data.dat");	//zapis do suboru
	for (int f = 1;f < 1000; f++) {
		fout << (float)f/100 << "\t" << jednaVrstva2((double)f / 100 * c) << endl;
	}
	/*double x;
	double n2;
	for (int i=0;i<=100;i++){
        x=((double)i/100)-0.5;
        cout << x << endl;
        n2=1+1*(1-abs(x)/1);
        fout <<x<< "\t"<< n2<<endl;
	}*/
	system("xmgrace data.dat");
	return 0;
}
double jednaVrstva2 (double frek) {  // pre meniace sa n
    double n1 = 1; // index lomu mimo vrstvy
	double n2; //index lomu vo vrstve
	double L = 1;  //dlzka vrstvy
	double lambda = c / frek;
	double h = 0.001; //dlzka kroku
	double k = 2 * M_PI / lambda;
	double zatvorka1 = 2 - (2 * M_PI)*(2 * M_PI)*h *h / lambda / lambda;  //clen mimo dielektrika
	double zatvorka2; // clen v dieelektriku
	int N = L / h;
	N = N + 5;  // zacinam a koncim trochu vedla od dielektrickej vrstvy
	const complex <double> im(0, 1);  //sqrt(-1)
	complex <double> E[10000];
	E[1] =  1 ;	//inicilizacia
	E[0] = exp(im*k*h);
	for (int i = 1;i <= N;i++) {	//iteracia
		if ((i >= 2) && (i <= N - 1)) {
			//E3 = E2 - zatvorka2*E1;
			n2=1+1*sqrt(1-((i-(N/2))*h/(L/2))*((i-(N/2))*h/(L/2)));
			//n2=1+1*(1-abs((i-(N/2))*h)/(L/2));
			zatvorka2 = 2 - (2 * M_PI)*(2 * M_PI)*h *h *n2*n2 / (lambda * lambda);
			E[i + 1] = -E[i - 1] + zatvorka2*E[i];
		}
		else {
			E[i + 1] = -E[i - 1] + zatvorka1*E[i];
		}

	}
	complex <double> citatel = E[N] - E[N - 1] * exp(im*k*h);	//vypcet T
	complex <double> menovatel = complex <double>( 2, 0 ) *im*sin(k*h);
	complex <double> T = pow(abs(citatel / menovatel), -2);
	complex <double> R = (E[N-1]*exp(-im*k*h)-E[N])/citatel;
	R=pow(abs(R),2);
	cout << "frek="<< frek << " T="<< setprecision(10) << T.real() << "  T+R=" << R.real()+T.real() << endl;
	return abs(T);
}
double jednaVrstva(double frek) {
	double n1 = 1; // index lomu mimo vrstvy
	double n2 = 2; //index lomu vo vrstve
	double L = 1;  //dlzka vrstvy
	double lambda = c / frek;
	double h = 0.001; //dlzka kroku
	double k = 2 * M_PI / lambda;
	double zatvorka1 = 2 - (2 * M_PI)*(2 * M_PI)*h *h / lambda / lambda;
	double zatvorka2 = 2 - (2 * M_PI)*(2 * M_PI)*h *h *n2*n2 / (lambda * lambda);
	int N = L / h;
	N = N + 5;  // zacinam a koncim trochu vedla od dielektrickej vrstvy
	const complex <double> im(0, 1);  //sqrt(-1)
	complex <double> E[10000];
	E[1] =  1 ;	//inicilizacia
	E[0] = exp(im*k*h);
	for (int i = 1;i <= N;i++) {	//iteracia
		if ((i >= 2) && (i <= N - 1)) {
			//E3 = E2 - zatvorka2*E1;
			E[i + 1] = -E[i - 1] + zatvorka2*E[i];
		}
		else {
			E[i + 1] = -E[i - 1] + zatvorka1*E[i];
		}

	}
	complex <double> citatel = E[N] - E[N - 1] * exp(im*k*h);	//vypcet T
	complex <double> menovatel = complex <double>( 2, 0 ) *im*sin(k*h);
	complex <double> T = pow(abs(citatel / menovatel), -2);
	complex <double> R = (E[N-1]*exp(-im*k*h)-E[N])/citatel;
	R=pow(abs(R),2);
	double DR = R.real();
    double DT = T.real();
	double TR = DT+DR;
	cout << "frek="<< frek << " T="<< setprecision(10) << T.real() << "  T+R=" << TR <<endl;
	return abs(T);
	//return 0;
}
