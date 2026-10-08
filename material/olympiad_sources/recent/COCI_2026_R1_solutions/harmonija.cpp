#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

#define PB push_back

const ll INF = (ll)1e18 + 7;
const int logo = 17;
const int MAXN = 1e5 + 7;

struct mat{
	ll a[5][5];
	
	mat(){
		for(int i=0; i<5; i++){
			for(int j=0; j<5; j++) a[i][j] = -INF;
		}
	}
	
	void res(){
		for(int i=0; i<5; i++){
			for(int j=0; j<5; j++) a[i][j] = -INF;
		}
	}
};

int par[logo][MAXN], dep[MAXN], vl[2][MAXN];
mat f[logo][MAXN], f2[logo][MAXN], res, res2;
vi g[MAXN];

void mrg(mat &c, mat a, mat b){
	c.res();
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			for(int k=0; k<5; k++){
				c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
			}
		}
	}
}

void dfs(int u, int p = -1){
	if(p == -1){
		dep[u] = 1;
		par[0][u] = u;
	}else{
		dep[u] = dep[p] + 1;
		par[0][u] = p;
	}
	
	for(auto &x : g[u]) if(x != p) dfs(x, u);
}

int getLCA(int a, int b){
	if(dep[a] < dep[b]) swap(a, b);
	int delta = dep[a] - dep[b];
	for(int i = 0; i < logo; i++) if(delta & (1 << i)) a = par[i][a];
	if(a == b) return a;
	for(int i = logo - 1; i >= 0; i--){
		if(par[i][a] != par[i][b]){
			a = par[i][a], b = par[i][b];
		}
	}
	return par[0][a];
}

void solve(){
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> vl[0][i];
	for(int i = 1; i <= n; i++) cin >> vl[1][i];
	for(int i = 1, a, b; i < n; i++){
		cin >> a >> b;
		g[a].PB(b);
		g[b].PB(a);
	}
	g[0].PB(1);
	dfs(0);
	
	for(int i = 0; i <= n; i++){
		for(int fir = 0; fir < 4; fir++) f[0][i].a[fir][fir + 1] = vl[0][i];
		for(int fir = 1; fir < 5; fir++) f[0][i].a[fir][fir - 1] = vl[1][i];
		f2[0][i] = f[0][i];
	}
	
	for(int j = 1; j < logo; j++){
		for(int i = 0; i <= n; i++){
			int nex = par[j - 1][i];
			par[j][i] = par[j - 1][nex];
			mrg(f[j][i], f[j - 1][i], f[j - 1][nex]);
			mrg(f2[j][i], f2[j - 1][nex], f2[j - 1][i]);
		}
	}
	
	while(q--){
		int a, b, c;
		cin >> a >> b;
		c = getLCA(a, b);
		
		res.res();
		res.a[2][2] = 0;
		
		int delta = dep[a] - dep[c];
		for(int i = logo - 1; i >= 0; i--){
			if(!(delta & (1 << i))) continue;
			mrg(res, res, f[i][a]);
			a = par[i][a];
		}
		
		mrg(res, res, f[0][c]);
		
		
		bool fir = 1;
		delta = dep[b] - dep[c];
		for(int i = logo - 1; i >= 0; i--){
			if(!(delta & (1 << i))) continue;
			if(fir) res2 = f2[i][b];
			else mrg(res2, f2[i][b], res2);
			b = par[i][b];
			fir = 0;
		}
		
		if(delta) mrg(res, res, res2);
		
		ll ans = -INF;
		for(int i=0; i<5; i++) ans = max(ans, res.a[2][i]);
		cout << ans << "\n";
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}

