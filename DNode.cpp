/*
 * DNode.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: 13027
 */

#include <iostream>
#include "DNode.hpp"
using namespace std;

/* write your constructors here! */



DNode::~DNode() {
	cout << "deleting node with task " << task->tasknum << endl;
	delete task;
	prev = NULL;
	next = NULL;
}