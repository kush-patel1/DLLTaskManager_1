#ifndef DNODE_HPP_
#define DNODE_HPP_
using namespace std;

#include "Task.hpp"

class DNode {
	friend class DLL;
	Task *task;
	DNode *prev;
	DNode *next;
public:
	DNode(); // empty constructor, sets all variables to default NULL value
	DNode(string taskname, int priority, int hours, int mins);  // node containing a task with the given parameters,
													// sets task variables to appropriate values
	~DNode(); // destructor
};



#endif /* DNODE_HPP_ */
