#ifndef MYLIST_H
#define MYLIST_H

#include<iostream>

template<typename T>
class ListItem
{
public:
	T value() const {return _value};
	ListItem* next() const { return _next;};
	
private:
	T _value;
	ListItem* _next;
};

template <typename T>
class List
{
public:
	void insert_front(T value)
	{
		_size++;
	};
	void insert_end(T value);
	{
		_end 
		_size++;
	};
	void display(std::ostream &os = std::cout) const
	{

	};
	ListItem<T> * front() const
	{
		return _front;
	};
private:
	ListItem<T>* _end;
	ListItem<T>* _front;
	long _size;
};

#endif

//#include"3mylist.h"
//
//template<class Item>
//struct ListIter
//{
//	Item* ptr;
//	ListIter(Item *p = 0)
//		:ptr(p){}
//	Item& operator*() const {return *ptr;}
//	Item* operator->() const{return ptr;}
//
//	ListIter &operator++()
//	{ptr = ptr->next(); return *this;}
//
//	ListIter operator++(int)
//	{ ListIter tmp = *this; ++*this; return tmp;}
//	
//	bool operator==(const ListIter& i)const
//	{return ptr == ptr;}
//
//	bool operator!= (const ListIter& i)const
//	{return ptr != i.ptr;}
//};
//
//int main()
//{
//	List<int> mylist;
//
//	for(int i = 0; i < 5; ++i){
//		mylist.insert_front(i);
//		mylist.insert_end(i+2);
//	}
//	mylist.display();
//
//	ListIter<ListItem<int> >begin(mylist.front());
//	ListIter<ListItem<int> >end;
//	ListIter<ListItem<int> >iter;
//	iter = find(begin, end, 3);
//	if(iter == end)
//		cout <<"not found" <<endl;
//	else
//		cout << "found." << iter->value() << endl;
//
//	iter = find(begin, end, 7);
//	if(iter == end)
//		cout << "not found" << endl;
//	else
//		cout << "found." << iter->value() << endl;
//}