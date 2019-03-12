#include "edx-io.hpp"
#include <vector>

using namespace std;

void swap(vector<int> &arr, int a, int b) {
	int t = arr[a];
	arr[a] = arr[b];
	arr[b] = t;
}

int main() {
	// read N
	int n;
	io >> n;

	// read input array
	auto arr = vector<int>(n);
	for (int i = 0; i < n; i++) {
		arr[i] = i + 1;
	}

	// generate array
	for (int i = 2; i < n; i++) {
		swap(arr, i, i / 2);
	}

	// print arr
	//reverse(arr.begin(), arr.end());
	for (auto e : arr) {
		io << e << " ";
	}

	return 0;
}
