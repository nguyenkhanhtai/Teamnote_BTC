#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int maxn=1e6+5;

pair < int, int > a[maxn];
pair < int, int > q[maxn];
int sol[maxn];
multiset < int > s1, s2;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int x;
	for(int i = 0; i < n; i++) {
		scanf("%d%d%d", &a[i].first, &a[i].second, &x);
		s2.insert(a[i].second - a[i].first);
	}
	sort(a, a + n);
	for(int i = 0; i < m; i++) {
		scanf("%d", &q[i].first);
		q[i].second = i;
	}
	sort(q, q + m);
	int pos = 0, tren;
	for(int i = 0; i < m; i++) {
		while(pos < n && a[pos].first < q[i].first) {
			s1.insert(a[pos].second + a[pos].first);
			s2.erase(s2.find(a[pos].second - a[pos].first));
			pos++;
		}
		tren = 0;
		if(!s1.empty()) {
			tren = max(tren, *(--s1.end()) - q[i].first);
		}
		if(!s2.empty()) {
			tren = max(tren, *(--s2.end()) + q[i].first);
		}
		sol[q[i].second] = tren;
	}
	for(int i = 0; i < m; i++) {
		printf("%d ", sol[i]);
	}
	printf("\n");
	return 0;
}
