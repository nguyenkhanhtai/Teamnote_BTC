#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vii;

#define PB push_back
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

const int MAXN = 3e5 + 7;

int n, k;
vii ev;
multiset<int> s;
int le[MAXN], ri[MAXN];

void solve(){
	cin >> n >> k;
	for(int i=1; i<=n; i++){
		cin >> le[i] >> ri[i];
		ev.PB({le[i], i});
		ev.PB({ri[i], -i});
	}
	sort(all(ev));
	
	int ans = 0;
	for(auto &x : ev){
		if(x.Y > 0){
			s.insert(ri[x.Y]);
			if((int)s.size() > k) s.erase(s.begin());
		}else if(*s.begin() == x.X) s.erase(s.begin());
		
		if((int)s.size() == k) ans = max(ans, *s.begin() - x.X);
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

