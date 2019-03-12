#include "edx-io.hpp"
#include <vector>
#include <algorithm>

using namespace std;

int n, k;

void sort_k_slice(vector<long long> &arr, int start) {
	auto slice = vector<long long>();
	slice.reserve(n / k);
	
	// extract a slice
	for (int i = start; i < n; i += k) {
		slice.push_back(arr[i]);
	}

	sort(slice.begin(), slice.end());

	// put it back
	for (int i = 0; i < slice.size(); i++) {
		arr[start + i * k] = slice[i];
	}
}

int main() {
	// read input
	io >> n >> k;

	// EDGE CASES
	// if step is 1, ANY array can be sorted 
	// if n is 1, array is sorted by definition
	if (k == 1 || n == 1) {
		io << "YES";
		return 0;
	}
	
	// initializing array with input
	auto arr = vector<long long>(n);
	for (int i = 0; i < n; i++) {
		io >> arr[i];
	}

	// SEPARATELY sort slices of corresponding k (in pythonic terms - [i::k])
	for (int i = 0; i < k; i++) {
		sort_k_slice(arr, i);
	}

	// check if array is sorted.
	// if it's not, then it's impossible.
	bool is_pugalo_crying = false;
	for (int i = 1; i < n; i++) {
		if (arr[i] < arr[i - 1]) {
			is_pugalo_crying = true;
			break;
		}
	}

	// print needed part
	io << (is_pugalo_crying ? "NO" : "YES");

	return 0;
}
