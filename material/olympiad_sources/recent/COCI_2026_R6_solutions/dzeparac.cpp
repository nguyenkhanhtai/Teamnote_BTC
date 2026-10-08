#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;

int mul(ll a, ll b){
	return (a * b) % mod;
}

int exp(int b, ll e){
	int ret = 1;
	for(; e; e /= 2, b = mul(b, b)) if(e & 1) ret = mul(ret, b);
	return ret;
}

void solve(){
	ll n;
	cin >> n;
	cout << exp(2, n / 2) << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}

