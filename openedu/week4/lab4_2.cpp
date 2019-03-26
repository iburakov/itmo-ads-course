#include "edx-io.hpp"

using namespace std;

#define SIZE 1000000
#define CYCLE_INC(v, sz) (((v) + 1 ) % (sz))

int main() {
	auto queue = new int[SIZE];
	int head = 0, tail = 0;
	
	int n;
	io >> n;

	for (int i = 0; i < n; i++) {
		// read command
		char c;
		io >> c;

		if (c == '+') {
			// push
			io >> queue[tail];
			tail = CYCLE_INC(tail, SIZE);
		} else {
			// pop
			io << queue[head] << '\n';
			head = CYCLE_INC(head, SIZE);
		}
	}

	return 0;
}
