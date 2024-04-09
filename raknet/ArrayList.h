
#ifndef __LIST_H
#define __LIST_H

namespace BasicDataStructures
{
	template <class list_type>
	class List
	{
	public:
		List();
	private:
		list_type* array;
		unsigned int list_size;
		unsigned int allocation_size;
	};

	template <class list_type>
	List<list_type>::List()
	{
		allocation_size = 16;
		array = new list_type[ allocation_size ];
		list_size = 0;
	}

} // End namespace

#endif
