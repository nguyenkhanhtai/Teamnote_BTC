#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LOG = 30;
const int N = 5e5 + 2;

int n, a[N], ans;

ll solve(vector<int>& x, vector<int>& y, int bit, bool equal = 1) {
	int p = (int)y.size() - 1;
	ll ret = 0;
	for (int i = 0; i < (int)x.size(); ++i) {
		while (p >= 0 && x[i] + y[p] >= (1 << bit)) --p;
		ret += (int)y.size() - p - 1;
	}
	if (equal) {
		for (int num : x) {
			if (num * 2 >= (1 << bit)) ++ret;
		}
		return ret / 2LL;
	}
	return ret;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	for (int bit = 0; bit <= LOG; ++bit) {
		vector<int> L, R;
		for (int i = 0; i < n; ++i) {
			if (a[i] & 1 << bit) R.push_back(a[i]);
			else L.push_back(a[i]);
		}
		for (int i = 0; i < (int)L.size(); ++i) a[i] = L[i];
		for (int i = 0; i < (int)R.size(); ++i) a[i + (int)L.size()] = R[i];
		
		for (int& x : L) x &= (1 << bit) - 1;
		for (int& x : R) x &= (1 << bit) - 1;
		
		ll cnt = solve(L, L, bit) + solve(R, R, bit);
		cnt += (ll)L.size() * R.size() - solve(L, R, bit, 0);
		
		if (cnt & 1LL) ans |= 1 << bit;
	}
	
	cout << ans << "\n";
	
	return 0;
}
