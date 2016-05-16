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

using namespace std;
double fx, fy;
void f ();
void f () {
    fx = (((double)rand ()/ (RAND_MAX))*2-1);
    fy = (((double)rand ()/ (RAND_MAX))*2-1);
}

int main()
{
    ofstream fout("data.dat");
    //Brownov Pohyb
    double x = 0;
    double y = 0;
    double dt = 0.0001;
    double gamma = 0.1;
    double vx = 0;
    double vy = 0;
    //  (((double)rand ()/ (RAND_MAX))*2-1)
    for (int i=0; i<10E7; i++) {
        if ((i%100)==0) {f();
            vx = vx + (-gamma*vx+fx)*dt;
            x = x + vx*dt;
            vy = vy + (-gamma*vy+fy)*dt;
            y = y + vy*dt;
            fout << x << '\t' << y << endl;
        }
        vx = vx + (-gamma*vx+fx)*dt;
        x = x + vx*dt;
        vy = vy + (-gamma*vy+fy)*dt;
        y = y + vy*dt;
        // jednorozmerny pripad
        //fout << i << '\t' << x << endl;
        //dvojrozmerny pripad

    }
    fout.close();
    system("xmgrace data.dat");
    return 0;
}
