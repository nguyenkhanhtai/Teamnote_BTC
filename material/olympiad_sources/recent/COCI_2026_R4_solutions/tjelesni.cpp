#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second

using namespace std;

const int maxn = 1e5 + 10, off = (1 << 17);

int n, q, m;
int p[maxn];
int bio[maxn];
int tour[2][2 * off];
int prop[2][2 * off];
int lef[maxn];
int rig[maxn];

void push(int b, int x, int sz){
	if(x >= off || prop[b][x] == -1) return;
	
	int val = prop[b][x];
	prop[b][x] = -1;
	
	tour[b][x * 2] = sz * val;
	tour[b][x * 2 + 1] = sz * val;
	prop[b][x * 2] = val;
	prop[b][x * 2 + 1] = val;
}

void update(int b, int x, int lo, int hi, int l, int r, int val){
	int sz = hi - lo;
	push(b, x, sz / 2);
	
	if(hi <= l || r <= lo) return;
	
	if(l <= lo && hi <= r){
		tour[b][x] = sz * val;
		prop[b][x] = val;
		return;
	}
	
	int mid = (lo + hi) / 2;
	update(b, x * 2, lo, mid, l, r, val);
	update(b, x * 2 + 1, mid, hi, l, r, val);
	tour[b][x] = tour[b][x * 2] + tour[b][x * 2 + 1];
}

int query(int b, int x, int lo, int hi, int l, int r){
	int sz = hi - lo;
	push(b, x, sz / 2);
	
	if(hi <= l || r <= lo) return 0;
	
	if(l <= lo && hi <= r) return tour[b][x];
	
	int mid = (lo + hi) / 2;
	return query(b, x * 2, lo, mid, l, r) + query(b, x * 2 + 1, mid, hi, l, r);
}

void f(int x){
	for(int i = 0; i < n; i++){
		tour[i % 2][off + i / 2] = (p[i] >= x);
	}
	
	for(int i = 0; i < 2; i++){
		for(int j = off - 1; j >= 1; j--){
			tour[i][j] = tour[i][j * 2] + tour[i][j * 2 + 1];
			prop[i][j] = -1;
		}
	}
	
	for(int t = 0; t < q; t++){
		int l = lef[t];
		int r = rig[t];
		int cnt = query(0, 1, 0, off, (l + 1) / 2, r / 2 + 1) + query(1, 1, 0, off, l / 2, (r + 1) / 2);
		
		int par = r / 2 + 1 - (l + 1) / 2;
		int nep = (r + 1) / 2 - l / 2;
		
		if(l % 2 == 1){
			if(cnt <= par){
				update(0, 1, 0, off, (l + 1) / 2, (l + 1) / 2 + cnt, 1);
				update(0, 1, 0, off, (l + 1) / 2 + cnt, (l + 1) / 2 + par, 0);
				update(1, 1, 0, off, l / 2, l / 2 + nep, 0);
			}
			else {
				update(0, 1, 0, off, (l + 1) / 2, (l + 1) / 2 + par, 1);
				update(1, 1, 0, off, l / 2 + nep - (cnt - par), l / 2 + nep, 1);
				update(1, 1, 0, off, l / 2, l / 2 + nep - (cnt - par), 0);
			}
		}
		else {
			if(cnt <= nep){
				update(1, 1, 0, off, l / 2, l / 2 + cnt, 1);
				update(1, 1, 0, off, l / 2 + cnt, l / 2 + nep, 0);
				update(0, 1, 0, off, (l + 1) / 2, (l + 1) / 2 + par, 0);
			}
			else {
				update(1, 1, 0, off, l / 2, l / 2 + nep, 1);
				update(0, 1, 0, off, (l + 1) / 2 + par - (cnt - nep), (l + 1) / 2 + par, 1);
				update(0, 1, 0, off, (l + 1) / 2, (l + 1) / 2 + par - (cnt - nep), 0);
			}
		}
	}
	
	for(int i = 0; i < n; i++){
		bio[i] ^= query(i % 2, 1, 0, off, i / 2, i / 2 + 1);
	}
}

int main(){
	cin >> n >> q >> m;
	
	for(int i = 0; i < n; i++){
		cin >> p[i];
	}
	
	for(int i = 0; i < q; i++){
		cin >> lef[i] >> rig[i];
		lef[i]--;
		rig[i]--;
	}
	
	f(m);
	f(m + 1);
	
	for(int i = 0; i < n; i++){
		if(bio[i]) cout << i + 1;
	}
	cout << endl;
	
	return 0;
}
