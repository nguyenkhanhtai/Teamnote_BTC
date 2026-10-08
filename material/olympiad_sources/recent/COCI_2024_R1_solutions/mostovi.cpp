#include <cstdio>
#include <vector>
#include <set>

#define PB push_back
#define X first
#define Y second

using namespace std;

const int N = 2e5 + 500;
const int OFF = (1 << 18);
const int LOG = 19;

int par[N][LOG], dep[N];
set < int > st[N];
vector < int > v[N], t[N], gore[N];

int max_iznad[N], min_iznad[N], ind_ch[N], dob[N], L[N], R[N], iznad_bez[N], n, m, tme;
int osobno[N];

void dfs_tree(int x, int lst){
	dep[x] = dep[lst] + 1; L[x] = tme++;
	for(int y : v[x]) {
		if(!dep[y]) {
			dfs_tree(y, x); par[y][0] = x;
			ind_ch[y] = (int)t[x].size();
			t[x].PB(y);
		} else if(y != lst && dep[y] < dep[x]) {
			gore[x].PB(y);
		}
	}
	R[x] = tme - 1;
}

void lca_precompute(){
	for(int j = 1;j < LOG;j++)
		for(int i = 1;i <= n;i++)
			par[i][j] = par[par[i][j - 1]][j - 1];
}

int digni(int x, int k) {
	for(int i = 0;i < LOG;i++)
		if(k & (1 << i)) x = par[x][i];
	return x;
}

int T[2 * OFF], loga[N];

void add(int x, int y) {
	for(x++;x < N;x += x & -x)
		loga[x] += y;
}

int query(int x) {
	int ret = 0;
	for(x++; x ; x -= x & -x)
		ret += loga[x];
	return ret;
}

int min_query(int i, int a, int b, int lo, int hi) {
	if(lo <= a && b <= hi) return T[i];
	if(a > hi || b < lo) return N;
	return min(min_query(2 * i, a, (a + b) / 2, lo, hi), min_query(2 * i + 1, (a + b) / 2 + 1, b, lo, hi));
}

void dfs_comp(int x){
	int P = 0;
	for(int y : t[x]) {
		dfs_comp(y); 
		dob[y] = P < dep[x];
		P = max(P, min_iznad[y]);
		if(st[y].size() > st[x].size()) swap(st[x], st[y]);
		for(int z : st[y]) st[x].insert(z);
	}
	iznad_bez[x] = P;
	P = 0;
	for(int i = (int)t[x].size() - 1;i >= 0;i--) {
		dob[t[x][i]] &= P < dep[x];
		P = max(P, min_iznad[t[x][i]]);
	}
	osobno[x] = N;
	for(int y : gore[x]) st[x].insert(dep[y]), osobno[x] = min(osobno[x], dep[y]);
	while(!st[x].empty() && *st[x].rbegin() == dep[x] - 1) 
		st[x].erase(--st[x].end());
	if(!st[x].empty()) {
		max_iznad[x] = *st[x].rbegin();
		min_iznad[x] = *st[x].begin();
	} else {
		max_iznad[x] = 0;
		min_iznad[x] = N;
	}
}

int sol = 0;

void dfs_fin(int x) {
	for(int y : t[x]) dfs_fin(y);
	if(x == 1) {
		int vel = 0, mal = 0;
		for(int y : t[x]) {
			if(t[y].size() > 0)
				vel++;
			else
				mal++;
		}
		if(mal == 0) {
			if(vel > 1) sol += vel;
			else for(int y : t[x])
				if((int)t[y].size() > 1) sol++;
		} else {
			sol += vel;
			if(vel + mal > 2) sol += mal;
		}
		return;	
	}
	for(int y : t[x]) 
		add(min_iznad[y] + 1, 1), add(max_iznad[y], -1);
	int svi = 1;
	set < int > pos;
	for(int y : t[x]) {
		if(!(dob[y] && iznad_bez[y] < dep[x])) {
			sol++;
		}
		svi &= min_iznad[y] < dep[x]; 
		if(min_iznad[y] == max_iznad[y]) {
			pos.insert(min_iznad[y]);			
		}
	}
	for(int y : gore[x]) {
		if(y != 1) {
			int oboje = query(dep[y]);
			int yy = digni(x, dep[x] - dep[y] - 1);
			if(!dob[yy] || !svi) {
				sol++; continue;
			}
			if(oboje > 0) {
				if(pos.count(dep[y])) {
					sol++;
				}
			} else {
				int veza = min(min_query(1, 0, OFF - 1, L[yy], L[x] - 1), min_query(1, 0, OFF - 1, R[x] + 1, R[yy]));
				if(veza >= dep[y]) {
					sol++;
				} else {
					if(pos.count(dep[y])) {
						sol++;
					}
				}
			}
		} else {
			if((int)t[y].size() > 1) {
				sol++; continue;
			}
			if(!svi || pos.count(dep[y])) {
				sol++;
			}
		}
	}
	for(int y : t[x]) 
		add(min_iznad[y] + 1, -1), add(max_iznad[y], 1); 
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0;i < m;i++) {
		int a, b; scanf("%d%d", &a, &b);
		v[a].PB(b), v[b].PB(a);
	}
	dfs_tree(1, 1);
	lca_precompute();
	dfs_comp(1);
	for(int i = 1;i <= n;i++) T[OFF + L[i]] = osobno[i];
	for(int i = OFF - 1; i ; i--) T[i] = min(T[2 * i], T[2 * i + 1]);
	dfs_fin(1);
	printf("%d\n", sol);
	return 0;
}
