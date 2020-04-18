#include <iostream>
using namespace std;

class Window{

  public:


    Window();
    ~Window();

    int idleTime;
    bool empty;

};

Window::Window(){
  idleTime = 0;
  empty = true;
}

Window::~Window(){}
