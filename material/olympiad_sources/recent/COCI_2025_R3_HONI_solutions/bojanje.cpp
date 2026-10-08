#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

typedef pair<int, int> pii;

const int N = 2005;

int n, a[N][N], cnt[N][2][3];
vector<pair<int, pii>> ans;
bool painted[N][N];

int check(int t, int i) {
	if (cnt[i][t][0]) return 0;
	if (cnt[i][t][1] && cnt[i][t][2]) return 0;
	if (cnt[i][t][1]) return 1;
	if (cnt[i][t][2]) return 2;
	return 0;
}

void paint_cell(int i, int j) {
	if (painted[i][j]) return ;
	painted[i][j] = 1;
	--cnt[i][0][a[i][j]];
	--cnt[j][1][a[i][j]];
}

void paint_block(int t, int i, int val) {
	ans.push_back({t, {i, val}});

	for (int j = 0; j < n; ++j) {
		if (t) paint_cell(j, i);
		else paint_cell(i, j);
	}

	for (int j = 0; j < n; ++j) {
		if ((val = check(t ^ 1, j))) paint_block(t ^ 1, j, val);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> a[i][j];
			++cnt[i][0][a[i][j]];
			++cnt[j][1][a[i][j]];
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int val, type = 0; type < 2; ++type) {
			if ((val = check(type, i))) paint_block(type, i, val);
		}
	}

	bool good = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) good &= painted[i][j] || !a[i][j];
	}

	if (good) {
		cout << ans.size() << "\n";
		reverse(ans.begin(), ans.end());
		for (auto x : ans) {
			cout << x.X + 1 << " " << x.Y.X + 1 << " " << x.Y.Y << "\n";
		}
	} else cout << "-1\n";

	return 0;
}
