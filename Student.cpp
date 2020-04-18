#include "Student.h"
#include <iostream>

using namespace std;


Student::Student(){
   arrivalTime = 0;
   timeNeeded = 0;
   waitTime = 0;
   atWindow = false;
 }

 Student::Student(int arrival, int timeAtWindow){
   arrivalTime = arrival;
   timeNeeded = timeAtWindow;

 }
 Student::~Student(){}
