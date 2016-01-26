#include"algorithm.h"
#include"algorithmtest.h"
#include"stl_function.h"
#include"iterator.h"
#include"vector.h"
#include<string>
#include<iostream>
#include<cassert>

using namespace mystl;

namespace algorithmtest{
	void algorithmtest()
	{
		testcase1();
		testcase2();
		testcase3();
		std::cout << "Algortihm test success!" <<std::endl;
	}

	//test for accumulate, inner_prodeuct, partial_sum, adjacent_difference
	void testcase1()
	{
		int ia[5] = {1,2,3,4,5};
		int res = 0;
		vector<int> iv(ia, ia+5);
		res = mystl::accumulate(iv.begin(), iv.end(), 0);
		assert(res == 15);
		res = mystl::accumulate(iv.begin(), iv.end(), 0, minus<int>());
		assert(res == -15);
		res = mystl::inner_product(iv.begin(), iv.end(), iv.begin(), 10);
		assert(res == 65);
		res = mystl::inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>());
		assert(res == -20);
		ostream_iterator<int> oite(std::cout, " ");
		//partial_sum(iv.begin(), iv.end(), oite);
		//partial_sum(iv.begin(), iv.end(), oite, minus<int>());
		//adjacent_difference(iv.begin(), iv.end(), oite);
		//adjacent_difference(iv.begin(), iv.end(), oite, plus<int>());
		res = mystl::power(10, 3);
		assert(res == 1000);
		res = mystl::power(10, 3, plus<int>());
		assert(res == 30);
	}

	//test for equal
	void testcase2()
	{
		int ia[9] = {0,1,2,3,4,5,6,7,8};
		vector<int> iv1(ia, ia+5);
		vector<int> iv2(ia, ia+9);

		assert(mystl::equal(iv1.begin(), iv1.end(), iv2.begin()));
		assert(mystl::equal(iv1.begin(), iv1.end(), &ia[3]) == false);
		assert(mystl::equal(iv1.begin(), iv1.end(), &ia[3], less<int>()));
		mystl::fill(iv1.begin(), iv1.end(), 9);
		mystl::fill(iv1.begin(), iv1.begin()+3, 7);
		//for_each(iv1.begin(), iv1.end(), display<int>());
		vector<int>::iterator ite1 = iv1.begin();
		vector<int>::iterator ite2 = ite1;
		mystl::advance(ite2, 3);
		mystl::iter_swap(ite1, ite2);
		assert(*ite1 == 9);
		assert(*ite2 == 7);
		assert(9 == max(*ite1, *ite2));
		assert(7 == min(*ite1, *ite2));

		swap(*iv1.begin(), *iv2.begin());

		std::string stra1[] = {"Jamie", "JJHou", "Jason"};
		std::string stra2[] = {"Jamie", "JJhou", "Jerry"};

		assert(mystl::lexicographical_compare(stra1, stra1+2, stra2, stra2+2) == true);
		assert(mystl::lexicographical_compare(stra1, stra1+2, stra2, stra2+2, greater<std::string>()) == false);
	}

	void testcase3()
	{
		;
	}
}