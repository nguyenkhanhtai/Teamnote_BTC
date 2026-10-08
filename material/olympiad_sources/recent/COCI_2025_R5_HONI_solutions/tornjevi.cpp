#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long llint;

const int maxn = 1e6+10;
const int base = 31337;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const int logo = 20;
const int off = 1 << logo;
const int treesiz = off << 1;

int n;
int niz[maxn];
int l[maxn], r[maxn];
list< pair<int, int> > s;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", niz+i);

	llint sol = 0;
	for (int i = 0; i < n; i++) {
		s.push_back({niz[i], i});
		for (auto iter = s.begin(); iter != s.end();) {
			iter->X = __gcd(niz[i], iter->X);
			if (iter != s.begin()) {
				auto prev = iter;
				prev--;
				if (prev->X == iter->X) iter = s.erase(iter);
				else iter++;
			} else iter++;
		}
		l[i] = s.rbegin()->Y;
	}

	s.clear();
	for (int i = n - 1; i >= 0; i--) {
		s.push_back({niz[i], i});
		for (auto iter = s.begin(); iter != s.end();) {
			iter->X = __gcd(niz[i], iter->X);
			if (iter != s.begin()) {
				auto prev = iter;
				prev--;
				if (prev->X == iter->X) iter = s.erase(iter);
				else iter++;
			} else iter++;
		}
		r[i] = s.rbegin()->Y;
	}
	for (int i = 0; i < n; i++) printf("%d ", r[i] - l[i] + 1);
	return 0;
}