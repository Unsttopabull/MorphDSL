#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <algorithm>
#include <vector>
#include "nVector.h"

//entry data into queue
//contains pixel position and its priority
struct queue_entry
{

	queue_entry()
	{}

	queue_entry(int x, int y, double _priority): pos(x,y), priority(_priority)
	{
	}

	queue_entry(const nVector<int, 2> &_pos, double _priority): pos(_pos), priority(_priority)
	{
	}

	nVector<int, 2> pos;
	double priority;

	static bool compare(const queue_entry &e1, const queue_entry &e2)
	{
		return e1.priority < e2.priority;
	}

};


struct priority_queue
{

	std::vector<queue_entry> heap;

	priority_queue() 
	{
		heap.reserve(1000);
	}

	//push to vector and sort the new queue item
	void add_entry(const queue_entry& e)
	{
		heap.push_back(e);
		push_heap(heap.begin(), heap.end(), queue_entry::compare);
	}

	size_t size()
	{
		return heap.size();
	}

	queue_entry pop_entry()
	{
		queue_entry top = heap.front();


		pop_heap(heap.begin(), heap.end(), queue_entry::compare);
		heap.pop_back();

		return top;
	}

	int top_priority()
	{
		if (heap.size())
		{
			return heap.front().priority;
		}

		//default return lowest possible priority
		return INT_MIN;
	}
};

#endif 