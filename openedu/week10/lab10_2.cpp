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

int main() {
	string s;
	io >> s;

	vector<int> z(1000000);

	int l = 0, r = 0;

	for (int i = 1; i < s.size(); i++) {
		if (i >= r) {
			// manually comparing
			int j = 0;
			while (i + j < s.size() && s[i + j] == s[j]) j++;
			// updating z-block
			l = i;
			r = i + j;
			// saving result
			z[i] = j;
		} else {
			// we're inside z-block
			if (z[i - l] < r - i) {
				// our entire known prefix fits inside z-block, so we've already compared it
				z[i] = z[i - l];
			} else {
				// known prefix outranges z-block, so we get more symbols to manually compare
				int j = r - i;
				while (i + j < s.size() && s[i + j] == s[j]) j++;
				l = i;
				r = j + i;
				z[i] = j;
			}
		}
	}

	for (int i = 1; i < s.size(); i++) {
		io << z[i] << " ";
	}
	return 0;
}
