#include "edx-io.hpp"
#include <stack>
#include <string>

using namespace std;

char invert_brace(char brace) {
	switch (brace) {
		case ')': return '(';
		case ']': return '[';
	}
}

bool check_braces(string sequence) {
	auto st = stack<char>();
	for (auto c : sequence) {
		if (c == '(' || c == '[') {
			st.push(c);
		} else {
			if (!st.empty() && st.top() == invert_brace(c)) {
				st.pop();
			} else {
				return false;
			}
		}
	}
	return st.size() == 0;
}

int main() {
	auto stack = new int[1e6];
	
	int n;
	io >> n;

	for (int i = 0; i < n; i++) {
		auto sequence = string();
		io >> sequence;

		io << (check_braces(sequence) ? "YES" : "NO") << '\n';
	}

	return 0;
}
