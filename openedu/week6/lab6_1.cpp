#include "edx-io.hpp"
#include <vector>
#include <string>

using namespace std;

int n;
vector<int> vec;

pair<int, int> bsearch(int e) {
	int l = -1,
		r = n - 1;
	
	while (r != l + 1) {
		int midi = (r + l) / 2;
		if (vec[midi] < e) {
			l = midi;
		} else {
			r = midi;
		}
	}

	if (vec[r] != e) {
		// +1 will be done later
		return make_pair(-2, -2);
	}

	int leftb = r;
	l = -1,
	r = n;

	while (r != l + 1) {
		int midi = (r + l) / 2;
		if (vec[midi] <= e) {
			l = midi;
		} else {
			r = midi;
		}
	}

	int rightb = l;

	return make_pair(leftb, rightb);
}

int main() {
	io >> n;
	vec = vector<int>(n);
	for (auto &e : vec) io >> e;

	int m;
	io >> m;
	for (int i = 0; i < m; i++) {
		int e;
		io >> e;
		auto result = bsearch(e);
		io << result.first + 1 << " " << result.second + 1 << "\n";
	}

	return 0;
}
