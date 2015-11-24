#include<new.h>

template <class T1, class T2>
inline void construct(T1 *p, const T2& value)
{
	new (p) T1(value);
}

template <class T>
inline void destroy(T *pointer){
	pointer->~T();
}

template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last){
	__destory(first, last, value_type(first));
}

template<class ForwardIterator, class T>
inline void __destory(ForwardIterator first, ForwardIterator last)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivail_destructor;
	__destroy_aux(first, last, trivail_destructor());
}

template<class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type){
	for(;first < last; ++first)
		destroy(&*first);
}

template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type){}
