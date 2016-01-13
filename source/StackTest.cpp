#include<cassert>
#include<iostream>
#include<stack>
#include"stack.h"
#include"test.h"
#include"stacktest.h"

namespace stacktest{
	void stacktest()
	{
		testcase1();
		testcase2();
		testcase3();
		testcase4();
		std::cout << "Stack test success!" <<std::endl;
	}

	//test for push && top
	void testcase1()
	{
		stack<int> s1;
		std::stack<int> s2;
		for(int i = 0; i < 10; i++)
		{
			s1.push(i);
			s2.push(i);
			assert(s1.top() == s2.top());
		}
	}

	//test for pop
	void testcase2()
	{
		stack<int> s1;
		std::stack<int> s2;
		for(int i = 0; i < 10; i++)
		{
			s1.push(i);
			s2.push(i);
		}
		s1.pop();
		s2.pop();
		assert(s1.top() == s2.top()); 
	}

	void testcase3()
	{
		stack<int> s1;
		std::stack<int> s2;
		for(int i = 0; i < 10; i++)
		{
			s1.push(i);
			s2.push(i);
		}
		assert(s1.size() == s2.size());
	}

	void testcase4()
	{
		stack<int> s1;
		s1.push(1);
		assert(!s1.empty());
	}

}