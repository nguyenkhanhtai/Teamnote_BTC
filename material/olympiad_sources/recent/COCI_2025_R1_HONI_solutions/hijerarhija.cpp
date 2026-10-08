#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long llint;

const int maxn = 3e5+10;
const int base = 31337;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const int logo = 20;
const int off = 1 << logo;
const int treesiz = off << 1;

int n, q;
set< pair<int, int> > s;
int in[maxn];
int cnt0, cnt1;

void print() {
	if (cnt0 == 1 && cnt1 == n - 1) printf("DA\n");
	else printf("NE\n");
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		in[b]++;
		s.insert({a, b});
	}

	for (int i = 1; i <= n; i++) {
		if (in[i] == 0) cnt0++;
		else if (in[i] == 1) cnt1++;
	}

	print();
	scanf("%d", &q);
	while (q--) {
		int a, b;
		scanf("%d%d", &a, &b);

		if (!s.count({a, b})) {
			swap(a, b);
		}

		s.erase({a, b});
		s.insert({b, a});
		if (in[b] == 2) cnt1++;
		else if (in[b] == 1) cnt1--, cnt0++;

		if (in[a] == 0) cnt0--, cnt1++;
		else if (in[a] == 1) cnt1--;
		in[b]--, in[a]++;
		print();
	}
	return 0;
}