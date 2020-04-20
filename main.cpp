#include <iostream>
#include <fstream>
#include "Simulation.h"
 using namespace std;

 int main(int argc, char **argv) {

  string fileName;

	//if user forgot to provide a file

	if(argc < 2){
		cout<<"You didnt provide a file. Re-type file name."<<endl;
		cin>> fileName;
	}
	else
		fileName = argv[1];


  Simulation sim;
  sim.runSimulation(fileName);



   return 0;
 }
