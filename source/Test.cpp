#include<iostream>
#include<algorithm>
#include<typeinfo>
#include"test.h"
#include"priority_queue.h"


int main(void)
{
	vectortest::vectortest();
	listtest::listtest();
	dequetest::dequetest();
	queuetest::queuetest();
	stacktest::stacktest();
	heaptest::heaptest();
	slisttest::slisttest();
	rb_treetest::rb_treetest();
	settest::settest();
	settest::multisettest();
	maptest::maptest();
	maptest::multimaptest();
	hashtabletest::hashtabletest();
	hashtabletest::hashsettest();
	hashtabletest::hash_multisettest();
	hashtabletest::hashmaptest();
	hashtabletest::hash_multimaptest();
	algorithmtest::algorithmtest();
//	rb_treetest::testcase1();
	return 0;
}

