#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

#define PB push_back

const int mod = 1e9 + 7;
const int MAXN = 5000;

int ans[MAXN], dp[MAXN][MAXN], ndp[MAXN][MAXN], sz[MAXN], n;
vi g[MAXN];

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int mul(ll a, ll b){
	return (a * b) % mod;
}

int sub(int a, int b){
	a -= b;
	if(a < 0) a += mod;
	return a;
}

void merge(int u, int x) {
	for(int i=0; i<=sz[u] + sz[x]; i++) ndp[u][i] = 0;	
	for(int ja=sz[u]; ja>=0; ja--){
		for(int ti=sz[x]; ti>=0; ti--){
			ndp[u][ja + ti] = add(ndp[u][ja + ti], mul(dp[u][ja], dp[x][ti]));
		}
	}
	sz[u] += sz[x];
	for(int i=0; i<=sz[u]; i++) dp[u][i] = ndp[u][i];	
}

//ch je dijete od roota i zelimo ga odspojit od roota stabla i postavit na root
void unmerge(int ch, int par){
	//rekonstrukcija parenta - izbacivanje
	for(int suma=0; suma<=sz[par] - sz[ch]; suma++){
		for(int ja=1; ja<=min(suma, sz[ch]); ja++){
			dp[par][suma] = sub(dp[par][suma], mul(dp[ch][ja], dp[par][suma - ja]));
		}
	}
	for(int suma=sz[par] - sz[ch] + 1; suma <= sz[par]; suma++) dp[par][suma] = 0;
	sz[par] -= sz[ch];
	dp[ch][1] = sub(dp[ch][1], 1);
	dp[par][1] = add(dp[par][1], 1);
	//spoji bivseg parenta na novi root
	merge(ch, par);
}

void dfs(int u, int p = -1){
	sz[u] = 1;
	dp[u][0] = 1;
	for(auto &x : g[u]){
		if(x == p) continue;
		dfs(x, u);
		merge(u, x);
	}
	
	if(p != -1) dp[u][1] = add(dp[u][1], 1);
}

void reroot(int u, int p = -1){
	if(p != -1) unmerge(u, p);
	for(int i=0; i<n; i++) ans[i] = add(ans[i], dp[u][i]);
	for(auto &x : g[u]) if(x != p) reroot(x, u);
	if(p != -1) unmerge(p, u);
}

void solve(){
	cin >> n;
	for(int i=1, a, b; i<n; i++){
		cin >> a >> b;
		g[a].PB(b);
		g[b].PB(a);
	}
	
	dfs(1);
  
	reroot(1);
	for(int i=0; i<n; i++) cout << ans[i] << " ";
	cout << "\n";
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
