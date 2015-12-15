#include<iostream>
#include<algorithm>
#include<typeinfo>

using namespace std;

struct __true_type {};

typedef __true_type has;

template<class I, class T>
void func_impl(I iter, T t)
{
	T tmp;
	cout << typeid(iter).name() << endl;
};

template <class I>
inline void func(I iter)
{
	func_impl(iter, *iter);
}

int main(void)
{
	int i;
	func(&i);
	return 0;
}