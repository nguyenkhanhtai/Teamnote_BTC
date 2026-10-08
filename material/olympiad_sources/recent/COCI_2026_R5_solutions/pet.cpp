#include <bits/stdc++.h>
using namespace std;

typedef __int128 ij;

#define PB push_back
#define PPB pop_back

const int MAXN = 2010;

bool mat[MAXN][MAXN];
bitset<MAXN> b[MAXN], help;
int red[MAXN], stup[MAXN], n, m;
ij ans;

int sumar[MAXN], sumas[MAXN];

ij f(ij x) {
	return x * (x - 1) / 2 * 8;
}

void prin() {
	vector<int> vec;
	while(ans) vec.PB(ans % 10), ans /= 10;
	if(vec.empty()) cout << 0 << "\n";
	else{
		while(vec.size()) cout << vec.back(), vec.PPB();
		cout << "\n";
	}
}

void solve(){
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++) {
			char t;
			cin >> t;
			mat[i][j] = (t == '1');
			b[i][j] = (t == '1');
			red[i] += mat[i][j];
			stup[j] += mat[i][j];
		}
	}
	
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(!mat[i][j]) continue;
			sumar[i] += stup[j] - 1;
			sumas[j] += red[i] - 1;
		}
	}
	
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(!mat[i][j]) continue;
			int redak = sumar[i] - (stup[j] - 1);
			int stupac = sumas[j] - (red[i] - 1);
			ans += (ij)redak * stupac * 2;
		}
	}
	
	for(int i=1; i<=n; i++) {
		for(int j=i+1; j<=n; j++){
			int zasad = (b[i] & b[j]).count();
			ans -= f(zasad);
		}
	}
	
	prin();
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}
