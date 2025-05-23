//Kush and Taha

#ifndef TASKMANAGER_HPP_
#define TASKMANAGER_HPP_
#include "DLL.hpp"
using namespace std;

class TaskManager {
	DLL *list;  // the doubly linked list of tasks
	int lenmin;
	int lensec;
public:
	TaskManager();//constructor that reads tasks from ListofTasks.txt
	TaskManager(string fname);  // constructor that lets you enter your own text file.
	void interface(); //the ridiculously simple Task Manager interface
	void addTask();  //the method for adding a Task to the list  (this calls the DLL push method)
	void removeTask();  //the method called for removing a song (this calls the DLL Remove(int tasknum) method)
	void ByeNow();  //quick goodbye message letting you know the program has ended
	void moveUp(); //moves a song up one in the task list (so the task above it moves down one)-
	//calls the DLL's moveUp(int tasknum) method
	void moveDown(); //Does the opposite of moveUP.  Calls the DLL's moveDown(int tasknum) method
	void changePriorityofTask(); // Changes the priority of a particular task
	void popTask(); // Pops a task from the top of the list
	void readList(string name);  //Reads in a list of tasks from a text file.  name holds the name of the text file
	//void printList();  //prints out your task list (calls the DLL's printList() method
	string strip(string &s);  //I used this to strip special characters and tokenize my string.
	string getTitle(); //I used to read in a  new task list title
	//void getDuration(); // used to find out and print out the playlist's total duration
	void getPriorityTasks(); //This prints out all tasks with those

};



#endif /* TASKMANAGER_HPP_ */
