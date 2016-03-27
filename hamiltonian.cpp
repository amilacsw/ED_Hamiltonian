#include <iostream>
#include <string>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include<ctime>
#include<cstdio>
#include<typeinfo>


#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
double Hamilt[1000][1000];
double pos[999];
double data[25];


double c=20.67;//(hbar*c)^2/(2mc^2)
double V0=-51.0;
double R=3.2;
double a0=0.67;
double L=0;
double delta=0.01;
int N=1000;

int main ()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                           Constructing the Hamiltonian                                                 /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (int i=0;i<N;i++)
    for (int j=0;j<N;j++)
    {

      if (j==i){Hamilt[i][j]=(2*c)/(delta*delta) +(c*L*(L + 1))/(((i - 1/2)*delta)*((i - 1/2)*delta)) + V0/(
 1 + exp(((i - 1/2)*delta - R)/a0));}
        else if (j==i+1){Hamilt[i][j]=-c/(delta*delta);}
        else if (j==i-1){Hamilt[i][j]=-c/(delta*delta);}
        else {Hamilt[i][j]=0;}
    }
    Hamilt[0][0]=(2*c)/(delta*delta) -pow(-1,L+1)*c/delta + (c*L*(L + 1))/((delta/2)*(delta/2)) + V0/(
 1 + exp((delta/2 - R)/a0));

    Hamilt[0][1]=-c/(delta*delta);

    Hamilt[N-1][N-2]=-c/(delta*delta);

    Hamilt[N-1][N-1]=(2*c)/(delta*delta) + c*L*(L+1)/(((N-1 - 1/2)*delta)*((N-1 - 1/2)*delta)) +V0/(
1 + exp(((N-1 - 1/2)*delta - R)/a0));


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                           Printing the Hamiltonian to a file                                           /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ofstream myfile;
  myfile.open ("hamiltonian.txt");

for (int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			 myfile << Hamilt[i][j]<<'\n';
		}
	}
 
  myfile.close();

  return 0;
 }


