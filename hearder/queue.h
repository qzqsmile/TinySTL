#ifndef QUEUE_H
#define QUEUE_H

#include"stl_config.h"
#include"deque.h"


template<class T, class Sequence = deque<T> >
class queue{
	template<class T, class Sequence>
    friend bool operator== __STL_NULL_TMPL_ARGS (const queue<T,Sequence>& x, const queue<T, Sequence>& y);
	template<class T, class Sequence>
	friend bool operator< __STL_NULL_TMPL_ARGS (const queue& x, const queue& y);
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;
public:
	queue(): c()
	{	}
	bool empty() const{return c.empty();}
	size_type size() const {return c.size();}
	reference front() {return c.front();}
	const_reference back() {return c.back();}
	const_reference back() const{return c.back();}
	void push(const value_type& x) {c.push_back(x);}
	void pop() {c.pop_front();}
};

template<class T, class Sequence>
bool operator== (const queue<T, Sequence>& x, const queue<T, Sequence>& y)
{
	return x.c == y.c;
	//return true;
}

template <class T, class Sequence>
bool operator<(const queue<T, Sequence>&x, const queue<T, Sequence>& y)
{
	return x.c < y.c;
}

template<class T, class Sequence = vector<T>, class Compare = less<typename Sequence::value_type> >
class priority_queue{
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;
	Compare comp;
public:
	priority_queue():c() { }
	explicit priority_queue(const Compare& x) : c(), comp(x) {}

	template<class InputIterator>
	priority_queue(InputIterator first, InputIterator last, const Compare& x)
		:c(first, last), comp(x) {make_heap(c.begin(), c.end(), comp);}
	template<class InputIterator>
	priority_queue(InputIterator first, InputIterator last)
		:c(first, last) {make_heap(c.begin(), c.end(), comp);}

	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}
	const_reference top() const {return c.front();}
	void push(const value_type& x){
		__STL_TRY{
			c.push_back(x);
			push_heap(c.begin(), c.end(), comp);
		}
		__STL_UNWIND(c.clear());
	}

	void pop(){
		__STL_TRY{
			pop_heap(c.begin(), c.end(), comp);
			c.pop_back();
		}
		__STL_UNWIND(c.clear());
	}
};


//template<class T, class Sequence = vector<T>, class Compare = less<typename Sequence::value_type> >
//class priority_queue{
//public:
//	typedef typename Sequence::value_type value_type;
//	typedef typename Sequence::size_type size_type;
//	typedef typename Sequence::reference reference;
//	typedef typename Sequence::const_reference const_reference;
//protected:
//	Sequence c;
//	Compare comp;
//public:
//	priority_queue():c(){}
//	explicit priority_queue(const Compare& x):c(),com(x){}

//	template <class InputIterator> 
//	priority_queue(InputIterator first, InputIterator last, const Compare& x)
//		:c(first, last), comp(x) {make_heap(c.begin(), c.end(), comp);}
//	template<class InputIterator>
//	priority_queue(InputIterator first, InputIterator last)
//		:C(first, last) {make_heap(c.begin(), c.end(), comp);}
//	
//	bool empty() const{return c.empty();}
//	size_type size() const {return c.size();}
//	const_reference top() const {return c.front();}

//	void push(const value_type& x){
//		__STL_TRY{
//			c.push_back(x);
//			push_heap(c.begin(), c.end(), comp);
//		}
//		__STL_UNWIND(c.clear());
//	}
//	void pop(){
//		pop_heap(c.begin(), c.end(), comp);
//		c.pop_back();
//	}
//	__STL_UNWIND(c.clear());
//};

#endif