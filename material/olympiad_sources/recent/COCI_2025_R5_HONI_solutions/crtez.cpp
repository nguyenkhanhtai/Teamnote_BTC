#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;

#define PB push_back
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

const int mod = 1e9 + 7;
const int logo = 21;
const int MAXN = 2e6 + 7;
const int off = 1 << logo;
const int trsz = off << 1;


int mul(ll a, ll b){
	return (a * b) % mod;
}

int exp(int b, ll e){
	int ret = 1;
	for(; e; e /= 2, b = mul(b, b)) if(e & 1) ret = mul(ret, b);
	return ret;
}


vpll p;
vll v;
map<ll, int> id;

struct tournament{
	ll seg[trsz], su[trsz];
	bool fl[trsz];
	
	void prop(int x){
		if(!fl[x]) return;
		seg[x] = su[x] - seg[x];
		if(x < off) fl[x * 2] ^= 1, fl[x * 2 + 1] ^= 1;
		fl[x] = 0;
	}
	
	void update(int x, int lo, int hi, int a, int b){
		prop(x);
		if(lo >= b or hi <= a) return;
		if(lo >= a and hi <= b){
			fl[x] = 1;
			prop(x);
			return;
		}
		int mid = (lo + hi) / 2;
		update(x * 2, lo, mid, a, b);
		update(x * 2 + 1, mid, hi, a, b);
		seg[x] = seg[x * 2] + seg[x * 2 + 1];
	}
	
	void build(){
		for(int i=off; i<trsz; i++){
			if(i - off >= (int)v.size() - 1) su[i] = 0;
			else su[i] = v[i - off + 1] - v[i - off];
		}
		for(int i=off-1; i; i--) su[i] = su[i * 2] + su[i * 2 + 1];
	}
}t;


void solve(){
	ll n, q;
	cin >> n >> q;
	v.PB(1);
	v.PB(n + 1);
	for(int i=0; i<q; i++){
		ll l, r;
		cin >> l >> r;
		p.PB({l, r});
		v.PB(l);
		v.PB(r + 1);
	}
	sort(all(v));
	v.erase(unique(all(v)), v.end());
	for(int i=0; i<(int)v.size(); i++) id[v[i]] = i;
	t.build();
	t.update(1, 0, off, id[1], id[n + 1]);
	for(int i=0; i<q; i++){
		ll l = p[i].X, r = p[i].Y;
		t.update(1, 0, off, id[l], id[r + 1]);
		cout << exp(3, t.seg[1]) << "\n";
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}

