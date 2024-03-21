//Kush and Taha

/*
 * DNode.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: 13027
 */

#include <iostream>
#include "DNode.hpp"
#include "Task.hpp"
using namespace std;

/* write your constructors here! */

DNode::DNode() {
    task = new Task();
    next = NULL;
    prev = NULL;
}

DNode::DNode(string taskname, int priority, int hours, int mins){
    task = new Task(taskname,priority,hours,mins);
}

DNode::~DNode() {
	cout << "deleting node with task " << task->tasknum << endl;
	delete task;
	prev = NULL;
	next = NULL;
}