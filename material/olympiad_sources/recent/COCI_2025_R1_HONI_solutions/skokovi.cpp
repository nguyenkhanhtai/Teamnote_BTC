#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 2;

int n, k, a[N];

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	int l = a[0], r = a[0];
	cout << "1 ";
	for (int i = 1; i < n; ++i) {
		if (l - k <= a[i] && a[i] <= r + k) {
			cout << "1 ";
			l = min(l, a[i]);
			r = max(r, a[i]);
		} else cout << "0 ";
	}
	cout << "\n";
	
	return 0;
}
