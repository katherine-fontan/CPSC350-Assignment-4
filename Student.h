#include <iostream>
 using namespace std;

 class Student{

  public:

    Student();
    Student(int arrival, int timeAtWindow);
    ~Student();

    int arrivalTime;
    int timeNeeded;
    int waitTime;
    bool atWindow;


 };
