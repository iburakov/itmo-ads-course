#include "edx-io.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <list>
#include <assert.h>
#include <tuple>

using namespace std;
typedef unsigned long long ull;

int group_repeats(string s, int cz) {
	// determine group length
	int l = 2;
	while (s.substr(l*cz, cz) == s.substr(0, cz)) l++;
	return l;
}

tuple<int, int> calc_z_func(string s, vector<int> &z) {
	z[0] = 0;
	int l = 0, r = 0;
	int maxz = 0;
	int maxl = 0;
	int cz = 0;
	int i;
	
	auto check_candidate = [&i, s, &maxz, &maxl](int candz) {
		if (candz == i && candz > maxz) {
			// got new candidate - new max z-prefix
			int l = group_repeats(s, candz);

			// HOW TO OPTIMIZE ???
			if (l >= maxl) {
				// new candidate is better
				maxz = candz;
				maxl = l;
			}
		}
	};

	auto grab_chars_while_can = [&i, &l, &r, &z, check_candidate, s](int j = 0) {
		while (i + j < s.size() && s[i + j] == s[j]) {
			j++;
			check_candidate(j);
		}
		// updating z-block
		l = i;
		r = i + j;
		// saving result
		z[i] = j;
	};

	for (i = 1; i < s.size(); i++) {
		if (i >= r) {
			// manually comparing
			grab_chars_while_can();
		} else {
			// we're inside z-block
			if (z[i - l] < r - i) {
				// our entire known prefix fits inside z-block, so we've already compared it
				z[i] = z[i - l];
			} else {
				// known prefix outranges z-block, so we get more symbols to manually compare
				grab_chars_while_can(r - i);
			}
		}
		check_candidate(z[i]);
	}
	return make_tuple(maxz, maxl);
}

string get_group_mult_str(pair<string, int> g) {
	stringstream result;
	result << g.first;
	if (g.second != 1) {
		result << "*" << g.second;
	}
	return result.str();
}

string get_group_plain_str(pair<string, int> g) {
	stringstream result;
	while (g.second--) result << g.first;
	return result.str();
}

int main() {
	string s;
	io >> s;

	vector<int> z(s.size());
	vector<pair<string, int>> groups;


	int l = 0, r = 0;
	for (int i = 0; i < s.size();) {
		string ss = s.substr(i);
		int maxz, maxl;
		tie(maxz, maxl) = calc_z_func(ss, z);
		if (maxz) {
			groups.push_back(make_pair(ss.substr(0, maxz), maxl));
		} else {
			groups.push_back(make_pair(ss.substr(0, 1), 1));
			i++;
		}
		i += maxz * maxl;
	}

	// print groups
	bool plain = true;
	for (int i = 0; i < groups.size(); i++) {
		auto g = groups[i];

		if (!plain) {
			io << "+";
		}

		string mult = get_group_mult_str(g);
		if (mult.size() < g.first.size() * g.second) {
			if (i && plain) io << "+";
			io << mult;
			plain = false;
		} else {
			string plainstr = get_group_plain_str(g);
			io << plainstr;
			plain = true;
		}
	}
	return 0;
}
