/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA 8 - Elektrostatika v 1D a 2D
    Ulohy:
        pomocou gaus jordana alebo inverzie matic vyrieste ulohu rozlozenia naboja na tenkom vodici/tenkej vodivej platni
    Poznamky k teorii:
        matica matrix ma riadky dlhe N+1 a ma N riadkov
        pre stabilny stav musi platit ze intenzita E je v kazdom bode ==0;
        Dostavame teda N-1 linearnych rovnic rovnych nule kde N je velke cislo, na ktore sme si vodic rozdelili
        Posledna rovnica je sucet vsetkych dq na malych usekoch musi dat celkovy naboj Q.

        V pripade nekonecne dlheho pasika dlzky L uvazujeme, ze vysledna intenzita E v y smere je vzdy nulova a preto nam staci pocitat hustotu
        naboja v x smere. jedine co sa zmeni je mocnina v menovateli 3->2
************************************************************/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

void print_matrix(vector< vector<double> > A);
vector<double> gauss(vector< vector<double> > A);

static const int N=200;   //rozdelenie na intervalu

int main() {
	ofstream fout("data.dat");
	double L=1.0;   //dlzka kovoveho vlakna
	double d=L/(2*N);   //dlzka jedneho intervalu, ratame iba na polovicnej dlzke preto 2*
	double Q=1.0000;    //naboj na celom vodici
	vector<double> rho(N);  //vysledna hustota
	vector<double> line(N + 1);     //jeden riadok matice
	vector< vector<double> > matrix(N, line);
	// vytvorit maticu A a dat do fomry sustavy linearnych rovnic
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N+1; j++) {
			matrix[i-1][j-1] = (i-j+0.5)/abs(pow((i-j+0.5),3))+(i+j-0.5)/abs(pow((i+j-0.5),3));
		}
	}
    for (int i=0;i<N+1;i++) {matrix[N-1][i]=1;} //posledny riadok matice vyadruje to ze sucet
    matrix[N-1][N]=Q/(2*d);     //dalo by sa to preskalovat na 1 ale takto mi to pride nazornejsie
	print_matrix(matrix);

	rho = gauss(matrix); // calc solution
	// vypis riesnie
	cout << "Riesenie:" << endl;
	double sum=0;
	for (int i = 0; i < N; i++) {
		fout<<i << '\t' << rho[i]<< endl;
		sum+=2*rho[i]*d;    //treba priratat nabok aj za zrkadlovu polovicu
	}
	cout << "Skuska spravnosti (predpokladmae ze sucet vypocitanych hustot da povodny naboj Q:" << '\n' << "Q=" << sum<< endl;
	system("xmgrace data.dat");
	return 0;
}

void print_matrix(vector< vector<double> > A) {
	int n = A.size();

	for (int i = 0; i<n; i++) {
		for (int j = 0; j < n + 1; j++) {
			cout << A[i][j] << "  ";
			if (j == n - 1) {
				cout << "| ";
			}
		}
		cout << "\n";
	}
	cout << endl;
}
vector<double> gauss(vector< vector<double> > A) {
	int n = A.size();
    // tento forcyklus robi upravu matice na jednotkovu
	for (int i = 0; i<n; i++) {
		// Search for maximum in this column
		double maxEl = abs(A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k<n; k++) {
			if (abs(A[k][i]) > maxEl) {
				maxEl = abs(A[k][i]);
				maxRow = k;
			}
		}
		// Swap maximum row with current row (column by column)
		for (int k = i; k<n + 1; k++) {
			double tmp = A[maxRow][k];
			A[maxRow][k] = A[i][k];
			A[i][k] = tmp;
		}
		// Make all rows below this one 0 in current column
		for (int k = i + 1; k<n; k++) {
			double c = -A[k][i] / A[i][i];
			for (int j = i; j<n + 1; j++) {
				if (i == j) {
					A[k][j] = 0;
				}
				else {
					A[k][j] += c * A[i][j];
				}
			}
		}
	}
	//print_matrix(A);
    cout << endl;
	// Solve equation Ax=b for an upper triangular matrix A
	vector<double> x(n);
	for (int i = n - 1; i >= 0; i--) {
		x[i] = A[i][n] / A[i][i];
		for (int k = i - 1; k >= 0; k--) {
			A[k][n] -= A[k][i] * x[i];
		}
	}
	return x;
}
