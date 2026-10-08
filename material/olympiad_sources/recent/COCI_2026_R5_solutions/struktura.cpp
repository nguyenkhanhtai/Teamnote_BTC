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

const int mod = 1e9 + 7;
const int inf = 1e9 + 7;
const ll INF = (ll)1e18 + 7;
const int logo = 20;
const int MAXN = 1e6 + 7;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int mul(ll a, ll b){
	return (a * b) % mod;
}

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int sub(int a, int b){
	a -= b;
	if(a < 0) a += mod;
	return a;
}

int exp(int b, ll e){
	int ret = 1;
	for(; e; e /= 2, b = mul(b, b)) if(e & 1) ret = mul(ret, b);
	return ret;
}

int divide(int a, int b){
	return mul(a, exp(b, mod - 2));
}

struct mat{
	int a[2][2];
	
	mat() {
		a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;
	}
	
	mat(int x) {
		if(x == 0) {
			//jedinicna
			a[0][0] = a[1][1] = 1;
			a[0][1] = a[1][0] = 0;
		} else if(x == 1) {
			//prijelaz
			a[0][0] = 0;
			a[1][1] = a[0][1] = a[1][0] = 1;
		} else {
			//pocetna
			a[0][1] = 1;
			a[0][0] = a[1][1] = a[1][0] = 0;
		}
	}
};

void mul(mat &a, mat b, mat c) {
	a = mat();
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			for(int k=0; k<2; k++) {
				a.a[i][j] = add(a.a[i][j], mul(b.a[i][k], c.a[k][j]));
			}
		}
	}
}

int fib(int n){
	mat ret(0), b(1);
	for(; n; n /= 2, mul(b, b, b)) {
		if(n & 1) mul(ret, ret, b);
	}
	
	b = mat(2);
	mul(b, b, ret);
	return b.a[0][1];
}

void solve(){
	int n, k;
	cin >> n >> k;
	if(k < n) {
		cout << 0 << "\n";
		return;
	}
	
	cout << divide(fib(n), exp(k, n)) << "\n";
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

