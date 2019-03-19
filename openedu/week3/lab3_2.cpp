#include "edx-io.hpp"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n, m, k;

vector<pair<char, int>> counting_sort(vector<pair<char, int>> &vec) {
	// indices 97 - 122 (26 letters), shift = 97
	auto counts = vector<int>(26, 0);

	// do element counting
	for (auto e : vec) {
		counts[e.first - 'a']++;
	}

	// calculate prepending elements count for each element
	for (int i = 1; i < counts.size(); i++) {
		counts[i] += counts[i - 1];
	}

	// assembling sorted array
	vector<pair<char, int>> result(vec.size());
	for (int i = vec.size() - 1; i >= 0; i--) {
		int result_position = --counts[vec[i].first - 'a'];
		result[result_position] = vec[i];
	}

	return result;
}

int main() {
	// read main input values 
	io >> n >> m >> k;
	
	// read and store all m input strings in memory because they're in invalid order!
	auto read_chars = vector<string>(m);
	for (auto &str: read_chars) {
		// read n chars - i-th chars of n strings
		io >> str;
	}
	
	// will be sorted vector of pairs: strings' ith characters (i = 0..m-1) and their initial indices
	auto sorted = vector<pair<char, int>>(n);

	for (int i = 0; i < n; i++) {
		// '-' is temporary: will be replaced by real char from input
		sorted[i] = make_pair('-', i);
	}

	// i - radix sort phase
	for (int i = 0; i < k; i++) {
		// put read chars in appropriate order to "sorted" vec
		for (int j = 0; j < n; j++) {
			sorted[j].first = read_chars.back()[sorted[j].second];
		}
		read_chars.pop_back();

		// stable counting sort by i-th chars
		sorted = counting_sort(sorted);
	}

	// print order that we've got
	for (auto p : sorted) {
		io << p.second + 1 << ' ';
	}

	return 0;
}
