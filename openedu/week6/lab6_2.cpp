#include "edx-io.hpp"
#include <vector>
#include <string>

using namespace std;

int main() {
	int n;
	double a;
	io >> n >> a;

	// lower and upper boundary
	double lowerb = 0, upperb = a;

	// height of the second lamp
	double h2;

	// last successful result
	double last_result;
	   
	while (upperb - lowerb > 1e-10) {
		// guessing h2
		h2 = (upperb + lowerb) / 2; 

		// calculating lamp heights
		double prev = h2;
		double prevprev = a;
		double cur;
		for (int i = 2; i < n; i++) {
			cur = 2 * prev - prevprev + 2;
			if (cur < 0) {
				// one of the lamps is below zero, invalidating cur, breaking
				cur = NAN;
				break;
			}

			prevprev = prev;
			prev = cur;
		}

		// checking if min height is fine
		if (!isnan(cur)) {
			// still above zero - lowering
			upperb = h2;
			// cur = last lamp's height
			last_result = cur;
		} else {
			// below zero - raising higher
			lowerb = h2;
		}
	}

	io << last_result;
	return 0;
}
