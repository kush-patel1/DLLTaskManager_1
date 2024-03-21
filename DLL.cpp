//Kush and Taha
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
    if(first == NULL){
        first = new DNode(taskname, priority, hours, mins);
        last = first;
        numTasks = 1;
        addTime(hours,mins);
    }
    else{
        DNode *newNode = new DNode(taskname, priority, hours, mins);
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
        numTasks++;
        addTime(hours,mins);
    }

}

DLL::~DLL(){
    DNode *current = first;
    while(current != NULL){
        first = current->next;
        delete current;
        current = first;
    }
    first = NULL;
    last = NULL;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

void DLL::push(string taskname, int priority, int hours, int mins) {
    DNode *newNode = new DNode(taskname, priority, hours, mins);

    if (first == NULL) {
        first = newNode;
        last = first;
    }
    else {
        if (priority != 3) {
            DNode *current = last;

            while (current != NULL && current->task->priority != 1) {
                current = current->prev;
            }

            if (current == NULL) {
                newNode->next = first;
                first->prev = newNode;
                first = newNode;
            }
            else {
                newNode->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = newNode;
                }
                current->next = newNode;
                newNode->prev = current;

                if (newNode->next == NULL) {
                    last = newNode;
                }
            }
        }
        else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
    }
    addTime(hours, mins);
}

Task *DLL::pop() {
    DNode *current = last;
    DNode *temp = current->prev;
    if (first != NULL && last != NULL) {
        Task *popped = current->task;
        if (first != last) {
            last = temp;
            last->next = NULL;
        }
        else {
            first = NULL;
            last = NULL;
        }
        numTasks--;
        removeTime(current->task->hr, current->task->min);
        return popped;
    }
    else{
        return NULL;
    }
}

int DLL::remove(int tasknum) {
    DNode *current = first;
    while (current != NULL) {
        if (current->task->tasknum == tasknum) {
            removeTime(current->task->hr, current->task->min);
            numTasks--;
            if (current == first && current == last) {
                first = NULL;
                last = NULL;
            }
            else if (current == first) {
                first = current->next;
                first->prev = NULL;
            }
            else if (current == last) {
                last = current->prev;
                last->next = NULL;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            delete current;
            return tasknum;
        }
        current = current->next;
    }
    return -1;
}

void DLL::addTime(int hours, int mins) {
	tothrs += hours;
    totmin += mins;

    tothrs += totmin / 60;
    totmin %= 60;
}

void DLL::removeTime(int hours, int mins) {
	tothrs -= hours;
    totmin -= mins;
}

void DLL::moveUp(int tasknum) {
    DNode *current = first;
    while (current != NULL && current->task->tasknum != tasknum) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    if (current == first) {
        first = current->next;
        first->prev = NULL;

        last->next = current;
        current->prev = last;
        current->next = NULL;
        last = current;

        current->task->priority = current->prev->task->priority;
    }
    else {

        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }

        if (current->prev->prev != NULL) {
            current->prev->prev->next = current;
        }
        else {
            first = current;
        }

        current->prev = current->prev->prev;
        current->next = current->prev;
        current->prev->prev = current;

        if (current->prev->prev != NULL && current->prev->prev->task->priority > current->task->priority) {
            current->task->priority = current->prev->prev->task->priority;
        }
    }
}

void DLL::moveDown(int tasknum) {
    DNode *current = first;
    while (current != NULL && current->task->tasknum != tasknum) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    if (current == last) {
        last = current->prev;
        last->next = NULL;

        first->prev = current;
        current->prev = NULL;
        current->next = first;
        first = current;

        if (current->prev == NULL && current->next->task->priority < current->task->priority) {
            current->task->priority = current->next->task->priority;
        }
    }
    else {

        current->next = current->next->next;
        if (current->next->next != NULL) {
            current->next->next->prev = current;
        }

        current->next->prev = current->prev;
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            first = current->next;
        }

        current->next->next = current;
        current->prev = current->next;

        if (current->prev != NULL && current->prev->task->priority > current->task->priority) {
            current->task->priority = current->prev->task->priority;
        }
    }
}

void DLL::changePriority(int tasknum, int newPriority) {
	DNode *current = first;
    while((current->task->tasknum != tasknum) && (current != NULL)){
        current = current->next;
    }
    if (current != NULL){
        current->task->priority = newPriority;
    }
}

void DLL::listDuration(int *pHours, int *pMins,int priority) {
    DNode *current = first;
    while(current != first){
        if (current->task->priority == priority){
            pHours += current->task->hr;
            pMins += current->task->min;
        }
        current = current->next;
    }
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
	DNode *current = first;
    while (current != NULL) {
        if (current->task->priority == priority) {
            current->task->printTask();
        }
        current = current->next;
    }
}

void DLL::printReverse() {
    DNode * current = last;
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    while (current != NULL) {
        current->task->printTask();
        current = current->prev;
    }
    cout << endl;
}
