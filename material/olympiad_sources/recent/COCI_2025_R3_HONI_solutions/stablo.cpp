#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define PB push_back
const int logo = 19;
const int MAXN = 5e5 + 7;

ll suma[MAXN], pf[MAXN], vl[MAXN], dep[MAXN], par[logo][MAXN];
vi g[MAXN];

int zadnji(int x, int y){
	for(int i=logo-1; i>=0; i--) if(dep[par[i][x]] > dep[y]) x = par[i][x];
	return x;
}

void solve(){
	int n, q;
	cin >> n >> q;
	for(int i=1; i<=n; i++) cin >> vl[i], pf[i] = vl[i];
	
	par[0][1] = 1;
	for(int i=2; i<=n; i++){
		cin >> par[0][i];
		dep[i] = dep[par[0][i]] + 1;
		suma[i] = vl[i] * dep[i];
	}
	
	for(int i=n; i>1; i--){
		suma[par[0][i]] += suma[i];
		pf[par[0][i]] += pf[i];
	}
	
	for(int j=1; j<logo; j++) for(int i=1; i<=n; i++) par[j][i] = par[j - 1][par[j - 1][i]];
	while(q--){
		int x, y, z;
		cin >> x >> y;
		
		ll ans = suma[y] - pf[y] * dep[y];
		if(par[0][x] != y){				
			z = zadnji(x, y);
			ans -= pf[x];
			ans -= vl[x] * (dep[x] - dep[y] - 1);
			ans += pf[z];
		}
		
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
