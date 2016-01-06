#include<cassert>
#include<iostream>
#include<deque>
#include"deque.h"
#include"test.h"
#include"dequetest.h"

namespace dequetest
{
	void dequetest()
	{
		testcase1();
		testcase2();
		testcase3();
		testcase4();
		testcase5();
		testcase6();
		std::cout << "deque test success" << std::endl;
	}

	//test for initial
	void testcase1()
	{
		deque<int>s1(10, 1);
		std::deque<int> s2(10, 1);
		assert(Test::container_equal(s1, s2));
	}

	//test for push_back()
	void testcase2()
	{
		deque<int> s1;
		std::deque<int>s2;
		for(auto i = 0; i < 10; i++)
		{
			s1.push_back(i);
			s2.push_back(i);
		}
		assert(Test::container_equal(s1, s2));
	}

	//test for
	void testcase3()
	{
		deque<int> s1;
		std::deque<int> s2;

		for(auto i = 0; i < 10; i++)
		{
			s1.push_back(i);
			s2.push_back(i);
		}
		while((!s1.empty()) && (!s2.empty()))
		{
			assert(s1.front() == s2.front());
			s1.pop_front();
			s2.pop_front();
		}
	}

	//test for push_front & pop_front
	void testcase4()
	{
		deque<int> s1;
		std::deque<int> s2;

		for(auto i = 0; i < 10; i++)
		{
			s1.push_front(i);
			s2.push_front(i);
		}
		assert(Test::container_equal(s1, s2));

		while((!s1.empty()) && (!s2.empty()))
		{
			assert(s1.front() == s2.front());
			s1.pop_front();
			s2.pop_front();
		}
	}

	//test for insert;
	void testcase5()
	{
		deque<int>s1;
		std::deque<int>s2;
		for(int i = 0; i < 10; i++)
		{
			s1.push_back(i);
			s2.push_back(i);
		}
		
		for(auto i = 0; i < 5; i++)
		{
			s1.insert(s1.begin()+i, i);
			s2.insert(s2.begin()+i, i);
		}
		assert(Test::container_equal(s1, s2));
	}

	//test for operation
	 void testcase6()
	 {
		 deque<int>s1(10, 0);
		 std::deque<int> s2(10, 0);

		 assert(s1[3] == s2[3]);
		 s1[0] = 1;
		 assert(s1[0] == 1);
	 }
}