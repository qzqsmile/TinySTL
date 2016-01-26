#include<iostream>
#include<cassert>
#include"stl_tree.h"
#include"stl_treetest.h"
#include"stl_function.h"
#include"algorithm.h"

namespace rb_treetest{
	void rb_treetest()
	{
		rb_tree<int, int, identity<int>, less<int> > itree;
		assert(itree.size() == 0);
		itree.insert_unique(10);
		itree.insert_unique(7);
		itree.insert_unique(8);
		assert(itree.size() == 3);

		itree.insert_unique(15);
		itree.insert_unique(5);
		itree.insert_unique(6);
		assert(itree.size() == 6);

		itree.insert_unique(11);
		itree.insert_unique(13);
		itree.insert_unique(12);
		assert(itree.size() == 9);

		rb_tree<int, int, identity<int>, less<int> >::iterator ite1 = itree.begin();
		assert(*ite1 == 5);
		std::cout << "rb_tree test success!" <<std::endl;
	}
}