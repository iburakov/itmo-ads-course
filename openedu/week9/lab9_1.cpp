#include "edx-io.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <assert.h>

using namespace std;

void main() {
	string substr, s;
	io >> substr >> s;

	auto result = vector<int>();
	result.reserve(10000);

	for (int i = 0; i <= long long(s.size() - substr.size()); i++) {
		int si = 0;
		while (s[i + si] == substr[si]) {
			si++;
			if (si == substr.size()) {
				result.push_back(i);
				break;
			}
		}
	}

	io << result.size() << "\n";
	for (auto e : result) io << e + 1 << " ";
}
