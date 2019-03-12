#include "edx-io.hpp"
#include <vector>

using namespace std;

long long count_inversions(vector<int> &arr, int left, int right) {
	// left subarray index in inclusive
	// right subarray index is exclusive (!)

	// length of the subarray to sort
	int subarray_n = right - left;

	if (subarray_n == 1) {
		// already sorted, job done
		return 0;
	}

	// beginning of left and right subarrays
	int left_beginning = left;
	int right_beginning = left + subarray_n / 2;

	// recursively sort subarrays
	long long result = 0;
	result += count_inversions(arr, left_beginning, right_beginning);
	result += count_inversions(arr, right_beginning, right);

	// merge sorted subarrays
	auto merged_arr = vector<int>(subarray_n);
	int i = left_beginning;
	int j = right_beginning;
	for (int k = 0; k < subarray_n;) {
		if (j == right || (i != right_beginning && arr[i] <= arr[j])) {
			// left subarray wins for current k
			merged_arr[k++] = arr[i++];
		} else {
			// right subarray wins for current k
			merged_arr[k++] = arr[j++];
			// Since right subarray won, all left subarray elements larger than the element from
			// right subarray will form an inversion. Add their quantity to result.
			result += right_beginning - i;
		}
	}

	// place merged_arr 
	copy_n(merged_arr.begin(), subarray_n, arr.begin() + left);

	return result;
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
	io << count_inversions(arr, 0, n);

	return 0;
}
