#include "edx-io.hpp"

using namespace std;

int main() {
	auto stack = new int[1e6];
	
	int n;
	io >> n;

	for (int i = 0; i < n; i++) {
		// read command
		char c;
		io >> c;

		if (c == '+') {
			// push
			io >> *(stack++);
		} else {
			// pop
			io << *(--stack) << '\n';
		}
	}

	return 0;
}
