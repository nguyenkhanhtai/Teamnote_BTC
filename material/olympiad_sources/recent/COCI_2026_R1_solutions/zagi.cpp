#include <bits/stdc++.h>
#define X first
#define Y second
 
using namespace std;
typedef long long llint;
const int maxn = 2e5; 
const int maxm = 35;
 
int n, q;
int s[maxn];
int posr[maxm][maxn], posl[maxm][maxn], dpl[maxm][maxn], dpr[maxm][maxn], z[maxm][maxn];
int k, kols[maxm], id[maxn];
 
bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.Y - a.X < b.Y - b.X;
}           
 
int solve(int l, int r) {
    llint mask = 0;
	for (int x = 0; x < maxm; x++) {
		if (posr[x][l] > r) continue;
		int lf = posr[x][l];
		int rf = posl[x][r];
		int now = 0;
		for (int i = id[lf]; i < id[rf]; i++) 
			now ^= z[x][i + 1];
 
		if (l < lf) {
			if (dpr[x][l] == -1) dpr[x][l] = solve(l, lf - 1);
			now ^= dpr[x][l];	
		}
		if (rf < r) {
			if (dpl[x][r] == -1) dpl[x][r] = solve(rf + 1, r);
			now ^= dpl[x][r];	
		}
		if (now < maxm) mask |= (1 << now);
	}
	for (int i = 0; i < maxm; i++)
	    if (((mask >> i) & 1) == 0)
	        return i;
	return maxm;	
}
 
int solve2(int l, int r) {
	llint mask = 0;
	for (int x = 0; x < maxm; x++) {
		if (posr[x][l] > r) continue;
		int lf = posr[x][l];
		int rf = posl[x][r];
		int now = (z[x][id[lf]] ^ z[x][id[rf]]);
 
		if (l < lf) {
			if (dpr[x][l] == -1) dpr[x][l] = solve2(l, lf - 1);
			now ^= dpr[x][l];	
		}
		if (rf < r) {
			if (dpl[x][r] == -1) dpl[x][r] = solve2(rf + 1, r);
			now ^= dpl[x][r];	
		}
		if (now < maxm) mask |= (1 << now);
	}
	for (int i = 0; i < maxm; i++)
	    if (((mask >> i) & 1) == 0)
	        return i;
	return maxm;
}
 
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; i++) {
		scanf("%d", s+i);
		s[i]--;
	}
 
	for (int i = 0; i < n; i++) {
		id[i] = kols[s[i]];
		kols[s[i]]++;
	}
 
	for (int i = 0; i < maxm; i++)
		posr[i][n] = n;
	for (int i = n - 1; i >= 0; i--) {
		for (int x = 0; x < maxm; x++)
			posr[x][i] = posr[x][i + 1];
		posr[s[i]][i] = i;
	}
 
	for (int i = 0; i < maxm; i++)
		posl[i][0] = -1;
	posl[s[0]][0] = 0;         
	for (int i = 1; i < n; i++) {
		for (int x = 0; x < maxm; x++)
			posl[x][i] = posl[x][i - 1];
		posl[s[i]][i] = i;
	}
 
	memset(dpl, -1, sizeof dpl);
	memset(dpr, -1, sizeof dpr);
 
	vector<pair<int, int> > seg;
	for (int x = 0; x < maxm; x++) {
		vector<int> pos;
		for (int i = 0; i < n; i++)
			if (s[i] == x)
				pos.push_back(i);
 
		for (int t = 0; t < (int)pos.size() - 1; t++)
			seg.push_back(make_pair(pos[t], pos[t + 1]));
	}
	sort(seg.begin(), seg.end(), cmp);
	for (pair<int, int> t : seg) {
		int l = t.X;
		int r = t.Y;
		if (r == l + 1) continue;
		int x = solve(l + 1, r - 1);
		z[s[r]][id[r]] = x;
	}
 
	for (int x = 0; x < maxm; x++)
		for (int i = 1; i < kols[x]; i++)
 			z[x][i] ^= z[x][i - 1];	
 
	for (int i = 0; i < q; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		printf(solve2(l, r) == 0 ? "Jakov\n" : "Toni\n");
	}	
	return 0;
}
