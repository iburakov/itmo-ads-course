#include "edx-io.hpp"
#include <vector>
#include <algorithm>
#include <forward_list>

using namespace std;

#define HASHTABLE_SIZE 909151

unsigned int h(long long x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x % HASHTABLE_SIZE;
}

int main() {
	int n;
	io >> n;

	auto hashmap = new forward_list<long long>[HASHTABLE_SIZE];

	for (int i = 0; i < n; i++) {
		char c;
		long long arg;
		io >> c >> arg;
		switch (c) {
			case 'A': {
				hashmap[h(arg)].remove(arg);
				hashmap[h(arg)].push_front(arg);
			} break;
			case 'D': {
				hashmap[h(arg)].remove(arg);
			} break;
			case '?': {
				auto list = hashmap[h(arg)];
				io << (find(list.begin(), list.end(), arg) != list.end() ? "Y" : "N") << "\n";
			} break;
		}
	}
	
	return 0;
}
