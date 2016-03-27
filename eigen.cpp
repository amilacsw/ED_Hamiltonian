
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
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
#include<math.h>
//#include<chplot>
#include <iterator>
#include <algorithm>
#include <vector>



using namespace std;

int N=1000;
//double pos[N];
double delta=0.01;

int
main (void)
{
    double data[N*N];// A matrix to store the Hamiltonian

	
	ifstream ifstr;
        ifstr.open("hamiltonian.txt"); //Importing the Hamiltonian matrix produced by hamiltonian.cpp

	for (int i=0; i<N*N; i++)
	{
         ifstr >> data[i];
        }

	ifstr.close();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                           Diagonilization using the GSL library                                        /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  gsl_matrix_view m 
    = gsl_matrix_view_array (data, N, N);

  gsl_vector *eval = gsl_vector_alloc (N);
  gsl_matrix *evec = gsl_matrix_alloc (N, N);

  gsl_eigen_symmv_workspace * w = 
    gsl_eigen_symmv_alloc (N);
  
  gsl_eigen_symmv (&m.matrix, eval, evec, w);

  gsl_eigen_symmv_free (w);

  gsl_eigen_symmv_sort (eval, evec, 
                        GSL_EIGEN_SORT_VAL_ASC);
  
  {
    ofstream myfile;
    myfile.open ("eigensys.txt"); // writing the eigen system to a file
    int i;
    

    for (i = 0; i < N; i++)
      {
        double eval_i 
           = gsl_vector_get (eval, i);
        gsl_vector_view evec_i 
           = gsl_matrix_column (evec, i);
	
	myfile<<eval_i<<'\n';
      }
  myfile.close();

cout<<"Negative eigen values:"<<endl;

	for (i = 0; i < N; i++)
	{
	double eval_i 
           = gsl_vector_get (eval, i);

		if (eval_i<0)
		{
	    	    printf ("eigenvalue = %g\n", eval_i);
	    	    //printf ("eigenvector = \n");
	    // gsl_vector_fprintf (stdout, 
            //                &evec_i.vector, "%g");
	    	}
			
	}

//Writing the first eigen vector to a file
	
FILE* vecfile;
//    vecfile.open ("eigenvector0.txt");
vecfile=fopen("eigenvector0.txt","w");
gsl_vector_view evec0 
           = gsl_matrix_column (evec, 0);//Choosing the zeroth column(1st eigen vector) from evec matrix
gsl_vector_fprintf (vecfile, 
                           &evec0.vector, "%g");
fclose(vecfile);

//Writing the second eigen vector to a file
	
FILE* vecfile1;
//    vecfile1.open ("eigenvector1.txt");
vecfile1=fopen("eigenvector1.txt","w");
gsl_vector_view evec1 
           = gsl_matrix_column (evec, 1);//Choosing the zeroth column(1st eigen vector) from evec matrix
gsl_vector_fprintf (vecfile1, 
                           &evec1.vector, "%g");
fclose(vecfile1);


//vecfile.close();
 
	/*cout<<"Forst eigen vector v1[0]"<<v1[0]<<endl;
	cout<<"Forst eigen vector v1[1]"<<v1[1]<<endl;
	cout<<"Forst eigen vector v1[100]"<<v1[100]<<endl;
	cout<<"Forst eigen vector v1[999]"<<v1[999]<<endl;*/


  }



/* // Checking whether data[] array is constructed correctly

cout<<"data[0]= "<<data[0]<<endl;
cout<<"data[1]= "<<data[1]<<endl;
cout<<"data[2]= "<<data[2]<<endl;
cout<<"data[3]= "<<data[3]<<endl;
cout<<"data[1001]= "<<data[1001]<<endl;
cout<<"data[1000000]= "<<data[1000000]<<endl;*/

  gsl_vector_free (eval);
  gsl_matrix_free (evec);

//Plotting the Potential and Eigenvectors
  {
        double pos[N];
	double ev0[N];
	
	for (int i=0; i<N; i++)
	{
	pos[i]= (i+1/2)*delta;
	}
//writing the position vector to a file for plotting
	ofstream posstrm;
	posstrm.open("position.txt");

	for (int i=0; i<N; i++)
	{
         posstrm<< pos[i]<<'\n';
	 // cout<<data[i]<<endl;
        }

	posstrm.close();

//writing the eigenvector to a file for plotting

	ifstream ifstev0;
	ifstev0.open("eigenvector0.txt");

	for (int i=0; i<N; i++)
	{
         ifstr >> ev0[i];
	 // cout<<data[i]<<endl;
        }

	ifstev0.close();

	//plotxy(pos,ev0);
	//double v1[1000];
	//gsl_vector *evec0 = gsl_vector_alloc (N);
	//evec0=gsl_matrix_column (evec, 0);
	//gsl_vector_view evec0 
         //  = gsl_matrix_column (evec, 0);

	//for (int j=0; j<N; j++)
	//{
	//v1[j]=gsl_vector_get (evec0, j);//gsl_vector_fscanf(&evec_1.vector,v1);
	//}
  }
  return 0;
}
//gcc -Wall -I/usr/local/include -c eigex.cpp
//gcc -L/usr/local/lib eigex.o -lgsl -lgslcblas -lm -o eigex
