#include"stl_hashtabletest.h"
#include"stl_hash_set.h"
#include"stl_hash_map.h"
#include<iostream>
#include<cassert>

using std::cout;
using std::endl;

namespace hashtabletest{

	struct eqstr
	{
		bool operator()(const char* s1, const char* s2) const
		{
			return strcmp(s1, s2) == 0;
		}
	};

	void hashtabletest()
	{
		hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc> iht(50, hash<int>(), equal_to<int>());
		assert(iht.size() == 0);
		assert(iht.bucket_count() == 53);
		assert(iht.max_bucket_count() == 4294967291);

		iht.insert_unique(59);
		iht.insert_unique(63);
		iht.insert_unique(108);
		iht.insert_unique(2);
		iht.insert_unique(53);
		iht.insert_unique(55);
		assert(iht.size() == 6);

		hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc>::iterator ite = iht.begin();
		assert(*ite == 53);
		ite++;
		assert(*ite == 55);
		ite++;
		assert(*ite == 2);
		ite++;
		assert(*ite == 108);

		for(int i = 0; i <= 47; i++)
			iht.insert_equal(i);
		assert(iht.size() == 54);
		assert(iht.bucket_count() == 97);
		assert(*(iht.find(2)) == 2);
		assert(iht.count(2) == 2);

		cout << "Hashtable test success!"<< endl;
	}

	void hashsettest()
	{
		hash_set<const char*, hash<const char*>, eqstr> Set;
		Set.insert("kiwi");
		Set.insert("plum");
		Set.insert("apple");
		Set.insert("mango");
		Set.insert("apricot");
		Set.insert("banana");

		hash_set<const char*, hash<const char*>, eqstr>::iterator ite1 = Set.begin();
		hash_set<const char*, hash<const char*>, eqstr>::iterator ite2 = Set.end();

		//for(;ite1 != ite2; ++ite1)
		//	cout << *ite1 <<endl;
		//mystl::lookup(Set, "mango");
		cout <<"Hash Set success!"<<endl;
	}


	void hashmaptest()
	{
		hash_map<const char*, int, hash<const char*>, eqstr> days;
		days["jnauary"] = 31;
		days["february"] = 28;
		days["march"] = 31;
		days["april"] = 30;
		days["may"] = 31;
		days["june"] = 30;
		days["july"] = 31;
		days["september"] = 30;
		assert(days["september"]==30);
		hash_map<const char*, int, hash<const char*>, eqstr>::iterator ite1 = days.begin();
		hash_map<const char*, int , hash<const char*>, eqstr>::iterator ite2 = days.end();
		cout << "hash map test success!" <<endl;
	}

	void hash_multisettest()
	{
		hash_multiset<const char*, hash<const char*>, eqstr> Set;
		Set.insert("kiwi");
		Set.insert("plum");
		Set.insert("apple");
		Set.insert("mango");
		Set.insert("apricot");
		Set.insert("banana");

		hash_multiset<const char*, hash<const char*>, eqstr>::iterator ite1 = Set.begin();
		hash_multiset<const char*, hash<const char*>, eqstr>::iterator ite2 = Set.end();

		//for(;ite1 != ite2; ++ite1)
		//	cout << *ite1 <<endl;
		//mystl::lookup(Set, "mango");
		cout <<"Hash multiset success!"<<endl;
	}


	void hash_multimaptest()
	{
		hash_map<const char*, int, hash<const char*>, eqstr> days;
		days["jnauary"] = 31;
		days["february"] = 28;
		days["march"] = 31;
		days["april"] = 30;
		days["may"] = 31;
		days["june"] = 30;
		days["july"] = 31;
		days["september"] = 30;
		assert(days["september"]==30);
		hash_map<const char*, int, hash<const char*>, eqstr>::iterator ite1 = days.begin();
		hash_map<const char*, int , hash<const char*>, eqstr>::iterator ite2 = days.end();
		//for(;ite1 != ite2; ++ite1)
		//	cout << ite1->first<<' ';
		cout <<"hash multimap test success!"<<endl;
	}
}