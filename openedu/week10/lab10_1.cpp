#include "edx-io.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <assert.h>

using namespace std;

int main() {
	string s;
	io >> s;

	auto p = vector<int>(s.size());

	int j = 0;
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == s[j]) {
			p[i] = ++j;
		} else if (j == 0) {
			p[i] = 0;
		} else {
			j = p[j - 1];
			i--;
		}
	}

	for (auto e : p) io << e << " ";
	return 0;
}
