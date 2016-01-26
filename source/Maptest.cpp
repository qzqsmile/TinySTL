#include"stl_maptest.h"
#include"stl_map.h"
#include"pair.h"
#include<iostream>
#include<cassert>
#include<string>
#include<utility>
#include<map>

using std::string;
using std::cout;
using std::endl;

namespace maptest{
	void maptest()
	{
		map<string, int> simap;
		simap[string("jjhou")] = 1;
		simap[string("jerry")] = 2;
		simap[string("jason")] = 3;
		simap[string("jimmy")] = 4;
		
		pair<string, int> value(string("david"), 5);
		simap.insert(value);

		map<string, int>::iterator simap_iter = simap.begin();
		assert(simap[string("jjhou")] == 1);
		map<string, int>::iterator ite1;
		ite1 = simap.find(string("mchen"));
		assert(ite1 == simap.end());
		ite1 = simap.find(string("jerry"));
		assert(ite1 != simap.end());
		assert((*ite1).second == 2);
		cout <<"Map test success!"<< endl;
	}

	void multimaptest()
	{
		multimap<string, int> simap;
		
		pair<string, int> value(string("david"), 5);
		simap.insert(value);
		simap.insert(value);

		map<string, int>::iterator simap_iter = simap.begin();
		assert((*simap_iter).second == 5);
		assert(simap.size() == 2);
		cout <<"Multimap test success!"<< endl;
	}
}