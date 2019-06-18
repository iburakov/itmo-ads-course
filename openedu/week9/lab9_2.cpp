#include "edx-io.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <list>
#include <assert.h>
#include <tuple>

using namespace std;
typedef unsigned long long ull;

struct CharEntry {
	ull left, right;
	CharEntry(ull left = 0, ull right = 0) : left(left), right(right) {}
};

int main() {
	ifstream fin("input.txt");

	string s;
	char c;
	while (fin >> c) {
		if (c != ' ') {
			s.push_back(c);
		}
	}
	
	// counting chars
	map<char, CharEntry*> right, left;
	for (auto cc : s) {
		auto ce = right.find(cc);
		if (ce != right.end()) {
			ce->second->right++;
		} else {
			right[cc]= new CharEntry(0, 1);
		}
	}
	
	ull output = 0;
	c = s[0];
	auto ce = right[c];
	left[c] = ce;
	ce->left++;
	ce->right--;

	for (auto cc : s.substr(1)) {
		auto ce = right[cc];
		ce->right--;

		for (auto le : left) {
			output += le.second->left * le.second->right;
		}

		ce->left++;
		left[cc] = ce;
	}

	io << output;
	return 0;
}
