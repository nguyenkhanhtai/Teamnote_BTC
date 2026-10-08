#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define PB push_back
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

const ll INF = 4e18;
const int MAXN = 10007;

vpll d;
ll dp[2][MAXN], ndp[2][MAXN];

ll cost(int l, int r){
	return d[r].X - d[l].X;
}

void chmin(ll &a, ll b){
	if(b < a) a = b;
}

void chmax(ll &a, ll b){
	if(b > a) a = b;
}

void solve(){
	int n;
	cin >> n;
	for(int i=1; i<=n; i++){
		ll a, b, w;
		cin >> a >> b >> w;
		d.PB({a, w});
		d.PB({b, w});
	}
	sort(all(d));
	n = d.size();
	
	for(int i=0; i<n; i++) dp[0][i] = dp[1][i] = INF;
	
	dp[0][0] = max(d[0].X, d[0].Y);
	dp[1][0] = max(d[n - 1].X, d[n - 1].Y);
	
	ll ans = INF;
	for(int len=n-2; len>=0; len--){
		for(int i=0; i<n; i++) ndp[0][i] = ndp[1][i] = INF;	
		for(int i=0; i+len<n; i++){
			int j = i + len;
			if(i){
				//[i - 1, j] -> [i, j]
				chmin(ndp[0][i], dp[0][i - 1] + cost(i - 1, i));
				chmin(ndp[1][i], dp[0][i - 1] + cost(i - 1, j));
			}
			
			if(j != n - 1){
				//[i, j + 1] -> [i, j]
				chmin(ndp[0][i], dp[1][i] + cost(i, j + 1));
				chmin(ndp[1][i], dp[1][i] + cost(j, j + 1));
			}
			
			chmax(ndp[0][i], d[i].Y);
			chmax(ndp[1][i], d[j].Y);
			if(len == 0) chmin(ans, ndp[0][i]);
		}
		
		for(int i=0; i<n; i++){
			dp[0][i] = ndp[0][i];
			dp[1][i] = ndp[1][i];
		}
	}
	
	cout << ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}
