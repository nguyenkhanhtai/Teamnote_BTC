#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;
typedef long long ll;

int n, q;
int a[MAXN];
ll pref[MAXN];

int provjeri (int pos, int x) {
	if (a[pos] > x) {
		return x * 2 - a[pos];
	}
	return a[pos];
}

ll provjeri2 (int x, int y, int mid) {
	return pref[mid] + 2ll * x * (y - mid) - (pref[n] - pref[n - y + mid]);
}


ll binary (int x, int y) {
	int lo = 0, hi = y, mid;
	while (lo < hi) {
		mid = (lo + hi) / 2;
		if (a[mid] > x) {
			hi = mid;
		} else if (a[n - y + mid] <= x) {
			lo = mid + 1;
		} else if (provjeri(mid, x) < provjeri(n - y + mid, x)) {
			lo = mid + 1;
		} else {
			hi = mid;
		}
	}
	return provjeri2(x, y, lo);
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
	}
	sort(a, a + n);
	for (int i = 0; i < n; ++i) {
		pref[i + 1] = pref[i] + a[i];
	}
	int x, y;
	for (int i = 0; i < q; ++i) {
		scanf("%d%d", &x, &y);
		printf("%lld\n", binary(x, y));
	}
	return 0;
}
