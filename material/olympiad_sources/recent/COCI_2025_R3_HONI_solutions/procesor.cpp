#include <bits/stdc++.h>
using namespace std;

const int N = (1 << 12) + 5;
const int OFF = (1 << 11) - 1;

int tour[N], cnt[N];
bool root[N];

int query(int i, int j) {
	if (i == -1) return j;
	if (j == -1) return i;
	cout << "? " << i << " " << j << "\n";
	fflush(stdout);
	int cmp; cin >> cmp;
	if (cmp) return j;
	return i;
}

void insert(int i) {
	tour[i + OFF] = i;
	root[i + OFF] = 1;

	for (int lvl = 1, j = i + OFF; j; j /= 2, lvl *= 2) {
		if (++cnt[j] == lvl && lvl > 1) {
			root[j] = 1;
			root[j * 2] = root[j * 2 + 1] = 0;

			tour[j] = query(tour[j * 2], tour[j * 2 + 1]);
		}
	}
}

void erase(int node) {
	int i = node + OFF;
	tour[i] = -1;

	for (i /= 2; !root[i * 2]; i /= 2) {
		tour[i] = query(tour[i * 2], tour[i * 2 + 1]);
	}
}

int main() {
	int n, x, cur = 1;
	cin >> n;

    int ans = -1;
	while (n--) {
		cin >> x;
        if (ans != -1) erase(ans);
		while (x--) insert(cur++);

		ans = -1;
		for (int i = 1; i < 2 * OFF; ++i) {
			if (root[i]) {
				ans = query(ans, tour[i]);
			}
		}

		cout << "! " << ans << "\n";
		fflush(stdout);
	}

	return 0;
}
