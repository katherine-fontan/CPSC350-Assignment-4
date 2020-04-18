#include "Queue.h"
#include "Student.h"
#include "Window.h"


using namespace std;

class Simulation{
  public:

    Simulation();
    ~Simulation();

    void readFile(string fName);
    void clock(int t);



    //calculate statistics
    double meanWaitTime();
    double medianWaiTime();
    int longestWaitTime();
    int studentsWaitingTen();
    double meanWindowIdleTime();
    int longestIdleTime();
    int numberOfWindowIdleFive();
    void printStatistics();

    //variables given by the file
    int windowsAvailable;
    int arrivedAt;
    int totalStudents;
    int timeNeed;


    //additional variables
    int idleTime;
    int numCurrentStudents;

    //student queue
    Queue<Student*> studentQueue;

    //arrays
    Student* *studentsHelped;
    Window* *windows;


};
