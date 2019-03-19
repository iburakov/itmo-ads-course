#include "edx-io.hpp"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n, m;

# define KTH_BYTE(k, val) ((val) >> 8 * k) & 0xFF

int main() {
	// read array sizes
	io >> n >> m;

	// read arrays
	auto a = vector<int>(n);
	auto b = vector<int>(m);
	for (auto &e : a) io >> e;
	for (auto &e : b) io >> e;

	// compose array to sort
	// STL vectors result in TLE! how's that possible
	auto c = new int[n * m];
	
	int max_val = 0;
	int next;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++) {
			next = a[i] * b[j];
			c[i*m + j] = next;

			if (next > max_val) {
				max_val = next;
			}
		}
	}

	// i - radix sort phase
	auto result = new int[n * m];
	auto counts = new int[256];
	for (int byte_n = 0; (1LL << (byte_n * 8)) <= max_val; byte_n++) {
		memset(counts, 0, 256 * sizeof(int));

		// do element counting
		for (int i = 0; i < n * m; i++) {
			counts[KTH_BYTE(byte_n, c[i])]++;
		}

		// calculate prepending elements count for each element
		for (int i = 1; i < 256; i++) {
			counts[i] += counts[i - 1];
		}

		// assembling sorted array
		for (int i = n * m - 1; i >= 0; i--) {
			// calculate result position and set c[i] to it
			result[--counts[KTH_BYTE(byte_n, c[i])]] = c[i];
		}

		memcpy(c, result, sizeof(int) * n * m);
	}

	// print order that we've got
	long long sum = 0;
	for (int i = 0; i < n * m; i += 10) {
		sum += c[i];
	}

	io << sum;
	return 0;
}
