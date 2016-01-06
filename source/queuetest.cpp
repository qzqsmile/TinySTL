#include<cassert>
#include<iostream>
#include<queue>
#include"queue.h"
#include"test.h"
#include"queuetest.h"

template<class T, class Sequence>
bool operator==(const queue<T, Sequence>& x, const queue<T, Sequence>& y);

namespace queuetest{
	void queuetest()
	{
		testcase1();
		testcase2();
		testcase3();
		std::cout << "Queue test success!"<< std::endl;
	}

	//test for push && front
	void testcase1()
	{
		queue<int>s1;
		std::queue<int>s2;

		for(auto i = 0; i < 10; i++)
		{
			s1.push(i);
			s2.push(i);
			assert(s1.front() == s2.front());
		}
	}

	//test for operator ==
	void testcase2()
	{
		queue<int>s1;
		queue<int>s2;

		for(int i = 0; i < 4; i++)
		{
			s1.push(i);
			s2.push(i);
		}
		assert(s1 == s2);
		//assert(s1 < s2);
	}

	//test for back;
	void testcase3()
	{
		queue<int>s1;
		std::queue<int>s2;

		for(auto i = 0; i < 10; i++)
		{
			s1.push(i);
			s2.push(i);
			assert(s1.back() == s2.back());
		}
	}
}