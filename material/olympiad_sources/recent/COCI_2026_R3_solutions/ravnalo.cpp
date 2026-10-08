#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 7;

int a[MAXN], b[MAXN], g[MAXN];

ll dijeli(ll visina, ll br, ll naz){
  return visina * naz / br;
}

ll presjek(int l, int r){
  if(l == 0) return 0;
  
  ll br = lcm<ll>(a[l] / g[l], a[r] / g[r]);
  ll naz = gcd<ll>(b[l] / g[l], b[r] / g[r]);
  
  return dijeli(min(a[l], a[r]), br, naz) + 1;
}


void solve() {
  int n;
  cin >> n;
  
  for(int i=1; i<=n; i++) cin >> a[i];
  for(int i=1; i<=n; i++) {
    cin >> b[i];
    g[i] = __gcd(a[i], b[i]);
  }
  
  ll ans = n + 1;
  for(int i=1; i<=n; i++){
    ans += b[i] + 1;
    ans -= presjek(i - 1, i);
  }
  cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}

