#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 2;

int n, D, X, x[N], y[N], idx[N], answer;
bool possible = 1;
priority_queue<int> pq;

int main() {
	cin >> n >> D >> X;

	for (int i = 0; i < n; ++i) cin >> x[i];
	for (int i = 0; i < n; ++i) cin >> y[i];

	iota(idx, idx + n, 0);
	sort(idx, idx + n, [&](int& i, int& j) {
		return x[i] < x[j];
	});

	int reached = D, ptr = 0;
	while (reached < X) {
		while (ptr < n && x[idx[ptr]] <= reached) {
			pq.push(y[idx[ptr]]);
			++ptr;
		}

		if (pq.empty()) {
			possible = 0;
			break;
		}

		int increment = pq.top();
		pq.pop();

		reached += increment;
		answer++;
	}

	if (!possible) cout << "-1\n";
	else cout << answer << "\n";

	return 0;
}
