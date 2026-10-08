#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define PB push_back
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

const int MAXN = 1e5 + 7;
const int off = 1 << 17;
const int trsz = off << 1;

struct tournament{
	ii seg[trsz];
	int p[trsz];
	
	void mrg(ii &c, ii &a, ii &b){
		c = a;
		if(a.X > b.X) c = b;
		if(a.X == b.X) c.Y += b.Y;
	}
	
	tournament(){
		for(int i=off; i<trsz; i++) seg[i] = {0, 1};
		for(int i=off-1; i; i--) seg[i].Y = seg[i * 2].Y + seg[i * 2 + 1].Y;
	}
	
	void update(int x, int lo, int hi, int a, int b, int v){
		if(lo >= b or hi <= a) return;
		if(lo >= a and hi <= b){
			seg[x].X += v;
			p[x] += v;
			return;
		}
		int mid = (lo + hi) / 2;
		update(x * 2, lo, mid, a, b, v);
		update(x * 2 + 1, mid, hi, a, b, v);
		mrg(seg[x], seg[x * 2], seg[x * 2 + 1]);
		seg[x].X += p[x];
	}
	
	int qry(){
		if(seg[1].X == 0) return seg[1].Y;
		return 0;
	}
}t;

vii ad[5][MAXN], rm[5][MAXN];
vi po[MAXN];
int n, k;
ll ans;

void unija(int maska){
	bool f = (__builtin_popcount(maska) % 2 == 0);
	for(int i=1; i<=n+1; i++){
		for(int j=0; j<k; j++){
			if(!(maska & (1 << j))) continue;
			for(auto &x : ad[j][i]) t.update(1, 0, off, x.X, x.Y + 1, 1);
			for(auto &x : rm[j][i]) t.update(1, 0, off, x.X, x.Y + 1, -1);
		}
		if(f) ans -= off - t.qry();
		else ans += off - t.qry();
	}
}

void add_rect(int s, int a, int b, int c, int d){
	ad[s][a].PB({c, d});
	rm[s][b + 1].PB({c, d});
}

void solve(){
	cin >> n >> k;
	for(int i=1; i<=n; i++) po[i].PB(0);
	for(int i=1; i<=n; i++){
		int x;
		cin >> x;
		po[x].PB(i);
	}
	for(int i=1; i<=n; i++) po[i].PB(n + 1);
	
	for(int j=0; j<k; j++){
		for(int vl=1; vl<=n; vl++){
			for(int i=j+1; i<(int)po[vl].size() - 1; i++){
				int m = i - j - 1;
				add_rect(j, po[vl][m] + 1, po[vl][m + 1], po[vl][i], po[vl][i + 1] - 1);
			}
		}
	}
	
	for(int i=0; i<(1 << k); i++) unija(i);
	cout << ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}
