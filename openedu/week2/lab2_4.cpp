#include "edx-io.hpp"
#include <vector>

using namespace std;

int k1, k2;

int hoare_patrition(vector<int> &arr, int left, int right) {
	int pivot = arr[(left + right) / 2];
	int i = left - 1;
	int j = right + 1;
	while (true) {
		do i++; while (arr[i] < pivot);
		do j--; while (arr[j] > pivot);

		if (i >= j) {
			return j;
		}

		int t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
	}
}

void quick_sort(vector<int> &arr, int left, int right) {
	// if we don't need to sort that subarray, skip it!
	if (right < k1 || left > k2) return;

	if (left < right) {
		int middle = hoare_patrition(arr, left, right);
		quick_sort(arr, left, middle);
		quick_sort(arr, middle + 1, right);
	}
}

int main() {
	// read input
	int n, A, B, C;
	io >> n >> k1 >> k2;
	k1--;
	k2--;

	auto arr = vector<int>(n);
	io>> A >> B >> C >> arr[0] >> arr[1];

	for (int i = 2; i < n; i++) {
		arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
	}

	// sort array
	quick_sort(arr, 0, n - 1);

	// print needed part
	for (int i = k1; i <= k2; i++) {
		io << arr[i]<< " ";
	}

	return 0;
}
