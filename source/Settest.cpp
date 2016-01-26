#include"stl_set.h"
#include"stl_settest.h"
#include<iostream>
#include<cassert>

namespace settest{
	void settest()
	{
		int ia[5] = {0, 1, 2, 3, 4};
		set<int> iset(ia, ia+5);

		assert(iset.size() == 5);
		assert(iset.count(3) == 1);
		iset.insert(3);
		assert(iset.count(3) == 1);
		iset.insert(5);
		assert(iset.size() == 6);
		assert(iset.count(3) == 1);
		iset.erase(1);
		assert(iset.size() == 5);
		set<int>::iterator ite1 = iset.begin();
		set<int>::iterator ite2 = iset.end();
		ite1 = mystl::find(iset.begin(), iset.end(), 3);
		assert(ite1 != iset.end());
		
		ite1 = iset.find(3);
		assert(ite1 != iset.end());
		
		//*ite1 = 9;

		std::cout << "Set test success!" <<std::endl;
	}

	void multisettest()
	{
		int ia[5] = {0, 1, 2, 3, 4};
		multiset<int> iset(ia, ia+5);

		assert(iset.size() == 5);
		assert(iset.count(3) == 1);
		iset.insert(3);
		assert(iset.count(3) == 2);
		assert(iset.size() == 6);
		assert(iset.count(3) == 2);
		iset.erase(1);
		assert(iset.size() == 5);
		set<int>::iterator ite1 = iset.begin();
		set<int>::iterator ite2 = iset.end();
		ite1 = mystl::find(iset.begin(), iset.end(), 3);
		assert(ite1 != iset.end());
		
		ite1 = iset.find(3);
		assert(ite1 != iset.end());
		std::cout << "Multiet test success!" <<std::endl;
	}
}