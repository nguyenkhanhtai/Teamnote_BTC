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
#define rep(i, a, b) for(int i=a; i<b; i++)
#define sz(x) (int)(x).size()

const int mod = 1e9 + 7; //998244353;
const int inf = 1e9 + 7;
const ll INF = (ll)1e18 + 7;
const int logo = 20;
const int MAXN = 90;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, -1, 1, 0};

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	for (int e : g[di])
	if (!vis[e] && find(e, g, btoa, vis)) {
		btoa[e] = di;
		return 1;
	}
	return 0;
}

int dfsMatching(vector<vi>& g, vi& btoa) {
	vi vis;
	rep(i,0,sz(g)) {
		vis.assign(sz(btoa), 0);
		for (int j : g[i]) if (find(j, g, btoa, vis)) {
			btoa[j] = i;
			break;
		}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}

int id[MAXN][MAXN], mat[MAXN][MAXN], n, m, nodes[2];
vector<vi> g;

void prin(){
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) cout << mat[i][j];
		cout << "\n";
	}
}

void add_edge(int i, int j, int ni, int nj) {
	int lef = id[i][j], rig = id[ni][nj];
	if((i + j) % 2) swap(lef, rig);
	g[lef].PB(rig);
	//cout << i << " " << j << " " << ni << " " << nj << " " << lef << " " << rig << "\n";
}

void solve(){
	cin >> n >> m;
	
	int cnt2 = 0;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			char t;
			cin >> t;
			mat[i][j] = (t - '0');
			cnt2 += (mat[i][j] == 2);
		}
	}
	
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(mat[i][j]) continue;
			
			bool fl = 0;
			for(int k=0; k<4; k++) {
				int ni = i + dx[k], nj = j + dy[k];
				fl |= (mat[ni][nj] == 2);
			}
			
			mat[i][j] = fl;
		}
	}
	
	int cvor = 0;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(mat[i][j]) continue;
			
			int ja = (i + j) % 2;
			id[i][j] = nodes[ja]++;
			if(ja == 0) g.PB({});
			cvor++;
			
			for(int k=0; k<2; k++) {
				int ni = i + dx[k], nj = j + dy[k];
				if(ni < 1 or nj < 1 or ni > n or nj > m) continue;
				if(mat[ni][nj]) continue;
				add_edge(i, j, ni, nj);
			}
		}
	}
	
	vi ostali(nodes[1], -1);
	cout << cnt2 + cvor - dfsMatching(g, ostali) << "\n";
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

