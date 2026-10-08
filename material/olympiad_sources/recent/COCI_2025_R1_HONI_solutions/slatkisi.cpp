#include <bits/stdc++.h>
using namespace std;

const int N = 101;

int n, s[N];
int sum, M;

int main() {

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> s[i];
		sum += s[i];
		M = max(M, s[i]);
	}

	cout << M * n - sum << "\n";

	return 0;
}
