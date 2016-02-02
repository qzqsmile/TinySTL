#include"algorithm.h"
#include"algorithmtest.h"
#include"stl_function.h"
#include"iterator.h"
#include"vector.h"
#include"stl_set.h"
#include<string>
#include<iostream>
#include<cassert>

using namespace mystl;
using std::cout;
using std::endl;

namespace algorithmtest{
	void algorithmtest()
	{
		testcase1();
		testcase2();
		testcase3();
		testcase4();
		testcase5();
		testcase6();
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

	//test for copy copybackward
	void testcase3()
	{
		int ia[] = {0,1,2,3,4,5,6,7,8};
		mystl::copy(ia+2, ia+7, ia);
		//mystl::for_each(ia, ia+9, display<int>());
		assert(*(ia + 3) == 5);
		int ia1 [] = {0,1,2,3,4,5,6,7,8};
		
		mystl::copy(ia1+2, ia1+7, ia1+4);
		assert(*(ia1 + 4) == 2);

		int ia2[] = {0,1,2,3,4,5,6,7,8};
		mystl::copy_backward(ia2+2, ia2+7, ia2+5);
		assert(*(ia2+4) == 6);
	}

	//test for union
	void testcase4()
	{
		int ia1[6] = {1,3,5,7,9,11};
		int ia2[7]= {1, 1, 2, 3, 5, 8, 13};
		multiset<int> s1(ia1, ia1+6);
		multiset<int> s2(ia2, ia2+7);
		multiset<int>::iterator first1 = s1.begin();
		multiset<int>::iterator last1 = s1.end();
		multiset<int>::iterator first2 = s2.begin();
		multiset<int>::iterator last2 = s2.end();
// 		mystl::set_union(first1, last1, first2, last2, ostream_iterator<int>(std::cout, " "));
//		cout << endl;
//		mystl::set_intersection(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
//		cout << endl;
//		mystl::set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
//		cout << endl;
//		mystl::set_symmetric_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
//		cout << endl;

	}

	//test for adjacent_find
	void testcase5()
	{
		int ia[] = {0,1,2,3,4,5,6,6,6,7,8};
		vector<int> iv(ia, ia+sizeof(ia)/sizeof(int));
		vector<int> iv2(ia+6, ia+8);
		assert(*adjacent_find(iv.begin(), iv.end())==6);
		assert(*adjacent_find(iv.begin(), iv.end(), equal_to<int>()));
		assert(count(iv.begin(), iv.end(), 6) == 3);
		assert(count_if(iv.begin(), iv.end(), bind2nd(less<int>(),7)) == 9);
		assert(*find(iv.begin(), iv.end(), 4) == 4);
		assert(*find_if(iv.begin(), iv.end(), bind2nd(greater<int>(), 2)) == 3);
		assert(*(find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end())+3) == 8);
		assert(*(find_first_of(iv.begin(), iv.end(), iv2.begin(), iv2.end())+3) == 7);
		
		vector<int> iv3(12);
		remove(iv.begin(), iv.end(), 6);
		remove_copy(iv.begin(), iv.end(), iv3.begin(), 6);

		replace(iv.begin(), iv.end(), 6, 3);
		replace_copy(iv.begin(), iv.end(), iv3.begin(), 3, 5);
		replace_if(iv.begin(), iv.end(), bind2nd(less<int>(), 5), 2);
		replace_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(equal_to<int>(), 8), 9);
		reverse(iv.begin(), iv.end());
		reverse_copy(iv.begin(), iv.end(), iv3.begin());
		rotate(iv.begin(), iv.begin()+4, iv.end());
		rotate_copy(iv.begin(), iv.begin()+5, iv.end(), iv3.begin());
		int ia2[3] = {2, 8};
		vector<int> iv4(ia2, ia2+2);
		search(iv.begin(), iv.end(), iv4.begin(), iv4.end());
		search_n(iv.begin(), iv.end(), 2, 8);
		search_n(iv.begin(), iv.end(), 3, 8, less<int>());
		transform(iv.begin(), iv.end(), iv.begin(), bind2nd(minus<int>(), 2));
	//assert();
	}

	void testcase6()
	{
		int ia[] = {12, 17, 20, 22, 23, 30, 33, 40};
		vector<int> iv(ia, ia+sizeof(ia)/sizeof(int));

		assert(*lower_bound(iv.begin(), iv.end(), 21) == 22);
		assert(*upper_bound(iv.begin(), iv.end(), 21) == 22);
		assert(*lower_bound(iv.begin(), iv.end(), 22) == 22);
		assert(*upper_bound(iv.begin(), iv.end(), 22) == 23);
		assert(binary_search(iv.begin(), iv.end(), 33) == 1);
		assert(binary_search(iv.begin(), iv.end(), 34) == 0);
		
		mystl::next_permutation(iv.begin(), iv.end());
		mystl::prev_premutation(iv.begin(), iv.end());
		mystl::random_shuffle(iv.begin(), iv.end());
		mystl::partial_sort(iv.begin(), iv.begin()+4, iv.end());
		mystl::sort(iv.begin(), iv.end());
		mystl::equal_range(iv.begin(),iv.end(), 22);
		mystl::nth_element(iv.begin(), iv.begin()+5, iv.end());
	}
}