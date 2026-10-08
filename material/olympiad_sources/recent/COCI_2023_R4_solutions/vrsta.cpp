#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 2e5 + 5, Log = 18, pot = (1 << Log);

struct tournament {
	ll t[pot * 2];
	void update(int x, int val) {
		for(; x > 0; x /= 2) {
			t[x] += val;
		}
	}
	int query(int x, ll val) {
		if(x >= pot) {
			return x - pot;
		}
		if(t[x * 2] >= val) {
			return query(x * 2, val);
		}
		return query(x * 2 + 1, val - t[x * 2]);
	}
};

tournament T;
int a[maxn], cnt[maxn];
vector < int > v;
map < int, int > ind;
int rev[maxn];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d%d", a + i, cnt + i);
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	int br = 0;
	for(int i = 0; i < v.size(); i++) {
		ind[v[i]] = br;
		rev[br] = v[i];
		br++;
	}
	ll uk = 0;
	for(int i = 0; i < n; i++) {
		uk += cnt[i];
		T.update(ind[a[i]] + pot, cnt[i]);
		printf("%d\n", rev[T.query(1, (uk + 1) / 2)]);
	}
	return 0;
}
