/* **********************************************************
    Pokrocile cvika z programovania - MATFYZ
    CVIKA 5 - Poissonovo a Gaussovo rozdelenie
    Ulohy:
        0. zopakujte predchádzajúci výpočet.
        1. zostrojte súbor náhodných čísiel homogénne rozdelených v intervale (a, b)
        2. zostrojte súbor náhodných čísiel {x} s binominálnym rozdelením
        3. napíšte program pre zoradenie N čísiel podľa veľkosti
        4. napíšte program pre konštrukciu pravdepodobnostného rozdeleniap(l)
        5. preverte tvar p(l)
        6. nájdite pravdepodobnostné rozdelenie pre čísla s = sum (x_i) od o do N
        7. presvedčte sa, že odchýlka
    Poznamky k teorii:
        Pravdepodobnostne rozdelenie dlzok:
            Najprv vygenerujeme N cisel od 0 po N. po ich usporiadani vypocitame vzdialenosti medzi nimi.
            Kedze ide o nahodne generovanie ziadna hodnota nieje preferovana a preto by mali byt vzdialenosti medzi cislami rovnako rozmiestnene.
            Predpokladame ze ziadne l nebude vacsie ako 10, preto pre vacsie N mouze program padnut (treba upravovat hodnotu b). to je aj dovodom pre nepresnosti pri vyssich hodnotach M.
            Vzdialenosti rozriedime do intervalov a urcim ake su jednotlive intervali pocetne. najviac by malo byt kratkych.
        Pravdepodobnostne rozdelenie suctu:

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
void max_sort(double *,int); //my max_sort, slow as hell
int One(); //pravdepodobnostne rozdelenie dlzok alebo intervali medzi nahodnimy casovymi udalostami
int Two(); //Pravdepodobnostne rozdelenie suctu nahodnych cisel
void max_sort(double *p,int N) {
    int index;
    double small, temp;
    for (int i=0;i<N-2;i++) {
        small = p[i];
        index = i;
        for (int j=i;j<N-2;j++){
            if (small > p[j]) {
                small = p[j];
                index = j;
            }
        }
        temp=p[index];
        p[index]=p[i];
        p[i]=temp;
    }
}
int One()
{
    signed int N = 1E7;  //pocet cisel
    int M = 100;     //rozdelenie intervalu
    double a = 0;   //horna hranica intervalu
    double b = 10;  //dolna hranica intervalu
    double p [M];   //pole pravdepodobnosti
    for (int i=0;i<M;i++) {p[i]=0;} //nulovanie pola
    srand (time(NULL));
    ofstream fout ("data.dat");
    double x [N-1];
    double l [N-1];
    for (signed int i=0; i<N;i++) {
        x[i]=(double)(rand())/RAND_MAX*N;
    }
    sort(x,x+N);
    //max_sort(x,N);
    x[0]=0;
    x[N-1]=N;
    for (signed int i=0;i<N-1;i++) {
        l[i]=x[i]-x[i-1];
    }
    int index;
    for (signed int i=0;i<N-1;i++) {
        try {
            index  = int((l[i]-a)/(b-a)*(double)M);
            throw i;
            }
            catch (int n) {//cout << index;
                            //cout <<" "<<n;
                            //cout << " "<<l[i]<< endl;
                          }
        if (index<M) {p[index]++;}
    }
    double norm = 1/(N*(b-a)/M);
    //for (int i=0;i<N;i++){fout << (double)i/N << "\t" << x[i] << endl;}
    for (int i=0; i<M;i++) {
        fout << i << "\t" << norm*p[i] << endl;
        //fout << log(i) << "\t" << log(norm*p[i]) << endl;
    }
    fout.close();
    system("xmgrace data.dat");
    return 0;
}
int Two()
{
    ofstream fout ("data.dat");
    signed int N = 1E4; // kedze <x>=1 hodnota s by mala byt = N
    int n = 10000; //pocet vypocitanych sum
    double MAX_RANGE=2.0; // maximum pokial sa moze pohybovat prvok scitancov v sum[i]
    double sum[n]; //pole sum
    int p_range = 800;
    double p[p_range]; //pole pravdepodnosti
    for (int i=0;i<p_range;i++) {p[i]=0;}
    for (int i=0;i<n;i++) {sum[i]=0;} //nulovanie pola
    for (signed int i=0; i<n;i++) {
        for (int j=0;j<N;j++) {
            sum[i]+=(double)(rand())/RAND_MAX*MAX_RANGE;
        }
    }
    int index;
    for (int i=0;i<n;i++) {
        index = round((sum[i]-N+0.02*N)/8); // cislo 200 by sa dalo vyadrit cez premenne
        cout << setprecision(10) << index << "   " << sum [i]<<  endl;
        p[index]++;
    }
    index=0;
    for (int i=0;i<p_range;i++) {index+=p[i];}
    for (int i=0;i<p_range;i++) {
        fout << 8*i-0.02*N+N << "\t" << p[i]/(double)index << endl;
    }
    cout << endl<< index;
    fout.close();
    system("xmgrace data.dat");
    return 0;
}
int main()
{
    cout << "Hello World! Please pick:" << endl << "1: Pravdepodobnosnte rozdelenie dlzok alebo casovych udalosti" << endl << "2: Pravdepodobnostne rozdelenie suctu" << endl << "3: help" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1: One();
            break;
    case 2: Two();
            break;
    case 3: cout << "Help not implemented yet! Please wait for patch!" << endl;
            break;
    default: cout << "Not a valid input" << endl;
            break;
    }

    return 0;
}
