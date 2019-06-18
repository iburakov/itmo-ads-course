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

int main() {
#ifdef  _DEBUG
	ofstream cout("output.txt");
#endif //  _DEBUG

	int n;
	cin >> n;

	// minimal last elements of LIS of length i
	vector<int> t(n);
	t[0] = 0;

	// where we came from when were setting t[i]
	vector<int> r(n, -1);

	// LIS length
	int ml = 0;

	// input sequence
	vector<int> a(n);

	auto find_ceiling_in_t = [&a, &t, &ml](int x) {
		int l = 0;
		int r = ml;
		while (l <= r) {
			int p = (l + r) / 2;
			if (a[t[p]] >= x && x >= a[t[p + 1]]) {
				while (a[t[p + 1]] == x) p++;
				return p + 1;
			} else if (x <= a[t[p]]) {
				l = p + 1;
			} else {
				r = p - 1;
			}
		}

		assert(false);
	};
	
	cin >> a[0];
	for (int i = 1; i < n; i++) {
		cin >> a[i];
		if (a[i] > a[t[0]]) {
			// a[i] is min last elem of LIS of len 1 (stored at t[0])
			t[0] = i;
			// leaving - 1 in r as this should be the end of a sequence
		} else if (a[i] <= a[t[ml]]) {
			// a[i] is not less than min last elem of curring - edge LIS
			// append it as a LIS of length(ml + 1) to T
			ml += 1;
			t[ml] = i;
			// save where we came from
			r[i] = t[ml - 1];
		} else {
			// binary search to find a ceiling of a[i] to put it there
			int ci = find_ceiling_in_t(a[i]);
			// update t, save new minimum
			t[ci] = i;
			// save where we came from
			r[t[ci]] = t[ci - 1];
		}
	}

	cout << ml + 1 << "\n";

	// reassemble sequence backwards
	vector<int> result(ml + 1);
	int ci = t[ml];
	while (ci != -1) {
		result[ml--] = ci + 1;
		ci = r[ci];
	}
	for (auto e : result) cout << e << " ";
	return 0;
}
