#include "edx-io.hpp"
#include <vector>
#include <string>

using namespace std;

#define MAX_OPS int(1e6)

auto heap = vector<int>();

// arrays for tracking heap elements position by string numbers on which they were added
// need to be able to resolve the link in both directions, so there's two arrays
auto strn_to_loc = new int[1e6 + 1];
auto loc_to_strn = new int[1e6];


#define PARENT(i) (((i) + 1) / 2 - 1)
#define LCHILD(i) (2 * ((i) + 1) - 1)
#define RCHILD(i) (LCHILD(i) + 1)
#define PARENT_EXISTS(i) (i != 0)
#define LCHILD_EXISTS(i) (LCHILD(i) < heap.size())
#define RCHILD_EXISTS(i) (RCHILD(i) < heap.size())

void swap(int a1, int a2) {
	int t = heap[a1];
	heap[a1] = heap[a2];
	heap[a2] = t;

	// do position tracking housekeeping as well
	// update strn2loc resolver (swap corresponding elements gathered by loc2strn)
	int strn1 = loc_to_strn[a1];
	int strn2 = loc_to_strn[a2];

	t = strn_to_loc[strn1];
	strn_to_loc[strn1] = strn_to_loc[strn2];
	strn_to_loc[strn2] = t;

	// update loc2strn resolver (swap based on just a1 and a2 to be in sync with heap)
	t = loc_to_strn[a1];
	loc_to_strn[a1] = loc_to_strn[a2];
	loc_to_strn[a2] = t;
}

void heapify(int root) {
	while (LCHILD_EXISTS(root)) {
		int largest_i = root;

		if (heap[LCHILD(root)] < heap[largest_i]) {
			largest_i = LCHILD(root);
		}

		if (RCHILD_EXISTS(root) && heap[RCHILD(root)] < heap[largest_i]) {
			largest_i = RCHILD(root);
		}

		if (largest_i == root) {
			// done, heap is correct
			break;
		}

		// swap and go deeper
		swap(root, largest_i);
		root = largest_i;
	}
}

void bubble_up(int current) {
	// bubble up until new element isn't violating heap condition
	while (PARENT_EXISTS(current) && heap[PARENT(current)] > heap[current]) {
		swap(PARENT(current), current);
		current = PARENT(current);
	}
}

void add(int val) {
	heap.push_back(val);
	bubble_up(heap.size() - 1);
}

int main() {
	int ops_size;
	io >> ops_size;

	heap.reserve(ops_size);

	for (int strn = 1; strn <= ops_size; strn++) {
		char cmd;

		io >> cmd;
		switch (cmd) {
			case 'A': {
				int val;
				io >> val;

				// register added element to location trackers
				strn_to_loc[strn] = heap.size();
				loc_to_strn[heap.size()] = strn;
				
				add(val);
			} break;
			case 'X': {
				if (empty(heap)) {
					io << "*\n";
				} else {
					io << heap.front() << "\n";
					swap(0, heap.size() - 1);
					heap.pop_back();
					heapify(0);
				}
			} break;
			case 'D': {
				int target_strn, newval;
				io >> target_strn >> newval;

				int target_index = strn_to_loc[target_strn];
				heap[target_index] = newval;
				bubble_up(target_index);
			} break;
		}
	}

	return 0;
}
