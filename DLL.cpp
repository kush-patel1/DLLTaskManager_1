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
    DNode *newNode = new DNode (taskname,priority,hours,mins);
    first = newNode;
    last = newNode;
    numTasks = 1;
    addTime(hours, mins);
}

DLL::~DLL(){
    DNode *current = first;
    while(current != nullptr){
        first = current->next;
        delete current;
        current = first;
    }
    first = nullptr;
    last = nullptr;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

void DLL::push(string taskname, int priority, int hours, int mins) {
    DNode *newNode = new DNode(taskname, priority, hours, mins);

    if (first == nullptr && last == nullptr) {
        first = newNode;
        last = first;
    }
    else {
        if (priority == 1) {
            DNode *current = last;

            while (current != nullptr && current->task->priority != 1) {
                current = current->prev;
            }

            if (current == nullptr) {
                newNode->next = first;
                first->prev = newNode;
                first = newNode;
            }
            else {
                newNode->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = newNode;
                }
                current->next = newNode;
                newNode->prev = current;

                if (newNode->next == nullptr) {
                    last = newNode;
                }
            }
        }
        else if (priority == 2){
            DNode *current = last;

            while(current != nullptr && current->task->priority != 2 && priority < current->task->priority){
                current = current->prev;
            }

            if (current == nullptr) {
                newNode->next = first;
                first->prev = newNode;
                first = newNode;
            }
            else{
                newNode->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = newNode;
                }
                current->next = newNode;
                newNode->prev = current;

                if (newNode->next == nullptr) {
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
    if (first != nullptr && last != nullptr) {
        Task *popped = new Task(*current->task);
        if (first != last) {
            remove(current->task->tasknum);
        }
        else {
            first = nullptr;
            last = nullptr;
            numTasks--;
            removeTime(current->task->hr, current->task->min);
            cout << "deleting node with task " << popped->tasknum << endl;
        }
        return popped;
    }
    else{
        return nullptr;
    }
}

int DLL::remove(int tasknum) {
    DNode *current = first;
    while (current != nullptr) {
        if (current->task->tasknum == tasknum) {
            removeTime(current->task->hr, current->task->min);
            numTasks--;
            if (current == first && current == last) {
                first = nullptr;
                last = nullptr;
            }
            else if (current == first) {
                first = current->next;
                first->prev = nullptr;
            }
            else if (current == last) {
                last = current->prev;
                last->next = nullptr;
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

    if(totmin >= 60){
        tothrs += totmin / 60;
        totmin %= 60;
    }

}

void DLL::removeTime(int hours, int mins) {
    tothrs -= hours;
    totmin -= mins;
    if (totmin < 0){
        tothrs -= 1;
        totmin += 60;
    }
}

void DLL::moveUp(int tasknum) {
    DNode *current = first;
    while (current != nullptr && current->task->tasknum != tasknum) {
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if(current->next == nullptr){
        last = current->prev;
        current->next = current->prev;
        current->prev->next = nullptr;

        current->prev->prev->next = current;
        current->prev = current->prev->prev;
        current->next->prev = current;

        if (current->prev != nullptr && current->next->task->priority > current->task->priority) {
            current->task->priority = current->next->task->priority;
        }
    }
    //move to bottom of list
    else if (current->prev == nullptr) {
        first = current->next;
        first->prev = nullptr;

        current->prev = last;
        last->next = current;
        current->next = nullptr;
        last = current;

        if (current->prev != nullptr && current->prev->task->priority > current->task->priority) {
            current->task->priority = current->prev->task->priority;
        }
    }

    else {
        //to make it less confusing
        DNode *prevNode = current->prev;
        DNode *prevPrevNode = current->prev->prev;

        prevNode->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = prevNode;
        }

        if (prevPrevNode != nullptr) {
            prevPrevNode->next = current;
        }
        else {
            first = current;
        }

        current->prev = prevPrevNode;
        current->next = prevNode;
        prevNode->prev = current;

        if (prevPrevNode != nullptr && current->task->priority > prevNode->task->priority) {
            current->task->priority = prevPrevNode->task->priority;
        }

    }
}

void DLL::moveDown(int tasknum) {
    DNode *current = first;
    while (current != nullptr && current->task->tasknum != tasknum) {
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if(current->next == nullptr)
    {
        current = last;
        last = last->prev;
        last->next = nullptr;
        current->prev = nullptr;
        //move to the first node
        current->next = first;
        first->prev = current;
        first = current;

        if (first->next != nullptr && first->next->task->priority < first->task->priority) {
            first->task->priority = first->next->task->priority;
        }
    }
    else if(current->prev == nullptr)
    {
        //re-allocate the first pointer
        DNode *nextNextNode = current->next->next;
        first = current->next;
        current->prev = current->next;
        current->next->prev = nullptr;

        nextNextNode->prev = current;
        current->next = nextNextNode;
        current->prev->next = current;


        if (current->prev != nullptr && current->prev->task->priority > current->task->priority) {
            current->task->priority = current->next->task->priority;
        }

    }
    else if(current->next->next == nullptr){
        current->prev->next = current->next;
        current->next->prev = current->prev;

        last->next = current;
        current->prev = last;
        current->next = nullptr;
        last = current;
    }
    else
    {
        DNode *nextNode = current->next;
        DNode *nextNextNode = nextNode->next;

        current->next = nextNextNode;
        if (nextNextNode != nullptr) {
            nextNextNode->prev = current;
        }

        nextNode->prev = current->prev;
        if (current->prev != nullptr) {
            current->prev->next = nextNode;
        }
        else {
            first = nextNode;
        }

        nextNode->next = current;
        current->prev = nextNode;

        if (current->prev != nullptr && current->prev->task->priority > current->task->priority) {
            current->task->priority = current->prev->task->priority;
        }
    }
}

void DLL::changePriority(int tasknum, int newPriority) {
    DNode *current = first;
    while((current->task->tasknum != tasknum) && (current != nullptr)){
        current = current->next;
    }
    if(current->task->priority == newPriority){
        if(newPriority == 3 && current->next == nullptr){
            return;
        }
        while (current->task->priority == current->next->task->priority) {
            moveDown(current->task->tasknum);
        }
    }
    else if(current->task->priority > newPriority){
        while(current->prev->task->priority != newPriority){
            moveUp(current->task->tasknum);
        }
        current->task->priority = newPriority;
    }
    else if(current->task->priority < newPriority){
        current->task->priority = newPriority;
        if(newPriority == 3){
            while(current->next != nullptr){
                moveDown(current->task->tasknum);
            }
        }
        else{
            while(current->next->task->priority != newPriority + 1){
                moveDown(current->task->tasknum);
            }
        }

    }
}

void DLL::listDuration(int *pHours, int *pMins,int priority) {
    DNode *current = first;
    while(current != nullptr){
        if (current->task->priority == priority){
            *pHours += current->task->hr;
            *pMins += current->task->min;
        }
        current = current->next;
    }
    *pHours += *pMins / 60;
    *pMins = *pMins % 60;
}

void DLL::printList() {
    DNode *current = first;
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    while (current != nullptr) {
        current->task->printTask();
        current = current->next;
    }
    cout << endl;
}

void DLL::printList(int priority) {
    int hours = 0;
    int minutes = 0;
    listDuration(&hours, &minutes,priority);
    cout << "Total Time Required: "<<hours<< ":"<<minutes<<endl;
    DNode *current = first;
    while (current != nullptr) {
        if (current->task->priority == priority) {
            current->task->printTask();
        }
        current = current->next;
    }
    cout << endl;

}

void DLL::printReverse() {
    DNode *current = last;
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    while (current != nullptr) {
        current->task->printTask();
        current = current->prev;
    }
    cout << endl;
}