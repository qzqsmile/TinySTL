#ifndef ALGORITHM_H
#define ALGORITHM_H

#include"type_traits.h"
#include"stl_iterator.h"
#include<cstring>
#include"pair.h"


namespace mystl{
	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __partial_sum(InputIterator first, InputIterator last,
		OutputIterator result, T*);
	template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator __partial_sum(InputIterator first, InputIterator last,
		OutputIterator result, T*, BinaryOperation binary_op);
	template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator __adjacent_difference(InputIterator first, InputIterator last, 
		OutputIterator result, T *, BinaryOperation binary_op);
	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __adjacent_difference(InputIterator first, InputIterator last, 
		OutputIterator result, T *);

	template<class T>
	inline const T& max(const T& a, const T& b)
	{
		return a < b ? b : a;
	}

	template<class T, class Compare>
	inline const T& max(const T& a, const T& b, Compare comp){
		return comp(a, b)? b : a;
	}

	template<class T>
	inline const T& min(const T& a, const T& b)
	{
		return b < a ? b : a;
	}

	template<class T, class Compare>
	inline const T& min(const T& a, const T& b, Compare comp){
		return comp(b, a) ? b : a;
	}

	template<class InputIterator, class T>
	T accumulate(InputIterator first, InputIterator last, T init)
	{
		for(;first != last; ++first)
			init = init + *first;
		return init;
	}

	template<class InputIterator, class T, class BinaryOperation>
	T accumulate(InputIterator first, InputIterator last, T init,
		BinaryOperation binary_op)
	{
		for(;first != last; ++first)
			init = binary_op(init, *first);
		return init;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result){
		if(first == last) return result;
		*result = *first;
		return __adjacent_difference(first, last, result, value_type(first));
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __adjacent_difference(InputIterator first, InputIterator last, 
		OutputIterator result, T *)
	{
		T value = *first;
		while(++first != last){
			T tmp = *first;
			*++result = tmp - value;
			value = tmp;
		}
		return ++result;
	}

	template<class InputIterator, class OutputIterator, class BinaryOperation>
	OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result,
		BinaryOperation binary_op){
			if(first == last) return result;
			*result = *first;
			return __adjacent_difference(first, last, result, value_type(first), binary_op);
	}

	template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator __adjacent_difference(InputIterator first, InputIterator last, 
		OutputIterator result, T *, BinaryOperation binary_op)
	{
		T value = *first;
		while(++first != last){
			T tmp = *first;
			*++result = binary_op(tmp, value);
			value = tmp;
		}
		return ++result;
	}

	template<class InputIterator1, class InputIterator2, class T>
	T inner_product(InputIterator1 first1, InputIterator1 last1, 
		InputIterator2 first2, T init)
	{
		for(;first1 != last1; ++first1, ++first2)
			init = init + (*first1 * *first2);
		return init;
	}

	template<class InputIterator1, class InputIterator2, class T,
	class BinaryOperation1, class BinaryOperation2>
		T inner_product(InputIterator1 first1, InputIterator1 last1, 
		InputIterator2 first2, T init, BinaryOperation1 binary_op1,
		BinaryOperation2 binary_op2)
	{
		for(;first1 != last1; ++first1, ++first2)
			init = binary_op1(init, binary_op2(*first1, *first2));
		return init;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator partial_sum(InputIterator first, InputIterator last,
		OutputIterator result){
			if(first == last) return result;
			*result = *first;
			return __partial_sum(first, last, result, value_type(first));
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __partial_sum(InputIterator first, InputIterator last,
		OutputIterator result, T*)
	{
		T value = *first;
		while(++first != last){
			value = value + *first;
			*++result = value;
		}
		return ++result;
	}

	template<class InputIterator, class OutputIterator, class BinaryOperation>
	OutputIterator partial_sum(InputIterator first, InputIterator last,
		OutputIterator result, BinaryOperation binary_op){
			if(first == last) return result;
			*result = *first;
			return __partial_sum(first, last, result, value_type(first), binary_op);
	}

	template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator __partial_sum(InputIterator first, InputIterator last,
		OutputIterator result, T*, BinaryOperation binary_op)
	{
		T value = *first;
		while(++first != last){
			value = binary_op(value, *first);
			*++result = value;
		}
		return ++result;
	}


	template<class T, class Integer>
	inline T power(T x, Integer n){
		return power(x, n, multiplies<T>() );
	}

	template<class T, class Integer, class MonoidOperation>
	T power(T x, Integer n, MonoidOperation op){
		if(n == 0)
			return identity_element(op);
		else{
			while((n & 1) == 0){
				n >>= 1;
				x = op(x, x);
			}
			T result = x;
			n >>= 1;
			while(n != 0){
				x = op(x, x);
				if((n & 1) != 0)
					result = op(result, x);
				n >>= 1;
			}
			return result;
		}
	}


	template<class ForwardIterator, class T>
	void iota(ForwardIterator first, ForwardIterator last, T value){
		while(first != last) *first++ = value++;
	}

	template<class InputIterator1, class InputIterator2>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
		for(; first1 != last1; ++first1, ++first2)
			if(*first1 != *first2)
				return false;
		return true;
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred)
	{
		for(; first1 != last1; ++first1, ++first2)
			if(!binary_pred(*first1, *first2))
				return false;
		return true;
	}

	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value){
		for(; first != last; ++first)
			*first = value;
	}

	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value){
		for(; n > 0; --n, ++first)
			*first = value;
		return first;
	}

	template <class ForwardIterator1, class ForwardIterator2, class T>
	inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*)
	{
		T tmp = *a;
		*a = *b;
		*b = tmp;
	}

	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
		for(; first1 != last1 && first2 != last2; ++first1, first2++){
			if(*first1 < *first2)
				return true;
			if(*first2 < *first1)
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, 
		InputIterator2 first2, InputIterator2 last2,
		Compare comp)
	{
		for(; first1 != last1 && first2 != last2; ++first1, ++first2){
			if(comp(*first1, *first2))
				return true;
			if(comp(*first2, *first1))
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	inline bool lexicographical_compare(const unsigned char* first1,
		const unsigned char* last1,
		const unsigned char* first2,
		const unsigned char* last2
		)
	{
		const size_t len1 = last1 - first1;
		const size_t len2 = last2 - first2;
		const int result = memcmp(first1, first2, min(len1, len2));
		return result != 0 ? result < 0 : len1 < len2;
	}

	template <class InputIterator1, class InputIterator2>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
		while(first1 != last1 && *first1 == *first2){
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1,
		InputIterator1 first2, BinaryPredicate binary_pred)
	{
		while(first1 != last1 && binary_pred(*first1, *first2)){
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}


	template<class T>
	inline void swap(T& a, T& b){
		T tmp = a;
		a = b;
		b = tmp;
	}

	//copy function
	template<class InputIterator, class OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last,
		OutputIterator result)
	{
		return __copy_dispatch<InputIterator, OutputIterator>()
			(first, last, result);
	}

	inline char *copy(const char * first, const char * last, char *result)
	{
		memmove(result, first, last-first);
		return result + (last-first);
	}

	inline wchar_t * copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	{
		memmove(result, first, sizeof(wchar_t) * (last - first));
		return result + (last-first);
	}

	template<class ForwardIterator1, class ForwardIterator2>
	inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b){
		__iter_swap(a, b, value_type(a));
	}

	template<class InputIterator, class OutputIterator>
	struct __copy_dispatch
	{
		OutputIterator operator() (InputIterator first, InputIterator last,
			OutputIterator result){
				return __copy(first, last, result, iterator_category(first));
		}
	};

	template<class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2 copy_backward ( BidirectionalIterator1 first,
		BidirectionalIterator1 last,
		BidirectionalIterator2 result )
	{
		while (last!=first) *(--result) = *(--last);
		return result;
	}

	template<class T>
	struct __copy_dispatch<T*, T*>
	{
		T* operator()(T* first, T* last, T* result){
			typedef typename __type_traits<T>::has_trivial_assignment_operator t;
			return __copy_t(first, last, result, t());
		}
	};

	template<class T>
	struct __copy_dispatch<const T*, T*>
	{
		T* operator() (const T* first, const T* last, T* result){
			typedef typename __type_traits<T>::has_trivial_assignment_operator t;
			return __copy_t(first, last, result, t());
		}
	};

	template<class InputIterator, class OutputIterator>
	inline OutputIterator __copy(InputIterator first, InputIterator last,
		OutputIterator result, input_iterator_tag)
	{
		for(; first != last; ++result, ++first)
			*result = *first;
		return result;
	}

	template<class RandomAccessIterator, class OutputIterator>
	inline OutputIterator
		__copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag)
	{
		return __copy_d(first, last, result, distance_type(first));
	}

	template<class RandomAccessIterator, class OutputIterator, class Distance>
	inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last,
		OutputIterator result, Distance *)
	{
		for(Distance n = last - first; n > 0; --n, ++result, ++first)
			*result = *first;
		return result;
	}

	template<class T>
	inline T* __copy_t(const T* first, const T* last, T* result, __true_type){
		memmove(result, first, sizeof(T) * (last-first));
		return result + (last - first);
	}

	template<class T>
	inline T* __copy_t(const T* first, const T* _last, T* result, __false_type){
		return __copy_d(first, last, result, (ptrdiff_t *)0 );
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
		InputIterator2 last2, OutputIterator result)
	{
		while(first1 != last1 && first2 != last2)
		{
			if(*first1 != last1 && first2 != last2)
			{
				if(*first1 < *first2)
				{
					*result = *first1;
					++first1;
				}
				else if(*first2 < *first1){
					*result = *first2;
					++first2;
				}
				else{
					*result = *first1;
					++first1;
					++first2;
				}
				++result;
			}
		}
		return copy(first2, last2, copy(first1, last1, result));
	}

	template<class InputIterator1, class InputIterator2,class OutputIterator>
	OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, 
		InputIterator2 first2, InputIterator2 last2,
		OutputIterator result)
	{
		while(first1 != last1 && first2 != last2)
		{
			if(*first1 < *first2)
				++first1;
			else if (*first2 < *first1)
				++first2;
			else{
				*result = *first1;
				++first1;
				++first2;
				++result;
			}
			return result;
		}
	}

	template <class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		OutputIterator result)
	{
		while(first1 != last1 && first2 != last2)
		{
			if(*first1 < *first2)
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if(*first2 < *first1)
				++first2;
			else{
				++first1;
				++first2;
			}
		}
		return copy(first1, last1, result);
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_symmetric_difference(InputIterator1 first1,
		InputIterator1 last1,
		InputIterator2 first2,
		InputIterator2 last2,
		OutputIterator result)
	{
		while(first1 != last1 && first2 != last2)
		{
			if(*first1 < *first2)
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if(*first2 < *first1){
				*result = *first2;
				++first2;
				++result;
			}else{
				++first1;
				++first2;
			}
			return copy(first2, last2, copy(first1, last1, result));
		}
	}


	template<class ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		if(first == last) return last;
		ForwardIterator next = first;
		while(++next != last){
			if(*first == *next) return first;
			first = next;
		}
		return last;
	}


	template<class ForwardIterator, class BinaryPredicate>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_pred)
	{
		if(first == last) return last;
		ForwardIterator next = first;
		while(++next != last){
			if(binary_pred(*first, *next)) return first;
			first = next;
		}
		return last;
	}

	template<class InputIterator, class T>
	typename iterator_traits<InputIterator>::difference_type
		count(InputIterator first, InputIterator last, const T& value){
			typename iterator_traits<InputIterator>::difference_type n = 0;
			for(; first != last; ++first)
				if(*first == value)
					++n;
			return n;
	}

	template<class InputIterator, class Predicate>
	typename iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, Predicate pred)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		for(; first != last; ++first)
			if(pred(*first))
				++n;
		return n;
	}

	template<class InputIterator, class Predicate, class Size>
	void count_if(InputIterator first, InputIterator last,
		Predicate pred, Size& n)
	{
		for(; first != last; ++first)
			if(pred(*first))
				++n;

	}

	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& value)
	{
		while(first != last && *first != value) ++first;
		return first;
	}

	template <class InputIterator, class Predicate>
	InputIterator find_if(InputIterator first, InputIterator last, 
		Predicate pred)
	{
		while(first != last && !pred(*first)) ++first;
		return first;
	}


	template<class ForwardIterator1 ,class ForwardIterator2>
	inline ForwardIterator1
		find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
		typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;

		return __find_end(frist1, last1, first2, last2, category1(), category2());
	}

	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		forward_iterator_tag, forward_iterator_tag)
	{
		if(first2 == last2)
			return last1;
		else{
			ForwardIterator1 result = last;
			while(1){
				ForwardIterator1 new_result = search(first1, last1, first2, last2);
				if(new_result == last1)
					return result;
				else{
					result = new_result;
					first1 = new_result;
					++first1;
				}
			}
		}
	}

	template<class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator1
		__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
		BidirectionalIterator2 first2, BidirectionalIterator2 last2,
		bidirectional_iterator_tag, bidirectional_iterator_tag)
	{
		typedef reverse_iterator<BidirectionalIterator1> reviter1;
		typedef reverse_iterator<BidirectionalIterator2> reviter2;

		reviter1 rlast1(first1);
		reviter2 rlast2(first2);

		reviter1 rresult = search(reviter1(last1), rlast1,
			reviter2(last2), rlast2);

		if(rresult == rlast1)
			return last1;
		else{
			BidirectionalIterator1 result = rresult.base();
			advance(result, -distance(first2, last2));
			return result;
		}
	}

	template<class InputIterator, class ForwardIterator>
	InputIterator find_first_of(InputIterator first1, InputIterator last1, 
		ForwardIterator first2, ForwardIterator last2)
	{
		for(;first1 != last1; ++first1)
			for(ForwardIterator iter = first2; iter != last2; ++iter)
				return first1;
		return last1;
	}

	template<class InputIterator, class Function>
	Function for_each(InputIterator first, InputIterator last, Function f)
	{
		for(; first != last; ++first)
			f(*first);
		return f;
	}

	template<class ForwardIterator, class Generator>
	void generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		for(; first != last; ++first)
			*first = gen();
	}

	template<class OutputIterator, class Size, class Generator>
	OutputIterator generate_n(OutputIterator first, Size n, Generator gen){
		for(; n > 0; --n,  ++first)
			*first = gen();
		return first;
	}

	template<class InputIterator1, class InputIterator2>
	bool include(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while(first1 != last1 && first2 != last2)
			if(*first2 < *first1)
				return false;
			else if(*first1 < *first2)
				++first1;
			else
				++first1, ++first2;
			return first2 - last2;
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool include(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
		InputIterator2 last2, Compare comp)
	{
		while(first1 != last1 && first2 != last2)
			if(comp(*first2, *first1))
				return false;
			else if(*first1 < *first2)
				++first1;
			else
				++first1, ++first2;
			return first2 == last2;
	}

	template<class ForwardIterator>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
	{
		if(first == last) return first;
		ForwardIterator result = first;
		while(++first != last)
			if(*result < *first) result = first;
		return result;
	}

	template<class ForwardIterator, class Compare>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp)
	{
		if(first == last) return first;
		ForwardIterator result = first;
		while(++first != last)
			if(comp(*result, *first)) result = first;
		return result;
	}

	template <class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
		InputIterator2 last2, OutputIterator result)
	{
		while(first1 != last1 && first2 != last2){
			if(*first2 < *first1){
				*result = *first2;
				++first2;
			}
			else{
				*result = *first1;
				++first1;
			}
			++result;
		}
	}


	template <class InputIterator1, class InputIterator2,
	class OutputIterator,class Compare>
		OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		OutputIterator result, Compare comp)
	{
		while(first1  != last1 && first2 != last2){
			if(comp(*first2, *first1)){
				*result = *first2;
				++first2;
			}
			else{
				*result = *first1;
				++first1;
			}
			++result;
		}

		return copy(first2, last2, copy(first1, last1, result));
	}

	template <class ForwardIterator>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
	{
		if(first == last) return first;
		ForwardIterator result = first;
		while(++first != last)
			if(*first < *result) result = first;
		return result;
	}

	template<class ForwardIterator, class Compare>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp)
	{
		if(first == last) return first;
		ForwardIterator result = first;
		while(++first != last)
			if(comp(*first, *result)) result = first;
		return result;
	}

	template<class BidirectionalIterator, class Predicate>
	BidirectionalIterator partition(BidirectionalIterator first,
		BidirectionalIterator last,
		Predicate pred)
	{
		while(true)
		{
			while(true)
				if(first == last)
					return first;
				else if(pred(*first))
					++first;
				else
					break;
				--last;
				while(true)
					if(first == last)
						return first;
					else if(!pred(*last))
						--last;
					else
						break;
					iter_swap(first, last);
					++first;
		}
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator remove_copy(InputIterator first, InputIterator last,
		OutputIterator result, const T& value)
	{
		for(; first != last; ++first)
			if(*first != value){
				*result = *first;
				++result;
			}
			return result;
	}

	template<class ForwardIterator, class T>
	ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value)
	{
		first = find(first, last, value);
		ForwardIterator next = first;
		return first == last ? first : remove_copy(++next, last, first, value);
	}


	template<class ForwardIterator, class Predicate>
	ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
		Predicate pred)
	{
		first = find_if(first, last, pred);
		ForwardIterator next = first;
		return first == last ? first : remove_copy_if(++next, last, first, pred);
	}

	template<class InputIterator, class OutputIterator, class Predicate>
	OutputIterator remove_copy_if(InputIterator first, InputIterator last,
		OutputIterator result, Predicate pred)
	{
		for(; first != last; ++ first)
			if(!pred(*first)){
				*result = *first;
				++result;
			}
			return result;
	}

	template<class ForwardIterator, class T>
	void replace(ForwardIterator first, ForwardIterator last, const T& old_value,
		const T& new_value)
	{
		for(; first != last; ++first)
			if(*first == old_value) 
				*first = new_value;
	}

	template<class InputIterator,class OutputIterator, class T>
	OutputIterator replace_copy(InputIterator first, InputIterator last,
		OutputIterator result, const T& old_value,
		const T& new_value){
			for(;first != last; ++first, ++result)
				*result = *first == old_value ? new_value : *first;
			return result;
	}

	template<class ForwardIterator, class Predicate, class T>
	void replace_if(ForwardIterator first, ForwardIterator last,
		Predicate pred, const T& new_value){
			for(; first != last; ++first)
				if(pred(*first)) *first = new_value;
	}

	template<class Iterator, class OutputIterator, class Predicate, class T>
	OutputIterator replace_copy_if(Iterator first, Iterator last,
		OutputIterator result, Predicate pred, const T& new_value)
	{
		for(;first != last; ++first, ++result)
			*result = pred(*first) ? new_value : *first;
		return result;
	}

	template<class BidirectionalIterator>
	inline void reverse(BidirectionalIterator first, BidirectionalIterator last)
	{
		__reverse(first, last, iterator_category(first));
	}

	template<class BidirectionalIterator>
	void __reverse(BidirectionalIterator first, BidirectionalIterator last,
		bidirectional_iterator_tag)
	{
		while(true)
			if(first == last || first == --last)
				return;
			else
				iter_swap(first++, last);
	}

	template<class RandomAccessIterator>
	void __reverse(RandomAccessIterator first, RandomAccessIterator last,
		random_access_iterator_tag)
	{
		while(first < last) iter_swap(first++, --last);
	}

	template<class BidirectionalIterator, class OutputIterator>
	OutputIterator reverse_copy(BidirectionalIterator first, 
		BidirectionalIterator last,
		OutputIterator result)
	{
		while(first != last)
		{
			--last;
			*result = *last;
			++result;
		}
		return result;
	}


	template<class ForwardIterator, class Distance>
	void __rotate(ForwardIterator first, ForwardIterator middle, 
		ForwardIterator last, Distance*, forward_iterator_tag)
	{
		for(ForwardIterator i = middle; ;)
		{
			iter_swap(first, i);
			++first;
			++i;
			if(first == middle){
				if(i == last) return;
				middle = i;
			}
			else if(i == last)
				i = middle;
		}
	}

	template <class BidirectionalIterator, class Distance>
	void __rotate(BidirectionalIterator first, BidirectionalIterator middle,
		BidirectionalIterator last, Distance *, bidirectional_iterator_tag){
			reverse(first, middle);
			reverse(middle, last);
			reverse(first, last);
	}

	template<class RandomAccessIterator, class Distance>
	void __rotate(RandomAccessIterator first, RandomAccessIterator middle,
		RandomAccessIterator last, Distance*, random_access_iterator_tag){
			Distance n = __gcd(last - first, middle - first);
			while(n--)
				__rotate_cycle(first, last, first + n, middle-first, value_type(first));
	}

	template<class EuclideanRingElement>
	EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n)
	{
		while(n != 0){
			EuclideanRingElement t = m % n;
			m = n;
			n = t;
		}
		return m;
	}

	template<class ForwardIterator>
	inline void rotate(ForwardIterator first, ForwardIterator middle,
		ForwardIterator last)
	{
		if(first == middle || middle == last) return;
		__rotate(first, middle, last, distance_type(first), iterator_category(first));
	}

	template<class RandomAccessIterator, class Distance, class T>
	void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last, 
		RandomAccessIterator initial, Distance shift, T*)
	{
		T value = *initial;
		RandomAccessIterator ptr1 = initial;
		RandomAccessIterator ptr2 = ptr1 + shift;
		while(ptr2 != initial){
			*ptr1 = *ptr2;
			ptr1 = ptr2;
			if(last - ptr2 > shift)
				ptr2 += shift;
			else
				ptr2 = first + (shift - (last - ptr2));
			*ptr1 = value;
		}
	}

	template <class ForwardIterator, class OutputIterator>
	OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle,
		ForwardIterator last, OutputIterator result)
	{
		return copy(first, middle, copy(middle, last, result));
	}

	template<class ForwardIterator1, class ForwardIterator2>
	inline ForwardIterator1 search(ForwardIterator1 first1,
		ForwardIterator1 last1,
		ForwardIterator2 first2,
		ForwardIterator2 last2)
	{
		return __search(first1, last1, first2, last2, distance_type(first1));
	}

	template<class ForwardIterator1, class ForwardIterator2, class Distance1, class Distance2>
	ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		Distance1*, Distance2*)
	{
		Distance1 d1 = 0;
		distance(first1, last1, d1);
		Distance d2 = 0;
		distance(first2, last2, d2);

		if(d1 < d2) return last1;

		ForwardIterator1 current1 = first1;
		ForwardIterator2 current2 = first2;

		while(current2 != last2){
			if(*current1 == *current2){
				++current1;
				++current2;
			}else{
				current1 = ++first1;
				current2 = first2;
				--d1;
			}
		}
		return first1;
	}

	template<class ForwardIterator, class Integer, class T>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T& value){
		if(count <= 0)
			return first;
		else{
			while(first != last){
				Integer n = count - 1;
				ForwardIterator i = first;
				++i;
				while(i != last && n != 0 && *i == value){
					++i;
					--n;
				}
				if(n == 0)
					return first;
				else
					first = find(i, last, value);
			}
			return last;
		}
	}

	template<class ForwardIterator, class Integer, class T, class BinaryPredicate>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
		Integer count, const T& value, BinaryPredicate binary_pred)
	{
		if(count <= 0)
			return first;
		else{
			while(first != last){
				if(binary_pred(*first, value)) break;
				++first;
			}
			while(first != last){
				Integer n = count - 1;
				ForwardIterator i = first;
				++i;
				while(i != last && n != 0 && binary_pred(*i, value)){
					++i;
					--n;
				}
				if(n == 0)
					return first;
				else{
					while(i != last){
						if(binary_pred(*i, value)) break;
						++i;
					}
					first = i;
				}
			}
			return last;
		}
	}

	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator2 swap_ranges(ForwardIterator1 first1,
		ForwardIterator1 last1,
		ForwardIterator2 first2)
	{
		for(; first1 != last1; ++first1, ++first2)
			iter_swap(first1, first2);
		return first2;
	}


	template <class InputIterator, class OutputIterator, class UnaryOperation>
	OutputIterator transform(InputIterator first, InputIterator last,
		OutputIterator result, UnaryOperation op)
	{
		for(; first != last; ++first, ++result)
			*result = op(*first);
		return result;
	}

	template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator transform(InputIterator1 first1, InputIterator1 last1, 
		InputIterator2 first2, OutputIterator result,
		BinaryOperation binary_op){
			for(;first1 != last1; ++first1, ++first2, ++result)
				*result = binary_op(*first1, *first2);
			return result;
	}

	template<class ForwardIterator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last){
		first = adjacent_find(first, last);
		return unique_copy(first, last, first);
	}

	template<class InputIterator, class OutputIterator>
	inline OutputIterator unique_copy(InputIterator first, InputIterator last,
		OutputIterator result)
	{
		if(first == last) return result;
		return __unique_copy(first, last, result, iterator_category(result));
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator __unique_copy(InputIterator first,
		InputIterator last,
		ForwardIterator result,
		forward_iterator_tag){
			*result = *first;
			while(++first != last)
				if(*result != *first) *++result = *first;
			return ++result;
	}

	template<class InputIterator, class OutputIterator>
	inline OutputIterator __unique_copy(InputIterator first, InputIterator last,
		OutputIterator result, output_iterator_tag)
	{
		return __unique_copy(first, last, result, value_type(first));
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __unique_copy(InputIterator first, InputIterator last,
		OutputIterator result, T*)
	{
		T value = *first;
		*result = value;
		while(++first != last)
			if(value != *first){
				value = *first;
				*++result = value;
			}
			return ++result;
	}

	template<class ForwardIterator, class T>
	inline ForwardIterator lower_bound(ForwardIterator first, 
		ForwardIterator last, const T& value)
	{
		return __lower_bound(first, last, value, distance_type(first),
			iterator_category(first));
	}

	template<class ForwardIterator, class T, class Compare>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last,
		const T& value, Compare comp)
	{
		return __lower_bound(first, last, value, comp, distance_type(first), iterator_category(first));
	}

	template<class ForwardIterator, class T, class Distance>
	ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value,
		Distance *, forward_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		ForwardIterator middle;

		while(len > 0){
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if(*middle > value){
				first = middle;
				++first;
				len = len - half -1;
			}
			else
				len = half;
		}

		return first;
	}

	template <class RandomAccessIterator, class T, class Distance>
	RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last,
		const T& value, Distance*, random_access_iterator_tag)
	{
		Distance len = last - first;
		Distance half;
		RandomAccessIterator middle;

		while(len > 0)
		{
			half = len >> 1;
			middle = first + half;
			if(*middle < value){
				first = middle + 1;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}

	template<class ForwardIterator, class T>
	inline ForwardIterator upper_bound(ForwardIterator first,
		ForwardIterator last,
		const T& value)
	{
		return __upper_bound(first, last, value, distance_type(first), iterator_category(first));
	}

	template<class ForwardIterator, class T, class Distance>
	ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value,
		Distance *, forward_iterator_tag)
	{
		Distance len;
		Distance half;
		ForwardIterator middle;

		distance(first, last, len);

		while(len > 0)
		{
			half = len >> 1;
			middle = first + half;
			if(*middle > value){
				first = middle;
				first++;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}

	template<class RandomAccessIterator, class T, class Distance>
	RandomAccessIterator __upper_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value,
		Distance *, random_access_iterator_tag)
	{
		Distance len;
		Distance half;
		RandomAccessIterator middle;
		len = last - first;

		while(len > 0)
		{
			half = len >> 1;
			middle = first + half;
			if(*middle > value){
				first = middle + 1;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}


	template <class ForwardIterator, class T>
	bool binary_search(ForwardIterator first, ForwardIterator last, const T& value)
	{
		ForwardIterator i = lower_bound(first, last, value);
		return i != last && !(value < *i);
	}

	template<class ForwardIterator, class T, class Compare>
	bool binary_serach(ForwardIterator first, ForwardIterator last, const T& value,
		Compare comp)
	{
		ForwardIterator i = lower_bound(first, last, value, comp);
		return i != last && !comp(value, *i);
	}

	template<class BidirectionalIterator>
	bool next_permutation(BidirectionalIterator first, BidirectionalIterator last)
	{
		if(first == last) return false;
		BidirectionalIterator i = first;

		++i;
		if(i == last) return false;
		i = last;
		--i;

		for(;;){
			BidirectionalIterator ii = i;
			--i;
			if(*i < *ii){
				BidirectionalIterator j = last;
				while(!(*i < *--j));
				iter_swap(i, j);
				reverse(ii, last);
				return true;
			}
			if(i == first){
				reverse(first, last);
				return false;
			}
		}            
	}

	template<class BidirectionalIterator>
	bool prev_premutation(BidirectionalIterator first, BidirectionalIterator last){
		if(first == last) return false;
		BidirectionalIterator i = first;
		++i;

		if(i == last) return false;
		i = last;
		--i;

		for(;;){
			BidirectionalIterator ii = i;
			--i;

			if(*ii < *i){
				BidirectionalIterator j = last;
				while(!(*--j < *i));
				iter_swap(i, j);
				reverse(ii, last);
				return true;
			}
			if(i == first){
				reverse(first, last);
				return false;
			}
		}
	}

	template <class RandomAccessIterator>
	inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last)
	{
		__random_shuffle(first, last, ditance_type(first));
	}

	template<class RandomAccessIterator, class Distance>
	void __random_shuffle(RandomAccessIterator first, RandomAccessIterator last, Distance *)
	{
		if(first == last) return;
		for(RandomAccessIterator i = first + 1; i != last; ++i)
			iter_swap(i, first + Distance(rand() % ((i - first) + 1)));
	}

	template<class RandomAccessIterator, class RandomNumberGenerator>
	void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator& rand){
		if(first == last) return;
		for(RandomAccessIterator i = first + 1; i != last; i++)
			iter_swap(i, first + rand((i-first) + 1));
	}

	template<class RandomAccessIterator>
	inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last)
	{
		__partial_sort(first, middle, last, value_type(first));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	}

	template <class RandomAccessIterator, class T>
	void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
		RandomAccessIterator last, T*)
	{
		make_heap(first, middle);
		for(RandomAccessIterator i = middle; i < last; i++)
			if(*i < *first)
				__pop_heap(first, middle, i, T(*i), distance_type(first));
		sort_heap(first, middle);
	}

	template<class RandomAccessIterator>
	void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
	{
		if(first == last) return;
		for(RandomAccessIterator i = first + i; i != last; i++)
			__linear_insert(first, i, value_type(first));
	}

	template<class RandomAccessIterator, class T>
	inline void __linear_insert(RandomAccessIterator first, RandomAccessIterator last, T*)
	{
		T value = *last;
		if(value < *first){
			copy_backward(first, last, last + 1);
			*first = value;
		}
		else
			__unguarded_linear_insert(last, value);
	}

	template <class RandomAccessIterator, class T>
	void __unguard_linear_insert(RandomAccessIterator last, T value)
	{
		RandomAccessIterator next = last;
		--next;

		while(value < *next){
			*last = next;
			last = next;
			--next;
		}
		*last = value;
	}


	template<class T>
	inline const T& __median(const T& a, const T& b, const T& c){
		if(a < b)
			if(b < c)
				return b;
			else if(a < c)
				return c;
			else
				return a;
		else if(a < c)
			return a;
		else if(b < c)
			return c;
		else 
			return b;
	}

	template<class RandomAccessIterator, class T>
	RandomAccessIterator __unguard_partition(RandomAccessIterator first, RandomAccessIterator last, T pivot){
		while(true){
			while(*first < pivot) ++first;
			--last;
			while(pivot < *last) --last;
			if(!(first < last)) return first;
			iter_swap(first, last);
			++first;
		}
	}

	template<class RandomAccessIterator>
	inline void sort(RandomAccessIterator first, RandomAccessIterator last){
		if(first != last){
			__introsort_loop(first, last, value_type(first), __lg(last-first)*2);
			__final_insertion_sort(first, last);
		}
	}

	template<class Size>
	inline Size __lg(Size n){
		Size k;
		for(k = 0; n > 1; n >>= 1) ++k;
		return k;
	}

	const int __stl_threshold = 16;

	template<class RandomAccessIterator, class T, class Size>
	void __introsort_loop(RandomAccessIterator first, RandomAccessIterator last, T*,
		Size depth_limit)
	{
		while(last - first > __stl_threshold)
		{
			if(depth_limit == 0)
			{
				partial_sort(first, last, last);
				return ;
			}
			--depth_limit;

			RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first, *(first))));

			__introsort_loop(cut, last, value_type(first), depth_limit);
			last = cut;
		}
	}

	template<class RandomAccessIterator>
	void __finial_insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
	{
		if(last-first > __stl_threshold)
		{
			__insertion_sort(first, first + __stl_threshold);
			__unguraded_insertion_sort(first + __stl_threshold, last);
		}
		else
			__insertion_sort(first, last);
	}

	template<class RandomAccessIterator>
	inline void __unguard_insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
	{
		__unguard_insertion_sort_aux(first, last, value_type(first));
	}

	template<class RandomAccessIterator, class T>
	void __unguarded_insertion_sort_aux(RandomAccessIterator first, RandomAccessIterator last, T*)
	{
		for(RandomAccessIterator i = first; i != last; i++)
		{
			__unguarded_linear_insert(i, T(*i));
		}
	}

	template<class ForwardIterator, class T>
	inline pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const T& value)
	{
		return __equal_range(first, last, value, distance_type(first), iterator_category(first));
	}

	template<class RandomAccessIterator, class T, class Distance>
	pair<RandomAccessIterator, RandomAccessIterator>
		__equal_range(RandomAccessIterator first, RandomAccessIterator last,
		const T& value, Distance *, random_access_iterator_tag)
	{
		Distance len = last-first;
		Distance half;
		RandomAccessIterator middle, left, right;

		while(len > 0)
		{
			half = len >> 1;
			middle = first + half;
			if(*middle < value)
			{
				first = middle + 1;
				len = len - half -1;
			}
			else if(value < *middle)
				len = half;
			else{
				lower_bound(first, middle, value);
				right = upper_bound(++middle, first + len, value);
				return pair<RandomAccessIterator, RandomAccessIterator>(left, right);
			}
		}

		return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
	}

	template<class ForwardIterator, class T, class Distance>
	pair<ForwardIterator, ForwardIterator>
		__equal_range(ForwardIterator first, ForwardIterator last, const T& value,
		Distance*, forward_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		ForwardIterator middle, left, right;

		while(len > 0){
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if(*middle < value){
				first = middle;
				++first;
				len = len - half -1;
			}
			else if(value < *middle)
				len = half;
			else{
				left = lower_bound(first, middle, value);
				advance(first, len);
				right = upper_bound(++middle, first, value);
				return pair<ForwardIterator, ForwardIterator>(left, right);
			}
		}
		return pair<ForwardIterator ,ForwardIterator>(first, first);
	}

	template<class BidirectionalIterator>
	inline void inplace_merge(BidirectionalIterator first, BidirectionalIterator middle,
		BidirectionalIterator last)
	{
		if(first == middle || middle == last) return;
		__inplace_merge_aux(first, middle, last, value_type(first), distance_type(first));
	}

	template <class BidirectionalIterator, class T, class Distance>
	inline void __inplace_merge_aux(BidirectionalIterator first, BidirectionalIterator middle, 
		BidirectionalIterator last, T*, Distance*)
	{
		Distance len1 = 0;
		distance(first, middle, len1);
		Distance len2 = 0;
		distance(middle,last, len2);

		temporary_buffer<BidirectionalIterator, T> buf(first, last);
		if(buf.begin() == 0)
			__merge_without_buffer(first, middle, last, len1, len2);
		else
			__merge_adaptive(first, middle, last, len1, len2, buf.begin(), Distance(buf.size()));
	}


	template<class BidirectionalIterator, class Distance, class Pointer>
	void __merge_adaptive(BidirectionalIterator first, BidirectionalIterator middle,
		BidirectionalIterator last, Distance len1, Distance len2,
		Pointer buffer, Distance buffer_size)
	{
		if(len1 <= len 2 && len1 <= buffer_size)
		{
			Pointer end_buffer = copy(first, middle, buffer);
			merge(buffer, end_buffer, middle, last, first);
		}
		else if(len2 <= buffer_size){
			Pointer end_buffer = copy(middle, last, buffer);
			__merge_backward(first, middle, buffer, end_buffer, last);
		}
		else{
			BidirectionalIterator first_cut = first;
			BidirectionalIterator second_cut = middle;
			Distance len11 = 0;
			Distance len22 = 0;
			if(len1 > len2){
				len11 = len1 / 2;
				advance(first_cut, len11);
				second_cut = lower_bound(middle, last, *first_cut);
				distance(middle, second_cut, len22);
			}
			else{
				len22 = len2 / 2;
				advance(second_cut, len22);
				first_cut = upper_bound(first, middle, *second_cut);
				distance(first, first_cut, len11);
			}
			BidrectionalIterator new_middle = __rotate_adaptive(first_cut, middle, second_cut,
				len1-len11, len22, buffer, buffer_size);
			__merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size);
			__merge_adaptive(new_middle, second_out, last, len1-len11, len2-len22, buffer, buffe_size);
		}
	}

	template<class BidirectionalIterator1, class BidirectionalIterator2, class Distance>
	BidirectionalIterator1 __rotate_adaptive(BidirectionalIterator1 first, 
		BidirectionalIterator2 middle,
		Distance len1, Distance len2,
		BidirectionalIterator2 buffer,
		Distance buffer_size)
	{
		BidirectionalIterator2 buffer_end;
		if(len1 > len2 && len2 <= buffer_size){
			buffer_end = copy(middle, last, buffer);
			copy_backward(first, middle, last);
			return copy(buffer, buffer_end, first);
		}else if(len1 <= buffer_size){
			buffer_end = copy(first, middle, buffer);
			copy(middle, last, first);
			return copy_backward(buffer, buffer_end, last);
		}else{
			rotate(first, middle, last);
			advance(first, len2);
			return first;
		}
	}

	template<class RandomAccessIterator>
	inline void nth_element(RandomAccessIterator first,
		RandomAccessIterator nth,
		RandomAccessIterator last){
			__nth_element(first, nth, last, value_type(first));
	}

	template<class RandomAccessIterator, class T>
	void __nth_element(RandomAccessIterator first,
		RandomAccessIterator nth,
		RandomAccessIterator last, T*)
	{
		while(last - first > 3)
		{
			RandomAccessIterator out = __unguarded_partition(first, last,
				T(__median(*first, *(first + (last-first)/2),*(last-1))));
			if(cut <= nth)
				first = cut;
			else 
				last = cut;
		}
		__insertion_sort(first, last);
	}

	template<class BidirectionalIter>
	void mergesort(BidirectionalIter first, BidirectionalIter last)
	{
		typename iterator_traits<BidirectionalIter>::difference_type n =distance(first, last);
		if(n == 0 || n==1)
			return;
		else{
			BidirectionalIter mid = first + n / 2;
			mergesort(first, mid);
			mergesort(mid, last);
			inplace_merge(first, mid, last);
		}
	}
}

#endif