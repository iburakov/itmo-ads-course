#include <fstream>
using namespace std;

int main() {
	short n;
	float* incomes = new float[10000]; 
	int* ids = new int[10000];
	
	ifstream cin;
	cin.open("input.txt");
	
	ofstream cout;
	cout.open("output.txt");

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> incomes[i];
		ids[i] = i + 1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (incomes[j] > incomes[j+1]) {
				float t = incomes[j];
				incomes[j] = incomes[j+1];
				incomes[j+1] = t;

				int ti = ids[j];
				ids[j] = ids[j+1];
				ids[j+1] = ti;
			}
		}
	}

	cout << ids[0] << " " << ids[n / 2] << " " << ids[n - 1];

	cin.close();
	cout.close();
	return 0;
}