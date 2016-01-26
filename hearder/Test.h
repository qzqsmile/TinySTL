#ifndef TEST_H
#define TEST_H

#include<iterator>
#include"vectortest.h"
#include"listtest.h"
#include"dequetest.h"
#include"queuetest.h"
#include"stacktest.h"
#include"heaptest.h"
#include"slisttest.h"
#include"stl_treetest.h"
#include"stl_settest.h"
#include"stl_maptest.h"
#include"stl_hashtabletest.h"
#include"algorithmtest.h"

namespace Test{
	template<class Container1, class Container2>
	bool container_equal(Container1& con1, Container2& con2){//不是每一个容器都有const_iterator
		auto first1 = std::begin(con1), last1 = std::end(con1);
		auto first2 = std::begin(con2), last2 = std::end(con2);
		for (; first1 != last1 && first2 != last2; ++first1, ++first2){
			if (*first1 != *first2)
				return false;
		}
		return (first1 == last1 && first2 == last2);
	}
}
#endif