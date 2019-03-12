#include "edx-io.hpp"
#include <vector>

using namespace std;

void merge_sort(vector<int> &arr, int left, int right) {
	// left subarray index in inclusive
	// right subarray index is exclusive (!)

	// length of the subarray to sort
	int subarray_n = right - left;

	if (subarray_n == 1) {
		// already sorted, job done
		return;
	}

	// beginning of left and right subarrays
	int left_beginning = left;
	int right_beginning = left + subarray_n / 2;

	// recursively sort subarrays
	merge_sort(arr, left_beginning, right_beginning);
	merge_sort(arr, right_beginning, right);

	// merge sorted subarrays
	auto merged_arr = vector<int>(subarray_n);
	int i = left_beginning;
	int j = right_beginning;
	for (int k = 0; k < subarray_n;) {
		if (j == right || (i != right_beginning && arr[i] < arr[j])) {
			// left subarray wins for current k
			merged_arr[k++] = arr[i++];
		} else {
			// right subarray wins for current k
			merged_arr[k++] = arr[j++];
		}
	}

	// place merged_arr 
	copy_n(merged_arr.begin(), subarray_n, arr.begin() + left);
	
	// print required info
	// (right - 1) -- inclusive
	// (right - 1) + 1 -- indexing from 1
	io << left + 1 << " " << right << " " << merged_arr.front() << " " << merged_arr.back() << "\n";
}

int main() {
	// read N
	int n;
	io >> n;

	// read input array
	auto arr = vector<int>(n);
	for (auto &e : arr) {
		io >> e;
	}

	// sorting 
	merge_sort(arr, 0, n);

	// printing sorted array
	for (auto e : arr) {
		io << e << " ";
	}
	return 0;
}
