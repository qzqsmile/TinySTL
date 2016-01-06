#include<iostream>
#include<cassert>
#include<list>
#include"list.h"
#include"listtest.h"
#include"test.h"

namespace listtest{
	void listtest()
	{
		testcase1();
		testcase2();
		testcase3();
		testcase4();
		testcase5();
		//	testcase6();
		//	testcase7();
		//	testcase8();
		//	testcase9();
		std::cout << "List test success!"<<std::endl;
	}

	//test for initial
	void testcase1()
	{
		list<int> s1;
		std::list<int> s2;
		assert(Test::container_equal(s1, s2));
	}

	//test for push_back 
	void testcase2()
	{
		list<int> s1;
		std::list<int> s2;

		for(int i = 0; i < 100; i++)
		{
			s1.push_back(i);
			s2.push_back(i);
		}

		assert(Test::container_equal(s1, s2));
	}

	//test for push_front
	void testcase3()
	{
		list<int> s1;
		std::list<int> s2;

		for(int i = 0; i < 10; i++)
		{
			s1.push_back(i);
			s2.push_back(i);
		}
		for(int i = 10; i > 0; i--)
		{
			s1.push_front(i);
			s2.push_front(i);
		}
		assert(Test::container_equal(s1, s2));
	}

	//test for insert
	void testcase4()
	{
		list<int> s1;
		std::list<int> s2;

		for(int i = 0; i < 10; i++)
		{
			s1.insert(s1.begin(), i);
			s2.insert(s2.begin(), i);
		}
		assert(Test::container_equal(s1, s2));
	}

	//test for unique;
	void testcase5()
	{
		list<int> s1;
		std::list<int> s2;

		for(int i = 0; i < 100; i++)
		{
			s1.push_back(i % 10);
			s2.push_back(i % 10);
		}
		s1.unique();
		s2.unique();
		assert(Test::container_equal(s1, s2));
	}
}