
#ifndef __QUEUE_H
#define __QUEUE_H

// Template classes have to have all the code in the header file
#include <assert.h>

namespace BasicDataStructures
{
	template <class queue_type>
	class Queue
	{
	public:
		Queue();

	private:
		queue_type* array;
		unsigned int head;  // Array index for the head of the queue
		unsigned int tail; // Array index for the tail of the queue
		unsigned int allocation_size;
	};

	template <class queue_type>
		Queue<queue_type>::Queue()
	{
		allocation_size = 16;
		array = new queue_type[ allocation_size ];
		head = 0L;
		tail = 0L;
	}

} // End namespace

#endif

