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


    int idleTimes;
    int numWindows;
    int totalStudents;
    int *idleTimesArray;
    int *waitTimeArray;



};

Simulation::Simulation(){

}
Simulation::~Simulation(){
  delete idleTimesArray;
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

  getline(file,line); // get first line

  numWindows = stoi(line); // convert the string from file to int

  //create an array of windows

  int *windows = new int[numWindows]; // create an array for windows to represent the windows at the registrar

  for(int i = 0; i< numWindows; ++i){

    windows[i] = 0; // assign them to 0 in order to make it easier to make calculations later on
    //0 = empty
  }

  totalStudents = 0;

  while(getline(file, line)){
    int arriveAt = stoi(line);

    getline(file,line);

    int studentsArrived = stoi(line);

    totalStudents += studentsArrived;

    for(int i = 0; i < studentsArrived; ++i){
      getline(file,line);
      int timeNeeded = stoi(line);

      Student *s = new Student(arriveAt, timeNeeded); // create a student object for every student that has arrived

      //insert student on Queue

      studentQueue->insert(s);
    }
  }

  //list of students that have been helped to keep track for later calculations

    DLinkedList<Student*>  *studentsHelped = new DLinkedList<Student*>();

    int currentTime = 0;

    idleTimes = 0;
    bool windowsFull;
    int totalWindowsFull;

    //num simulation until both line are empty and all windows are empty

    while(!(studentQueue->isEmpty())|| totalWindowsFull !=0){
      totalWindowsFull = 0;
      windowsFull = false;

      for (int i = 0; i < numWindows; ++i){
        if(windows[i] != 0 ){
          windows[i] -= 1; //for each clock tick, decrement time remaining at window if the windows are full

          if(windows[i] !=0)
            totalWindowsFull++; // if the window is still full, increment

        }
      }

      if(totalWindowsFull == numWindows){
        windowsFull = true;
      }

// check to see if there are still student in line
      if(!(studentQueue->isEmpty())){

        //while students are stil in line and the current time of arrival is the arrival time of the next student
        //and there is a window available, send student to window

        while(!(studentQueue->isEmpty()) && (currentTime >= studentQueue->peek()->arrivalTime) && !totalWindowsFull){
          for(int i = 0; numWindows; ++i){
            if(windows[i] == 0){
              windows[i] = studentQueue->peek()->timeNeeded;
              studentQueue->peek()->timeLeave = currentTime;
              studentQueue->peek()->atWindow = true;

              //keep track of what window student went in
              studentQueue->peek()->windowNumber = i;

              totalWindowsFull++; // make the window full once the student is send to that window

              break;


            }
          }

          //remove student from line since it was already helped, add that to the list of student helped.
          studentsHelped->insertBack(studentQueue->remove());

          //check if windows are full in case the nest sutdnet in line has same arrival time
          if(totalWindowsFull == numWindows)
            windowsFull = true;

        }

        //increment wait time of student still in line
        if((currentTime >= studentQueue->peek()->arrivalTime) && windowsFull)
          studentQueue->peek()->waitTime += 1;


      }
      //if amy of the windows are empty, increment the idle time counter
      for(int i = 0; i< numWindows; ++i){
        if(windows[i]==0){
          idleTimes++;


        }
      }
      currentTime++;


    }//END of simulation

    //calculate metrics
    idleTimesArray = new int[numWindows]; // initialize idle time array to help with calculations later on

    //idle times of windows to be total time of Simulation

    for(int i  = 0; i< numWindows; ++i){
      idleTimesArray[i] = currentTime;
    }

    // initialize wait time of each student to be 0
    waitTimeArray = new int[totalStudents];
    for(int i = 0; i<totalStudents; ++i){
      waitTimeArray[i] = 0;
    }

    Student *student; // keep track of student

    while(!studentsHelped->isEmpty()){
      //pull data from student to calculate metrics

      student = studentsHelped->removeFront();

      //fill wait time array
      int studentWindowNumber = student->windowNumber;

      //idle time for each window =  total time of simulation - time that student was at the window
      for(int i = 0; i<numWindows; ++i){
        idleTimesArray[i] -= student->timeNeeded;
      }
    }

    //fill wait time array with the times of each student
    for(int i=0; i<totalStudents; ++i){
      if(i == (studentsHelped->getSize())){
        waitTimeArray[i] = student ->waitTime;
      }
    }

    //CALL PRINT STATS

      printStatistics();

      file.close();

}


void Simulation::printStatistics(){

  cout<<"The following statistics were calculated based on the simulation: \n"<<endl;

  cout<< "1. The mean student wait time: ";
  cout<< meanWaitTime()<< "\n"<<endl;

  cout<< "2. The median student wait time: ";
  cout<< medianWaiTime()<< "\n"<<endl;

  cout << "3. The longest student wait time: ";
  cout << longestWaitTime()<< "\n"<<endl;

  cout<<  "4. The number of students waiting over 10 minutes: ";
  cout << studentsWaitingTen()<< "\n" << endl;

  cout<< "5. The mean window idle time: ";
  cout << meanWindowIdleTime() << "\n"<< endl;

  cout<< "6. The longest window idle time: ";
  cout<< longestIdleTime()<< "\n"<< endl;

  cout << "7. Number of windows idle for over 5 minutes: ";
  cout << numberOfWindowIdleFive() << "\n "<<  endl;


}
double Simulation:: meanWaitTime(){

// calculate mean student wait time 1.
  int sumWaitTimes = 0;
  for(int i = 0; i< totalStudents; ++i){
    sumWaitTimes + waitTimeArray[i];
  }
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

   double meanWindowIdleTime = (double)idleTimes/numWindows;
   return meanWindowIdleTime;
}


int Simulation::longestIdleTime(){
  //calculate longest idle time 6.

  int longestIdleTime = 0;

  for(int i = 0; i < numWindows; ++i){
    if(idleTimesArray[i]> longestIdleTime){
      longestIdleTime = idleTimesArray[i];

    }
  }
  return longestIdleTime;
}

int Simulation::numberOfWindowIdleFive(){

  //calculate number of windows idle for over 5 minutes 7.
  int numWindowsIdleFive = 0;

  for(int i = 0; i < numWindows; ++i){
    if(idleTimesArray[i]> 5){
      numWindowsIdleFive++;
    }
  }

  return numWindowsIdleFive;
}



/*//reading file and getting the necessary information
void Simulation::readFile(string fName){

  fstream inputFile;

  //inputFile.open(file);

  string fileInfo;
  int lineNumber;

  studentQueue = new Queue<Student*>();

  if(inputFile.is_open()){
    //get number of windows
    getline(inputFile, fileInfo);

    windowsAvailable = stoi(fileInfo); //converting string to int

    windows = new Window[windowsAvailable];

    for(int i = 0; i<windowsAvailable; ++i){
        Window *w = new Window();
        widows[i] = w;
    }
    lineNumber++;

    //student information
    while(getline(inputFile, fileInfo)){
      arrivedAt = stoi(fileInfo);

      getline(inputFile,fileInfo);

      numCurrentStudents = stoi(fileInfo);

      totalStudents += numCurrentStudents;

      //loop to create new students

      for(int i=0; i<numCurrentStudents; ++i){
        getline(inputFile,fileInfo);
        timeNeed = stoi(fileInfo);

        //initialize each student with their arrival time and time they need
        Student *student = new Student(arrivedAt, timeNeed);

        //insert student in Queue
        studentQueue->insert(student);
      }
    }//end of while

  }

}

void Simulation::clock(int t){
  for(int i = 0; i<windowsAvailable; ++i){
    if(!windows[i]->empty){
      windows[i]->idleTime--;
      //decreases when there is a student
    }
    else
      windows[i]->idleTime++;
      //idle time increases where there is no student
  }

  if(!studentQueue.isEmpty()){
    //create pointer to current students

    //ListNode<Student*> *curr = studentQueue.front;
  }
}*/
