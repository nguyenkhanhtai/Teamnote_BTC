#include <bits/stdc++.h>
using namespace std;

const int logo = 30;
const int MAXN = 1e5 + 7;

int par[logo][MAXN], a[MAXN], ans[MAXN], ret;

void solve(){
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) cin >> par[0][i];
	
	for(int j = 1; j < logo; j++){
		for(int i = 1; i <= n; i++) par[j][i] = par[j - 1][par[j - 1][i]];
	}
	
	for(int i = 1; i <= n; i++){
		int j = i;
		for(int bit = 0; bit < logo; bit++){
			if(k & (1 << bit)) j = par[bit][j];
		}
		ans[j] += a[i];
	}
	
	for(int i = 1; i <= n; i++) ret = max(ret, ans[i]);
	
	cout << ret << "\n";
	for(int i = 1; i <= n; i++) if(ans[i] == ret) cout << i << " ";
	cout << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}

