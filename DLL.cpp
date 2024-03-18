
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
using namespace std;


DLL::DLL(){
	first = NULL;
    last = NULL;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

DLL::DLL(string taskname, int priority, int hours, int mins){

    tothrs += hours;
    totmin += mins;
}

DLL::~DLL(){
	DNode *current = first;
    while (first){
        first = first->next;
        delete current;
        current = first;
    }
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

void DLL::push(string taskname, int priority, int hours, int mins) {
	
}

Task *DLL::pop() {
	
}

int DLL::remove(int tasknum) {
	
}

void DLL::addTime(int hours, int mins) {
	
}

void DLL::removeTime(int hours, int mins) {
	
}

void DLL::moveUp(int tasknum) {
	
}

void DLL::moveDown(int tasknum) {
	
}

void DLL::changePriority(int tasknum, int newPriority) {
	
}

void DLL::listDuration(int *pHours, int *pMins,int priority) {
	
}

void DLL::printList() {
	DNode *current = first;
	cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
	while (current != NULL) {
		current->task->printTask();
		current = current->next;
	}
	cout << endl;
}

void DLL::printList(int priority) {
	
}

void DLL::printReverse() {

}
