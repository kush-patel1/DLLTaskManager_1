//Kush and Taha

#ifndef DLL_HPP_
#define DLL_HPP_

#include "DNode.hpp"
#include <iostream>
using namespace std;

class DLL {
	DNode *first;
	DNode *last;
	int numTasks;
	int tothrs;
	int totmin;
public:
	DLL();  // constructor - initializes an empty list
	DLL(string taskname, int priority, int hours, int mins);    // constructor, initializes a list with one new node
																// with given information
	~DLL(); // destructor
	void push(string taskname, int priority, int hours, int mins);  // adds a task to the end of the list, BUT if the
	// priority isn't 3, it will move the task up to the end of the set of tasks with that priority.
	// In other words, if the priority is 1, it will traverse the list in reverse order until it finds a
	// task with a priority of 1, and insert the new task between the last task with a priority of
	// 1 and the first task with a priority of 2
	// it also updates the total time of the list
	Task *pop();  // removes the last task from the list - make sure to update the total time of the list
	int remove(int tasknum); // removes a task (base2d on its number) and updates the total time of the list.
						// Returns the task number if it was found, or -1 otherwise.
	void moveUp(int tasknum); // moves task with number tn up one in the list.
						// If it is at the beginning of the list,
						// it will be moved to the end of the list.
						// NOTE: if this moves a task up before a task with a higher priority (1 is
						// higher priority than 2 - I know the wording is a bit weird), then this
						// changes the priority of the task being moved to that higher priority

	void moveDown(int tasknum);  // moves task with task number tn down one in the list.
							// If it is at the end of the list, it will move to
							// beginning of the list.
							// NOTE: if this moves a task after a task with a lower priority (again, 3 is
							// a lower priority than 2) then this changes the priority of the task being
							// moved.
	void changePriority(int tasknum, int newPriority); // changes the priority of the task tasknum
	void listDuration(int *pHours, int *pMins, int priority);  // helper function for printList(int priority)
												// gets the total list duration in hours and minutes (passed
												// in as pointers) of a particular priority (so the total time
												// needed to complete all tasks with priority of p).
	void printList(); // prints the entire task list
	void printReverse(); // prints the task list in reverse
	void printList(int priority); // print out the total duration and list of all tasks with a priority of p
	void addTime(int hours, int mins);  // Helper function to add time to total time of list when pushing a new task
	void removeTime(int hours, int mins);  // helper function to remove time from the total time of the list when
											// popping/removing a task

};


#endif /* DLL_HPP_ */
