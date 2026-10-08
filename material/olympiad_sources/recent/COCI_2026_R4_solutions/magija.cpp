#include <cstdio>
#include <vector>
#include <algorithm>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef long long ll;
typedef pair < int, int > pii;

const int N = 2e5 + 500;
const int BS = 1e6 + 3;
const int MOD =  1e9 + 7;

inline int add(int A, int B) {
	if(A + B >= MOD)
		return A + B - MOD;
	return A + B;
}

inline int sub(int A, int B) {
	if(A - B < 0)
		return A - B + MOD;
	return A - B;
}

inline int mul(int A, int B) {
	return (ll)A * B % MOD;
}

int par[N], loga[N], pot[N], tko[N];
int miin[N], maax[N], n, q, edg_cnt = 0;
vector < int > komp[N];
vector < pii > edg;

void loga_add(int i, int x) {
	for(; i < N; i += i & -i)
		loga[i] = add(loga[i], x);
}

int get_hsh(int l, int r) {
	int ret = 0; l--;
	int ol_r = r;
	for(; r ; r -= r & -r) ret = add(ret, loga[r]);
	for(; l ; l -= l & -l) ret = sub(ret, loga[l]);
	return mul(pot[n - ol_r], ret);
}

void spoji(int a, int b) {
	a = tko[a], b = tko[b];
	if((int)komp[a].size() < (int)komp[b].size()) swap(a, b);
	miin[a] = min(miin[a], miin[b]);
	maax[a] = max(maax[a], maax[b]);
	for(int x : komp[b]) {
		tko[x] = a;
		loga_add(x, mul(pot[x], sub(a, b)));
		komp[a].PB(x);
	}
	komp[b].clear();
}

void nadi_edge(int l1, int r1, int l2, int r2) {
	if(l1 == r1) {
		if(tko[l1] != tko[l2]) spoji(l1, l2);
		return;
	}
	if(get_hsh(l1, r1) == get_hsh(l2, r2)) return;
	int pol = (r1 - l1 + 1) / 2;
	nadi_edge(l1, l1 + pol - 1, l2, l2 + pol - 1); 
	nadi_edge(l1 + pol, r1, l2 + pol, r2);	
}

int main() {
	pot[0] = 1;
	for(int i = 1;i < N;i++) pot[i] = mul(BS, pot[i - 1]);
	scanf("%d%d", &n, &q);
	for(int i = 1;i <= n;i++) {
		tko[i] = i, miin[i] = i, maax[i] = i;
		 komp[i].PB(i);
		loga_add(i, mul(i, pot[i]));
	}
	for(;q--;) {
		int ty; scanf("%d", &ty);
		if(ty == 1) {
			int x; scanf("%d", &x); x = tko[x];
			printf("%d %d\n", miin[x], maax[x]);
		} else {
			int l1, l2, len; scanf("%d%d%d", &l1, &l2, &len);
			nadi_edge(l1, l1 + len - 1, l2, l2 + len - 1);
		}
	}
	return 0;
}
