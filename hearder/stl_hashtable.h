#ifndef STL_HASHTABLE_H
#define STL_HASHTABLE_H

#include"algorithm.h"
#include"stl_alloc.h"
#include"vector.h"
#include"stl_function.h"
#include"stl_hash_fun.h"

template <class Value, class Key, class HashFcn,
class ExtractKey, class EqualKey, class Alloc = alloc>
class hashtable;

template <class Value, class Key, class HashFcn,
class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator;

template <class Value, class Key, class HashFcn,
class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_const_iterator;

template <class Value, class Key, class HashFcn,
class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator;

template<class Value>
struct __hashtable_node
{
	__hashtable_node* next;
	Value val;
};

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator{
	typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
	typedef __hashtable_iterator<Value, Key, HashFcn,ExtractKey, EqualKey, Alloc> iterator;
	typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
	typedef __hashtable_node<Value> node;

	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;

	node* cur;
	hashtable* ht;

	__hashtable_iterator(node *n, hashtable* tab):cur(n), ht(tab){}
	__hashtable_iterator(){}
	reference operator*() const {return cur->val;}
	pointer operator->() const {return &(operator*());}
	iterator& operator++();
	iterator operator++(int);

	bool operator==(const iterator& it) const {return cur == it.cur;}
	bool operator!=(const iterator& it) const {return cur != it.cur;}
};

template <class Value, class Key, class HashFcn,
class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_const_iterator
{
	typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>
		hashtable;
	typedef __hashtable_iterator<Value, Key, HashFcn,
		ExtractKey, EqualKey, Alloc>
		iterator;
	typedef __hashtable_const_iterator<Value, Key, HashFcn,
		ExtractKey, EqualKey, Alloc>
		const_iterator;
	typedef __hashtable_node<Value> node;

	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef const Value& reference;
	typedef const Value* pointer;

	const node* cur;
	const hashtable* ht;

	__hashtable_const_iterator(const node* n, const hashtable* tab)
		: cur(n), ht(tab) {}
	__hashtable_const_iterator() {}
	__hashtable_const_iterator(const iterator& it) : cur(it.cur), ht(it.ht) {}
	reference operator*() const { return cur->val; }
	pointer operator->() const { return &(operator*()); }
	const_iterator& operator++();
	const_iterator operator++(int);
	bool operator==(const const_iterator& it) const { return cur == it.cur; }
	bool operator!=(const const_iterator& it) const { return cur != it.cur; }
};

template <class V, class K, class HF, class ExK, class EqK, class A>
__hashtable_const_iterator<V, K, HF, ExK, EqK, A>&
	__hashtable_const_iterator<V, K, HF, ExK, EqK, A>::operator++()
{
	const node* old = cur;
	cur = cur->next;
	if (!cur) {
		size_type bucket = ht->bkt_num(old->val);
		while (!cur && ++bucket < ht->buckets.size())
			cur = ht->buckets[bucket];
	}
	return *this;
}

template <class V, class K, class HF, class ExK, class EqK, class A>
inline __hashtable_const_iterator<V, K, HF, ExK, EqK, A>
	__hashtable_const_iterator<V, K, HF, ExK, EqK, A>::operator++(int)
{
	const_iterator tmp = *this;
	++*this;
	return tmp;
}

template <class V, class K, class HF, class ExK, class EqK, class A>
__hashtable_iterator<V, K, HF, ExK, EqK, A>& __hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++()
{
	const node* old = cur;
	cur = cur->next;
	if(!cur){
		size_type bucket = ht->bkt_num(old->val);
		while(!cur && ++bucket < ht->buckets.size())
			cur = ht->buckets[bucket];
	}
	return *this;
}

template<class V, class K, class HF, class ExK, class EqK, class A>
inline __hashtable_iterator<V, K, HF, ExK, EqK, A>
	__hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++(int)
{
	iterator tmp = *this;
	++*this;
	return tmp;
}

template<class Value, class Key, class HashFcn,
class ExtractKey, class EqualKey, class Alloc>
class hashtable{
public:
	typedef HashFcn hasher;
	typedef Value value_type;
	typedef EqualKey key_equal;
	typedef size_t size_type;
	typedef Key key_type;
	typedef ptrdiff_t difference_type;
	typedef Value& reference;
	typedef Value* pointer;
	typedef const value_type* const_pointer;
	typedef const value_type& const_reference;

private:
	hasher hash;
	key_equal equals;
	ExtractKey get_key;

	typedef __hashtable_node<Value> node;
	typedef simple_alloc<node, Alloc> node_allocator;

	size_type num_elements;

public:
	vector<node*, Alloc>buckets;
	typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
	typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
	size_type size() const { return num_elements; }
	size_type bucket_count() const {return buckets.size();}
	reference find_or_insert(const value_type& obj);
	size_type max_bucket_count() const{
		return __stl_prime_list[__stl_num_primes-1];
	}

	typedef simple_alloc<node, Alloc>node_allocator;

	iterator begin()
	{
		for (size_type n = 0; n < buckets.size(); ++n)
			if (buckets[n])
				return iterator(buckets[n], this);
		return end();
	}

	iterator end() { return iterator(0, this); }

	const_iterator begin() const
	{
		for (size_type n = 0; n < buckets.size(); ++n)
			if (buckets[n])
				return const_iterator(buckets[n], this);
		return end();
	}

	const_iterator end() const { return const_iterator(0, this); }

	node *new_node(const value_type& obj)
	{
		node* n = node_allocator::allocate();
		n->next = 0;
		__STL_TRY{
			construct(&n->val, obj);
			return n;
		}
		__STL_UNWIND(node_allocator::deallocate(n));
	}

	void delete_node(node *n)
	{
		destroy(&n->val);
		node_allocator::deallocate(n);
	}

	hashtable(size_type n, const HashFcn& hf, const EqualKey& eql)
		:hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0)
	{
		initialize_buckets(n);
	}


	iterator insert_equal(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_equal_noresize(obj);
	}

	pair<iterator, bool> insert_unique(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_unique_noresize(obj);
	}

private:
	size_type next_size(size_type n) const { return __stl_next_prime(n); }

	void initialize_buckets(size_type n)
	{
		const size_type n_buckets = next_size(n);
		buckets.reserve(n_buckets);
		buckets.insert(buckets.end(), n_buckets, (node*) 0);
		num_elements = 0;
	}

public:
	pair<iterator, iterator> equal_range(const key_type& key);
	pair<const_iterator, const_iterator> equal_range(const key_type& key) const;
	iterator find(const key_type& key)
	{
		size_type n = bkt_num_key(key);
		node* first;
		for ( first = buckets[n];
			first && !equals(get_key(first->val), key);
			first = first->next)
		{}
		return iterator(first, this);
	}

	size_type count(const key_type& key) const
	{
		const size_type n = bkt_num_key(key);
		size_type result = 0;

		for (const node* cur = buckets[n]; cur; cur = cur->next)
			if (equals(get_key(cur->val), key))
				++result;
		return result;
	}

	size_type bkt_num(const value_type& obj, size_type n) const
	{
		return bkt_num_key(get_key(obj), n);
	}

	size_type bkt_num(const value_type& obj) const
	{
		return bkt_num_key(get_key(obj));
	}

	size_type bkt_num_key(const key_type& key) const
	{
		return bkt_num_key(key, buckets.size());
	}

	size_type bkt_num_key(const key_type& key, size_t n) const
	{
		return hash(key) % n;
	}
public:
	void clear();
	void copy_from(const hashtable& ht);
	void resize(size_type num_elements_hint);
	pair<iterator, bool> insert_unique_noresize(const value_type& obj);
	iterator insert_equal_noresize(const value_type& obj);
};


  template <class V, class K, class HF, class Ex, class Eq, class A>
  pair<typename hashtable<V, K, HF, Ex, Eq, A>::iterator,
       typename hashtable<V, K, HF, Ex, Eq, A>::iterator>
  hashtable<V, K, HF, Ex, Eq, A>::equal_range(const key_type& key)
  {
    typedef pair<iterator, iterator> pii;
    const size_type n = bkt_num_key(key);
  
    for (node* first = buckets[n]; first; first = first->next) {
      if (equals(get_key(first->val), key)) {
        for (node* cur = first->next; cur; cur = cur->next)
          if (!equals(get_key(cur->val), key))
            return pii(iterator(first, this), iterator(cur, this));
        for (size_type m = n + 1; m < buckets.size(); ++m)
          if (buckets[m])
            return pii(iterator(first, this),
                       iterator(buckets[m], this));
        return pii(iterator(first, this), end());
      }
    }
    return pii(end(), end());
  }
  
  template <class V, class K, class HF, class Ex, class Eq, class A>
  pair<typename hashtable<V, K, HF, Ex, Eq, A>::const_iterator,
       typename hashtable<V, K, HF, Ex, Eq, A>::const_iterator>
  hashtable<V, K, HF, Ex, Eq, A>::equal_range(const key_type& key) const
  {
    typedef pair<const_iterator, const_iterator> pii;
    const size_type n = bkt_num_key(key);
  
    for (const node* first = buckets[n] ; first; first = first->next) {
      if (equals(get_key(first->val), key)) {
        for (const node* cur = first->next; cur; cur = cur->next)
          if (!equals(get_key(cur->val), key))
            return pii(const_iterator(first, this),
                       const_iterator(cur, this));
        for (size_type m = n + 1; m < buckets.size(); ++m)
          if (buckets[m])
            return pii(const_iterator(first, this),
                       const_iterator(buckets[m], this));
        return pii(const_iterator(first, this), end());
      }
    }
    return pii(end(), end());
  }

template<class V, class K, class HF, class Ex, class Eq, class A>
void hashtable<V, K, HF, Ex, Eq, A>::clear()
{
	for(size_type  i = 0; i < buckets.size(); i++){
		node* cur = bucktes[i];
		while(cur != 0){
			node* next = cur->next;
			delete_node(cur);
			cur = next;
		}
		buckets[i] = 0;
	}
	num_elements = 0;
}

template<class V, class K, class HF, class Ex, class Eq, class A>
void hashtable<V, K, HF, Ex, Eq, A>::copy_from(const hashtable& ht)
{
	buckets.clear();
	buckets.reserve(ht.buckets.size());
	buckets.insert(buckets.end(), ht.buckets.size(), (node*) 0);

	//		__STL_TRY{
	for(size_type i = 0; i < ht.buckets.size(); ++i){
		if(const node * cur = ht.buckets[i]){
			node* copy = new_node(next->val);
			copy = copy->next;
			//				}
		}
	}
	num_elements = ht.num_elements;
}

template<class V, class K, class HF, class Ex, class Eq, class A>
void hashtable<V, K, HF, Ex, Eq, A>::resize(size_type num_elements_hint)
{
	const size_type old_n = buckets.size();
	if(num_elements_hint > old_n){
		const size_type n = next_size(num_elements_hint);
		if(n > old_n){
			vector<node*, A>tmp(n, (node*)0);
			//			__STL_TRY{
			for(size_type bucket = 0; bucket < old_n; ++bucket){
				node* first = buckets[bucket];
				while(first){
					size_type new_bucket = bkt_num(first->val , n);
					buckets[bucket] = first->next;
					first->next = tmp[new_bucket];
					tmp[new_bucket] = first;
					first = buckets[bucket];
				}
				buckets.swap(tmp);
			}
			//			}
		}
	}
}

template<class V, class K, class HF, class Ex, class Eq, class A>
pair<typename hashtable<V,K,HF, Ex, Eq, A>::iterator, bool>
	hashtable<V, K, HF, Ex, Eq, A>::insert_unique_noresize(const value_type& obj)
{
	const size_type n = bkt_num(obj);
	node *first = buckets[n];

	for(node* cur = first; cur; cur = cur->next)
		if(equals(get_key(cur->val), get_key(obj)))
			return pair<iterator, bool>(iterator(cur, this), false);

	node* tmp = new_node(obj);
	tmp->next = first;
	buckets[n] = tmp;
	++num_elements;
	return pair<iterator, bool>(iterator(tmp, this), true);
}

  template <class V, class K, class HF, class Ex, class Eq, class A>
  typename hashtable<V, K, HF, Ex, Eq, A>::reference
  hashtable<V, K, HF, Ex, Eq, A>::find_or_insert(const value_type& obj)
  {
    resize(num_elements + 1);
  
    size_type n = bkt_num(obj);
    node* first = buckets[n];
  
    for (node* cur = first; cur; cur = cur->next)
      if (equals(get_key(cur->val), get_key(obj)))
        return cur->val;
  
    node* tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return tmp->val;
  }

template<class V, class K, class HF, class Ex, class Eq, class A>
typename hashtable<V, K, HF, Ex, Eq, A>::iterator
	hashtable<V, K, HF, Ex, Eq, A>::insert_equal_noresize(const value_type& obj)
{
	const size_type n = bkt_num(obj);
	node *first = buckets[n];

	for(node *cur = first; cur; cur = cur->next)
		if(equals(get_key(cur->val), get_key(obj))){
			node* tmp = new_node(obj);
			tmp->next = cur->next;
			cur->next =tmp;
			++num_elements;
			return iterator(tmp, this);
		}	

		node *tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return iterator(tmp, this);
}

static const int __stl_num_primes = 28;

static const unsigned long __stl_prime_list[__stl_num_primes] =
{
	53, 97, 193, 389, 769,
	1543, 3079, 6151, 12289, 24593,
	49157, 98317, 196613, 393241, 786433,
	1572869, 3145739, 6291469, 12582917, 25165843,
	50331653, 100663319, 201326611, 402653189, 805306457,
	1610612741, 3221225473ul, 4294967291ul
};

inline unsigned long __stl_next_prime(unsigned long n)
{
	const unsigned long *first = __stl_prime_list;
	const unsigned long *last = __stl_prime_list + __stl_num_primes;
	const unsigned long *pos = mystl::lower_bound(first, last, n);

	return pos == last ? *(last-1) : *pos;
}

#endif