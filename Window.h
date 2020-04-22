#include <iostream>
using namespace std;

class Window{

  public:


    Window();
    ~Window();

    int idleTime;
    int timeAtWindow;
    bool empty;

};

Window::Window(){
  idleTime = 0;
  empty = true;
  timeAtWindow = 0;
}

Window::~Window(){}
