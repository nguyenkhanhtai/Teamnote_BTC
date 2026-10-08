#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int OFF = 1 << 18;

struct Node {
	int pref = 0, suf = 0;
	int maks = 0, sum = 0;
	
	void set(int value) {
		pref = max(pref, value);
		suf = max(suf, value);
		maks = max(maks, value);
		sum = value;
	}
} tour[OFF][2], e;

Node merge(const Node& L, const Node& R) {
	Node ret;
	ret.pref = max(L.pref, L.sum + R.pref);
	ret.suf = max(R.suf, L.suf + R.sum);
	ret.maks = max(L.maks, R.maks);
	ret.maks = max(ret.maks, L.suf + R.pref);
	ret.sum = L.sum + R.sum;
	return ret;
}

int value(char c, bool flag) {
	if ((c == 'P') ^ flag) return 1;
	return -1; 
}

int n, q;
string s;

void con(int x, int l, int r, bool flag) {
	if (l == r) {
		tour[x][flag].set(value(s[l], flag));
	} else {
		int mid = (l + r) >> 1;
		con(x * 2 + 1, l, mid, flag);
		con(x * 2 + 2, mid + 1, r, flag);
		tour[x][flag] = merge(tour[x * 2 + 1][flag], tour[x * 2 + 2][flag]);
	}
}

Node get(int x, int l, int r, int ql, int qr, bool flag) {
	if (ql <= l && r <= qr) return tour[x][flag];
	if (ql > r || l > qr) return e;
	
	int mid = (l + r) >> 1;
	
	return merge(
		get(x * 2 + 1, l, mid, ql, qr, flag),
		get(x * 2 + 2, mid + 1, r, ql, qr, flag)
	);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	cin >> s;
	
	con(0, 0, n - 1, 0);
	con(0, 0, n - 1, 1);
	
	while (q--) {
		int l, r;
		cin >> l >> r, --l, --r;
		Node X = get(0, 0, n - 1, l, r, 0);
		Node Y = get(0, 0, n - 1, l, r, 1);
		cout << max(X.maks, Y.maks) << "\n";
	}
	
	return 0;
}
