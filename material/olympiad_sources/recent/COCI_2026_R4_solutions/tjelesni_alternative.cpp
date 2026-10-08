#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define PB push_back
#define PF push_front
#define PPB pop_back
#define PPF pop_front
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

const int mod = 1e9 + 7; //998244353;
const int inf = 1e9 + 7;
const ll INF = (ll)1e18 + 7;
const int logo = 17;
const int MAXN = 1e5 + 7;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct tournament{
	int seg[trsz], fli;
	ii p[trsz];
	
	//p.X - postavi
	//p.Y - naizmjenicno al koji je 1. element
	void res(){
		fill(seg, seg + trsz, 0);
		fill(p, p + trsz, (ii){-1, -1});
	}
	
	void prop(int x, int lo, int hi){
		if(p[x] == (ii){-1, -1}) return;
		
		if(p[x].X != -1){
			seg[x] = (hi - lo) * p[x].X;
			if(x < off){
				p[x * 2] = p[x];
				p[x * 2 + 1] = p[x];
			}
		}else{
			seg[x] = (hi - lo + p[x].Y) / 2;
			
			if(x * 2 < off){
				p[x * 2] = {-1, p[x].Y};
				p[x * 2 + 1] = {-1, p[x].Y};
			}else if(x < off){
				p[x * 2] = {-1, p[x].Y};
				p[x * 2 + 1] = {-1, p[x].Y ^ 1};
			}
		}
		
		p[x] = {-1, -1};
	}
	
	void update(int x, int lo, int hi, int a, int b, ii vl){
		prop(x, lo, hi);
		if(lo >= b or hi <= a) return;
		if(lo >= a and hi <= b){
			if(vl.X == -1) p[x] = {-1, fli % 2};	
			else p[x] = vl;
			prop(x, lo, hi);
			if(vl.X == -1) fli += (hi - lo);
			return;
		}
		int mid = (lo + hi) / 2;
		update(x * 2, lo, mid, a, b, vl);
		update(x * 2 + 1, mid, hi, a, b, vl);
		seg[x] = seg[x * 2] + seg[x * 2 + 1];
	}
	
	int query(int x, int lo, int hi, int a, int b){
		prop(x, lo, hi);
		if(lo >= b or hi <= a) return 0;
		if(lo >= a and hi <= b) return seg[x];
		int mid = (lo + hi) / 2;
		return query(x * 2, lo, mid, a, b) + query(x * 2 + 1, mid, hi, a, b);
	}
}t;

int ans[MAXN], p[MAXN], n;
vii qs;

void f(int value){
	t.res();
	for(int i=1; i<=n; i++){
		if(p[i] >= value) t.update(1, 0, off, i, i + 1, {1, -1});
	}
	for(auto &x : qs){
		int jed = t.query(1, 0, off, x.X, x.Y + 1);
		int nul = x.Y - x.X + 1 - jed;
		
		int post = min(jed, nul) * 2;
		int vl = (jed > nul) ? 1 : 0;
		
		t.fli = 0;
		t.update(1, 0, off, x.X, x.X + post, {-1, 1});
		t.update(1, 0, off, x.X + post, x.Y + 1, {vl, -1});
	}
	
	for(int i=1; i<=n; i++){
		int vl = t.query(1, 0, off, i, i + 1);
		ans[i] ^= vl;
	}
}

void solve(){
	int q, x;
	cin >> n >> q >> x;
	for(int i=1; i<=n; i++) cin >> p[i];
	while(q--){
		int l, r;
		cin >> l >> r;
		qs.PB({l, r});
	}
	
	f(x);
	f(x + 1);
	for(int i=1; i<=n; i++){
		if(ans[i]) cout << i << "\n";
	}	
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int tt = 1;
	//cin >> tt;
	while(tt--) solve();
	return 0;
}

