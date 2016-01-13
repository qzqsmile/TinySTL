#include<cassert>
#include<iostream>
#include<forward_list>
#include"algorithm.h"
#include"slist.h"
#include"test.h"
#include"slisttest.h"

namespace slisttest{
	void slisttest()
	{
		slist<int> islist;
		assert(islist.size() == 0);
		islist.push_front(9);
		islist.push_front(1);
		islist.push_front(2);
		islist.push_front(3);
		islist.push_front(4);
		assert(islist.size()==5);
		slist<int>::iterator ite;
		ite = find(islist.begin(), islist.end(), 1);
		if(ite != 0)
			islist.insert_after(ite, 99);
	
		assert(islist.front() == 4);
		islist.pop_front();
		assert(islist.front() == 3);
		islist.pop_front();
		assert(islist.front() = 2);
		islist.pop_front();
		assert(islist.front() == 1);
		islist.pop_front();
		assert(islist.front() == 99);
		islist.pop_front();
		assert(islist.front() == 9);

		std::cout << "slist test success!" << std::endl;
	}
}