#include<iostream>
#include<algorithm>
#include<typeinfo>
#include"vector.h"


int main(void)
{
	vector<int> s;
	s.push_back(1);
	std::cout << s[0] << std::endl;
	std::cout << s.size() << std::endl;
	s.clear();
	std::cout << s.size() << std::endl;
	return 0;
}