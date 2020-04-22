#include "Queue.h"
#include "Student.h"
#include "Window.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

//code to sort the array so its easier to compare to find the median
int compare(const void * a, const void * b) {
 return ( *(int*)a - *(int*)b );
}

class Simulation{
  public:

    Simulation();
    ~Simulation();

    void runSimulation(string fileName);


    //calculate statistics

    void printStatistics();

    double meanWaitTime();
    double medianWaiTime();
    double meanWindowIdleTime();
    int longestWaitTime();
    int numberOfWindowIdleFive();
    int longestIdleTime();
    int studentsWaitingTen();

    int sumIdleTimes;
    int numWindows;
    int totalStudents;
    double sumWaitTimes;
    int currentTime;
    int *sumIdleTimesArray;
    int *waitTimeArray;
    Window* *windows;
    Window *w;



};

Simulation::Simulation(){

}
Simulation::~Simulation(){
  delete sumIdleTimesArray;
  delete waitTimeArray;
}


void Simulation::runSimulation(string fName){
  ifstream file;
  string fileName = fName;

  file.open(fileName);

  //test to make sure file exists and it has opened
  while(!file.is_open()){
    cout<< "Error opening file. Re-type file name: " << endl;
    cin>>fileName;
    file.open(fileName);

  }

  //create a student Queue
  GenQueue<Student*> *studentQueue = new GenQueue<Student*>();


  string line; // line of the file

  getline(file,line); // get first line  of file and assign that to the number of windows
  numWindows = stoi(line); // convert the string from file to int



  //create an array of windows

  windows = new Window*[numWindows]; // create an array of windows to represent the windows at the registrar

  for(int i = 0; i< numWindows; ++i){
    w = new Window();
    windows[i] = w;

  }



  totalStudents = 0;


// loop to read data and assign the data to the correct variables
  while(getline(file, line)){

      //second line of file arrival time
        int arriveAt = stoi(line);//covert to int

        getline(file,line);
        int studentsArrived = stoi(line); //number of students that arrived at that time

        totalStudents += studentsArrived; //add to the total number of students


        for(int i = 0; i < studentsArrived; ++i){

            getline(file,line);
            int timeNeeded = stoi(line);

            Student *s = new Student(arriveAt, timeNeeded); // create a student object for every student that has arrived

            //insert student on Queue
            studentQueue->insert(s);

        }

  }

  //list of students that have been helped to keep track for later calculations


    GenQueue<Student*> *studentsHelped = new GenQueue<Student*>();

    currentTime = 0;

    sumIdleTimes = 0;
    bool windowsFull;
    int totalWindowsFull;

    sumWaitTimes = 0.0;

    waitTimeArray = new int[totalStudents];
    sumIdleTimesArray = new int[numWindows];

    //run simulation until both line are empty and all windows are empty

    while(!(studentQueue->isEmpty()) || (totalWindowsFull != 0)) {
  		totalWindowsFull = 0;
  		windowsFull = false;

  		for(int i = 0; i < numWindows; ++i) {
  			if(windows[i]->timeAtWindow != 0) {

          //for each clock tick, decrement time remaining at window if the windows are full
          windows[i]->timeAtWindow--;


          if(windows[i]->timeAtWindow != 0)
  					totalWindowsFull++; // if the window is still full, increment

  			}
  		}

  		if(totalWindowsFull == numWindows) {
  			windowsFull = true;
  		}

    // check to see if there are still student in line
  		if(!(studentQueue->isEmpty())) {

        //while students are stil in line and the current time of arrival is the arrival time of the next student
        //and there is a window available, send student to window

      			while(!(studentQueue->isEmpty()) && (currentTime >= studentQueue->peek()->arrivalTime) && !windowsFull) {

      				for(int i = 0; i < numWindows; ++i) {
      					if(windows[i]->timeAtWindow == 0) {

                  //keep track when students are at the window

      						windows[i]-> timeAtWindow = studentQueue->peek()->timeNeeded;
      						studentQueue->peek()->timeLeave = currentTime;

      						//keep track of what window student went in
      						studentQueue->peek()->windowNumber = i;

      						totalWindowsFull++;  // make the window full once the student is send to that window


                  break;
      					}
                else{
                  sumWaitTimes++;

                }
      				}

      			//remove student from line since it was already helped, add that to the list of student helped.

              //add to wait time array the wait time student that is getting removed from line
              waitTimeArray[totalStudents-studentQueue->getSize()-1] = studentQueue->peek()->waitTime;

      				studentsHelped->insert(studentQueue->remove());


              //increment wait time for next student
              studentQueue->peek()->waitTime = sumWaitTimes + 1;

              sumWaitTimes++; // increment the total wait times

      				  //check if windows are full in case the nest sutdnet in line has same arrival time
      				if(totalWindowsFull == numWindows){
                windowsFull = true;

              }

      		}
  		}

  		//if any of the windows are empty, increment the idle time counter
  		for(int i = 0; i < numWindows; ++i) {
  			if(windows[i]->timeAtWindow == 0){
          	sumIdleTimes++;
            windows[i]->idleTime++;
        }

  		}

  		currentTime++;

  	}//END of simulation

    //populate idle time array once simulation is over
    for(int i  = 0; i < numWindows; ++i){
      sumIdleTimesArray[i] = windows[i]->idleTime;
    }

    //CALL PRINT STATS
      printStatistics();

      file.close();

}


void Simulation::printStatistics(){

  cout<<"\nThe following statistics were calculated based on the simulation: \n"<<endl;

  cout<< "1. The mean student wait time: ";
  cout<< meanWaitTime()<< " minute(s)"<< endl;

  cout<< "2. The median student wait time: ";
  cout<< medianWaiTime()<< " minute(s)"<<endl;

  cout << "3. The longest student wait time: ";
  cout << longestWaitTime()<< " minute(s)"<<endl;

  cout<<  "4. The number of students waiting over 10 minutes: ";
  cout << studentsWaitingTen()<< " minute(s)" << endl;

  cout<< "5. The mean window idle time: ";
  cout << meanWindowIdleTime()<< " minute(s)"<< endl;

  cout<< "6. The longest window idle time: ";
  cout<< longestIdleTime()<< " minute(s)"<< endl;

  cout << "7. Number of windows idle for over 5 minutes: ";
  cout << numberOfWindowIdleFive() << " minute(s)"<<  endl;


}
double Simulation:: meanWaitTime(){

  // calculate mean student wait time 1.
  double meanStudentWaitTime = (double) sumWaitTimes/totalStudents;
  return meanStudentWaitTime;
}

double Simulation::medianWaiTime(){
  //calculate median student wait time 2.

  //sort array of waittimes
  qsort(waitTimeArray, totalStudents, sizeof(int), compare);

  //find median

  int middleIndex = (totalStudents/2);
  int secondIndex = 0;

  //if array has even number of elemens

  if(middleIndex%2 == 0){
    secondIndex = middleIndex-1;
  }
  double medianWaiTime;

  if(secondIndex == 0){
    medianWaiTime = waitTimeArray[middleIndex];
  }
  else
    medianWaiTime = (double)waitTimeArray[middleIndex]+ waitTimeArray[secondIndex]/2;


  return medianWaiTime;
}

int Simulation::longestWaitTime(){
  // calculate longest student  wait time 3.
  int longestWait = 0;

  for(int i = 0; i < totalStudents; ++i){
    if(waitTimeArray[i]>longestWait)
      longestWait = waitTimeArray[i];
  }

  return longestWait;
}

int Simulation:: studentsWaitingTen(){
  //calculate number of student waiting over 10 minutes 4.
  int studentWaitingOverTen = 0;

  for(int i = 0; i < totalStudents; ++i){
    if(waitTimeArray[i] > 10)
      studentWaitingOverTen++;
  }
  return studentWaitingOverTen;
}

double Simulation::meanWindowIdleTime(){
  //calculate mean winow idle time 5.

   double meanWindowIdleTime = (double)sumIdleTimes/numWindows;

   return meanWindowIdleTime;
}


int Simulation::longestIdleTime(){
  //calculate longest idle time 6.

  int longestIdleTime = 0;

  for(int i = 0; i < numWindows; ++i){

    if(sumIdleTimesArray[i] > longestIdleTime)
      longestIdleTime = sumIdleTimesArray[i];

  }
  return longestIdleTime;
}

int Simulation::numberOfWindowIdleFive(){

  //calculate number of windows idle for over 5 minutes 7.
  int numWindowsIdleFive = 0;

  for(int i = 0; i < numWindows; ++i){
    if(sumIdleTimesArray[i]> 5){
      numWindowsIdleFive++;
    }
  }

  return numWindowsIdleFive;
}
