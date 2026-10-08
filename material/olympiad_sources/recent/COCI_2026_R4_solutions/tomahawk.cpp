#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<char, int> pi;

#define all(x) (x).begin(), (x).end()
#define X first
#define Y second

int n;
vector<pi> qs;


ll f(int r, int s) {
	ll ret = 0;
	for(auto &x : qs) {
		if(x.X == 'L') {
			int ud = s - 1;
			ret += max(0, x.Y - ud);
		}else if(x.X == 'R') {
			int ud = n - s;
			ret += max(0, x.Y - ud);
		}else{
			int ud = n - r;
			ret += max(0, x.Y - ud);
		}
	}
	return ret;
}

void solve(){
	int q;
	cin >> n >> q;
	
	qs.resize(q);
	for(auto &x : qs) cin >> x.X >> x.Y;
	
	ll najvise = max(f(n, 1), f(n, n)); 
	ll najmanje = 0;
	if(n % 2) {
		int sred = (n + 1) / 2;
		najmanje = min({f(1, sred - 1), f(1, sred), f(1, sred + 1)});
	}else najmanje = min(f(1, n / 2), f(1, n / 2 + 1));
	
	//cout << najvise << " " << najmanje << "\n";
	cout << najvise - najmanje << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}

