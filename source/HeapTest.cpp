#include<cassert>
#include<iostream>
#include<vector>
#include"vector.h"
#include"heap.h"
#include"test.h"
#include"heaptest.h"

namespace heaptest{
	void heaptest()
	{
		int ia[9] = {0,1,2,3,4,8,9,3,5};
		std::vector<int> ivec(ia, ia+9);

		heapstl::make_heap(ivec.begin(), ivec.end());
		assert(test_is_heap(ivec));
		ivec.push_back(7);
		heapstl::push_heap(ivec.begin(), ivec.end());
		assert(test_is_heap(ivec));
		heapstl::pop_heap(ivec.begin(), ivec.end());
		assert(ivec.back() == 9);
		heapstl::sort_heap(ivec.begin(), ivec.end());
		
		std::cout << "Heap test success" <<std::endl;
	}

	bool test_is_heap(const std::vector<int>& ivec)
	{
		for(std::vector<int>::size_type i = 0; i < (ivec.size() / 2); i++)
		{
			if(((2*i+1) < ivec.size()) &&(ivec[i] < ivec[2*i+1]))
				return false;
			if(((2*i+2) < ivec.size()) && (ivec[i] < ivec[2*i+2]))
				return false;
		}
		return true;
	}
}