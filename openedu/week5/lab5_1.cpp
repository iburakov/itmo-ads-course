#include "edx-io.hpp"
#include <vector>
#include <string>

using namespace std;

int main() {
	int n;
	io >> n;

	vector<int> arr(n);
	for (auto& v : arr) io >> v;

	bool result = true;
	for (int i = 1; i <= n / 2; i++) {
		if (arr[i - 1] > arr[2*i - 1]) {
			result = false;
			break;
		} else if (2 * i + 1 <= n && arr[i - 1] > arr[(2 * i + 1) - 1]) {
			result = false;
			break;
		}
	}

	io << ((result) ? "YES" : "NO");
	return 0;
}
