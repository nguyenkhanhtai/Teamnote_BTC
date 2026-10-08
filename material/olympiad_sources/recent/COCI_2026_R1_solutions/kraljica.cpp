#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

#define PB push_back
#define PF push_front
#define PPF pop_front
#define X first
#define Y second

const int inf = 1e9 + 7;
const int MAXN = 1007;
const int MK = 10;
const int dx[] = {1, -1, 0, 0, -1, -1, 1, 1};
const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

string mat[MAXN];
int d[9][MAXN][MAXN], n, m;
ii p[10], skoci[MAXN][MAXN];

struct stanje{
	int pr, r, s;
};

deque<stanje> dq;

void bfs01(int r1, int s1){
	d[8][r1][s1] = 0;
	dq.PB({8, r1, s1});
	
	while(!dq.empty()){
		stanje c = dq.front();
		dq.PPF();
		
		for(int k=0; k<8; k++){
			int nr = c.r + dx[k], ns = c.s + dy[k];
			if(nr < 0 or ns < 0 or nr >= n or ns >= m) continue;
			if(mat[nr][ns] == '#') continue;
			int nd = d[c.pr][c.r][c.s] + (k != c.pr);
			
			if(d[k][nr][ns] <= nd) continue;
			d[k][nr][ns] = nd;
			if(nd) dq.PB({k, nr, ns});
			else dq.PF({k, nr, ns});
		}
		
		if(skoci[c.r][c.s].X != -1){
			int nr, ns, nd;
			tie(nr, ns) = skoci[c.r][c.s];
			nd = d[c.pr][c.r][c.s];
			
			if(d[8][nr][ns] <= nd) continue;
			d[8][nr][ns] = nd;
			dq.PF({8, nr, ns});
		}
	}
}

void solve(){
	int s1 = 0, s2 = 0, r1 = 0, r2 = 0;
	cin >> n >> m;
	
	for(int i = 0; i < 10; i++) p[i] = {-1, -1};
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			skoci[i][j] = {-1, -1};
		}
	}
	
	for(int i = 0; i < n; i++){
		cin >> mat[i];
		
		for(int j = 0; j < m; j++){
			int vl = mat[i][j] - '0';
			if(vl >= 1 and vl <= 9){
				if(p[vl].X == -1) p[vl] = {i, j};
				else{
					skoci[i][j] = p[vl];
					skoci[p[vl].X][p[vl].Y] = {i, j};
				}
			}
			
			if(mat[i][j] == 'S') r1 = i, s1 = j;
			if(mat[i][j] == 'E') r2 = i, s2 = j;
		}
	}
	
	for(int k = 0; k < 9; k++){	
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++) d[k][i][j] = inf;
		}
	}
	
	bfs01(r1, s1);
	
	int ans = inf;
	for(int k = 0; k < 9; k++) ans = min(ans, d[k][r2][s2]);
	
	if(ans == inf) cout << -1 << "\n";
	else cout << ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}
