# CPSC350-Assignment-4
Student registrar
Assignment 4

Katherine Fontan
2290561
luzfonta@chapman.edu

This assignment simulated a registrar's office and calculates metrics on student wait times and window idle times given a specific traffic flow of students.

- Doubly Linked List:
https://programmercave0.github.io/blog/2017/07/28/C++-Doubly-Linked-List-using-Template-(Data-Structure)
https://www.out4mind.com/en/doubly-linked-list-with-class-templates-part-i/
http://www.cplusplus.com/forum/beginner/71319/

- Queue
https://www.geeksforgeeks.org/queue-linked-list-implementation/

- Compare function
http://www.cplusplus.com/reference/cstdlib/qsort/

if there is not enough data in the file for the number of students, lets say 5 students arrived, but the next following lines only represent the arrival time for 4/5 students, the program throws in the following error and aborts this occurs because it tries to convert something from string to int that doesn't exist.

terminate called after throwing an instance of 'std::invalid_argument'
  what():  stoi
Aborted

I also referenced code for list node, linked list and queue from lectures. Also, the implementation of the classes is within the header files because of generics and Simulation was for consistency purposes.


to run i used g++ *.cpp && ./a.out fileName.txt OR  you can use makefile to run.
