#include "edx-io.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <list>

using namespace std;

#define HASHTABLE_SIZE 800000

struct Entry {
	string key;
	string val;
	list<Entry*>::iterator orderlink;

	Entry(string newkey, string newval) {
		key = newkey;
		val = newval;
	}
};

void main() {
	int n;
	io >> n;

	auto hashmap = new list<Entry>[HASHTABLE_SIZE];
	auto orderlist = list<Entry*>();
	
	for (int i = 0; i < n; i++) {
		string cmd, key, val;
		io >> cmd >> key;

		auto &list = hashmap[hash<string>{}(key) % HASHTABLE_SIZE];
		auto result = find_if(list.begin(), list.end(), [key](const Entry& e) {return e.key == key; });

		if (cmd == "put") {
			io >> val;

			if (result == list.end()) {
				list.push_front(Entry(key, val));
				orderlist.push_front(&list.front());
				list.front().orderlink = orderlist.begin();
			} else {
				result->val = val;
			}
		} else if (cmd == "delete") {
			if (result != list.end()) {
				orderlist.erase(result->orderlink);
				list.erase(result);
			}
		} else if (cmd == "get") {
			io << (result != list.end() ? result->val : "<none>") << "\n";
		} else if (cmd == "next") {
			io << ((result != list.end() && result->orderlink != orderlist.begin()) ? (*prev(result->orderlink))->val : "<none>") << "\n";
		} else if (cmd == "prev") {
			io << ((result != list.end() && next(result->orderlink) != orderlist.end()) ? (*next(result->orderlink))->val : "<none>") << "\n";
		}
	}
}
