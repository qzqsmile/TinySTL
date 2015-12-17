#ifndef VECTOR_H
#define VECTOR_H

#include"memory.h"
#include"algorithm.h"

template<class T, class Alloc=alloc>
class vector{
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

protected:
	typedef simple_alloc<value_type, Alloc> data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;
	void insert_aux(iterator position, const T& x);
	void insert_aux(iterator position, size_type n, const T& x);
	void deallocate() {
		if(start)
			data_allocator::deallocate(start, end_of_storage-start);
	}

	void fill_initialize(size_type n, const T& value){
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}

public:
	iterator begin() const {return start;}
	iterator end() const { return finish;}
	size_type size() const { 
		return size_type(end()-begin()); 
	}
	size_type capacity() const {
		return size_type(end_of_storage - begin());
	}
	bool empyt() const{ return begin() == end();}
	reference operator[] (size_type n) { return *(begin() + n);}

	vector() : start(0), finish(0), end_of_storage(0){ }
	vector(size_type n, const T& value){fill_initialize(n, value);}
	vector(int n, const T& value) {fill_initialize(n,value);};
	vector(long n, const T& value){fill_initialize(n, value);}
	explicit vector(size_type n){fill_initialize(n, T());}

	~vector() {
		destroy(start, finish);
		deallocate();
	}
	reference front(){return *begin();}
	reference back() {return *(end()-1);}
	void push_back(const T& x){
		if(finish != end_of_storage){
			construct(finish, x);
			++finish;
		}
		else
			insert_aux(end(), x);
	}

	void pop_back(){
		--finish;
		destory(finish);
	}

	iterator erase(iterator position){
		if(position + 1 != end())
			copy(position +1, finish, position);
		--finish;
		destory(finish);
		return position;
	}

	iterator erase(iterator first, iterator last);

	void resize(size_type new_size, const T& x){
		if(new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - size(), x);
	}

	void resize(size_type new_size) {resizse(new_size, T());}
	void clear(){erase(begin(), end());}

protected:
	iterator allocate_and_fill(size_type n, const T& x){
		iterator result = data_allocator::allocate(n);
		uninitialized_fill_n(result, n, x);
		return result;
	}
};

template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x){
	if(finish != end_of_storage){
		construct(finish, *(finish-1));
		++finish;
		T x_copy = x;
		copy_backward(position, finish - 2, finish-1);
		*position = x_copy;
	}
	else{
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2  * old_size : 1;

		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;
		try{
			new_finish = uninitialized_copy(start, position, new_start);
			construct(new_finish, x);
			++new_finish;
			new_finish = uninitialized_copy(position, finish, new_finish);
		}catch(...){
			destroy(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}

		destroy(begin(), end());
		deallocate();

		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}


template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, size_type n, const T& x)
{
	if(n != 0){
		if(size_type(end_of_storage - finish) >= n){
			T x_copy = x;
			const size_type elems_after = finish-position;
			iterator old_finish = finish;
			if(elems_after > n){
				uninitialized_backward(position, old_finish - n, old_finish);
				fill(position, position+n, x_copy);
			}
		}else{
			uninitialized_fill_n(finish, n - elems_after, x_copy);
			finish += n - elems_after;
			uninitialized_copy(position, old_finish, finish);
			finish += elems_after;
			fill(position, old_finish, x_copy);
		}
	}
	else{
		const size_type old_size = size();
		const size_type len = old_size + max(old_size, n);

		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;

		__STL_TRY{
			new_finish = uninitialized_copy(start, position, new_start);
			new_finish = uninitialized_fill_n(new_finish, n, x);
			new_finish = uninitialized_copy(position, finish, new_finish);
		}
#ifdef __STL_USE_EXCEPTIONS
		catch(...){
			destroy(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}
#endif // __STL_USE_EXCEPTIONS
		destroy(start, finish);
		deallocate();

		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator  
	vector<T, Alloc>::erase(iterator first, iterator last){
	iterator i = copy(last, finish, first);
	destroy(i, finish);
	finish = finish - (last - first);
	return first;
}

#endif