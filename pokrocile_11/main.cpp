#include <iostream>
#include <cmath>
#include <bitset>
#include <string>
const int n=10;
const int N=1024;

using namespace std;
int InverseBinary(int);
int main()
{

    double x[N];
    for (int i=0;i<N;i++) {
        //x[InverseBinary(i)]=sin(2*M_PI*(double)i/N);
        x[InverseBinary(i)]=i;
        //cout << i << "  "<< InverseBinary(i)<<endl;
    }
    for (int i=0;i<N;i++) {cout << i << "  "<< x[i]<<endl;}
    return 0;
}
int InverseBinary(int i) {

    bitset<n> cislo (i);
    string temp;
    string temp2="";
    temp = cislo.to_string();
    for (string::reverse_iterator rit=temp.rbegin(); rit!=temp.rend(); ++rit) {
        temp2 += *rit;
    }
    cislo=bitset<n> (temp2);
    return cislo.to_ulong();
}
