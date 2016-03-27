#
#    makefile
#


eigen: eigen.o
	g++ -L/usr/local/lib eigen.o -lgsl -lgslcblas -lm -o eigen

eigen.o: eigen.cpp hamiltonian
	g++ -Wall -I/usr/local/include -c eigen.cpp

#hamiltonian: hamiltonian.o hamiltonian.cpp
#	g++ hamiltonian.cpp -o hamiltonian 





#cleaning things
clean:
	rm *.o
cleanAll:
	rm eigen *.o
