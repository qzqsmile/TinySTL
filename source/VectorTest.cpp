#include<cassert>
#include<iostream>
#include<vector>
#include<cassert>
#include<string>
#include"test.h"
#include"vector.h"
#include"vectortest.h"

namespace vectortest{
	void vectortest()
	{
		testcase1();
		testcase2();
		testcase3();
		testcase4();
		testcase5();
		testcase6();
		std::cout << "Vector test success!" << std::endl;
	}
	//test for int
	void testcase1()
	{
		vector<int>s1(10, 0);
		std::vector<int>s2(10, 0);
		assert(Test::container_equal(s1, s2));

		//	vector<std::string>s3(2,"STL");
		//	std::vector<std::string>s4(2,"STL");
		//	assert(Test::container_equal(s3, s4));

	}

	//test for push_back && pop_back;
	void testcase2()
	{
		vector<int>s1;
		std::vector<int>s2;
		s1.push_back(1);
		s2.push_back(1);
		assert(Test::container_equal(s1, s2));
		s1.push_back(3);
		s2.push_back(3);
		s1.pop_back();
		s2.pop_back();
		assert(Test::container_equal(s1, s2));
	}

	//test for size;
	void testcase3()
	{
		vector<int>s1(10, 4);
		std::vector<int>s2(10, 4);
		assert(s1.size() == s2.size());
	}

	//test for capacity
	void testcase4()
	{
		vector<int>s1;
		std::vector<int>s2;
		for(int i = 0; i < 100; i++)
		{
			s1.push_back(i);
			s2.push_back(i);
		}
		//assert(s1.capacity() == s2.capacity());
	}

	//test for insert
	void testcase5()
	{
		vector<int> s1;
		std::vector<int> s2;

		for(int i = 0; i < 10; i++)
		{
			s1.push_back(i);
			s2.push_back(i);
		}

		s1.insert(s1.begin(), 100);
		s2.insert(s2.begin(), 100);
		assert(Test::container_equal(s1, s2));
	}

	//test for erase
	void testcase6()
	{
		vector<int> s1;
		std::vector<int> s2;

		for(int i = 0; i < 10; i++)
		{
			s1.push_back(i);
			s2.push_back(i);
		}
		s1.erase(s1.begin());
		s2.erase(s2.begin());
		assert(Test::container_equal(s1, s2));
	}
}