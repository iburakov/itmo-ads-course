#include "edx-io.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <forward_list>

using namespace std;

#define HASHTABLE_SIZE 800000

typedef unsigned long long ull;

auto HASHMAP = new vector<ull>[HASHTABLE_SIZE];

ull h(ull x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x % HASHTABLE_SIZE;
}

bool add_if_not_in_hashmap(ull x) {
	auto& list = HASHMAP[h(x)];
	if (find(list.begin(), list.end(), x) != list.end()) {
		// already found
		return false;
	} else {
		list.push_back(x);
		return true;
	}
}

#define E3 1000
#define E15 1000000000000000

void main() {
	long long N, X, A, B, Ac, Bc, Ad, Bd;
	io >> N >> X >> A >> B >> Ac >> Bc >> Ad >> Bd;
	

	for (int i = 0; i < N; i++) {
		if (add_if_not_in_hashmap(X)) {
			A = (A + Ad) % E3;
			B = (B + Bd) % E15;
		} else {
			A = (A + Ac) % E3;
			B = (B + Bc) % E15;
		}

		X = (X * A + B) % E15;
	}
	io << X << " " << A << " " << B << "\n";
}
