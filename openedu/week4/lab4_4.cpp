#include "edx-io.hpp"
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

#define SIZE 1000000
#define CYCLE_INC(v, sz) (((v) + 1 ) % (sz))


int main() {
	auto queue = new int[SIZE];
	int head = 0, tail = 0;
	auto pq = multiset<int>();

	int n;
	io >> n;

	for (int i = 0; i < n; i++) {
		// read command
		char c;
		io >> c;

		if (c == '+') {
			// push
			io >> queue[tail];
			pq.insert(queue[tail]);
			tail = CYCLE_INC(tail, SIZE);
		} else if (c == '-') {
			// pop
			//io << queue[head] << '\n';
			pq.erase(pq.find(queue[head]));
			head = CYCLE_INC(head, SIZE);
		} else {
			io << *pq.begin() << '\n';
		}
	}

	return 0;
}
