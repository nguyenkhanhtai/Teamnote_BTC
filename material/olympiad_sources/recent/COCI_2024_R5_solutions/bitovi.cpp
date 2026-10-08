#include <bits/stdc++.h>
using namespace std;
const int N = (1 << 15) + 1;
const int LOG = 15;

int n, a[N], b[N], inv[N];
bool ok[N];
vector<pair<int, int> > ans;
set<int> s;

void upd(int i, int j) {
	ans.push_back({a[i], a[i] ^ 1 << j});
	inv[a[i]] = 0;
	if (ok[a[i]]) s.insert(i);
	a[i] ^= 1 << j;
	inv[a[i]] = i;
	if (ok[a[i]]) s.erase(s.find(i));
}

void solve(int i, int num, int j = 0) {
	for (; j < LOG; ++j) {
		if (a[i] & 1 << j ^ num & 1 << j) {
			if (inv[a[i] ^ 1 << j]) {
				solve(inv[a[i] ^ 1 << j], num, j + 1);
				upd(i, j);
				break;
			} else {
				upd(i, j);
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];

	for (int i = 1; i <= n; ++i) {
		inv[a[i]] = i;
		ok[b[i]] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		if (!ok[a[i]]) s.insert(i);
	}

	for (int i = 1; i <= n; ++i) {
		if (!inv[b[i]]) {
			solve(*s.begin(), b[i]);
		}
	}

	cout << ans.size() << "\n";
	for (pair<int, int> p : ans) {
		cout << p.first << " " << p.second << "\n";
	}
	return 0;
}
