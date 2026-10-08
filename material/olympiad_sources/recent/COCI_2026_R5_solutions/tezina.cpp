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
const int logo = 20;
const int MAXN = 1e6 + 7;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct interval{
	int l, r, vl;
};

int a[MAXN], n, b;
ll ans;

void dodaj(int l, int r, int y, int x) {
	ll vrijednost = (ll)(x + 2) * y;
	vrijednost = min(vrijednost, (ll)1e8);
	if(l > b) return;
	r = min(r, b);
	ans += vrijednost * (r - l + 1);
}

void rastavi(int x){
    int y = 1;
    while (y <= x) {
        int k = x / y;
        int L = y;
        int R = (k == 0) ? x : x / k;
        dodaj(L, R, k, x);
        y = R + 1;
    }
}

void solve(){
	cin >> n >> b;
	
	for(int i=1; i<=n; i++){
		int x;
		cin >> x;
		rastavi(x);	
	}
	cout << ans << "\n";
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

