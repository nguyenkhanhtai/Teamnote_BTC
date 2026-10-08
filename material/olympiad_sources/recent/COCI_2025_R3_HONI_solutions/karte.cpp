#include <bits/stdc++.h>
using namespace std;

int msk[30], n, m, x, y;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m >> x >> y;
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		for(int j=0; j<m; j++){
			if(s[j] == '1') msk[i] |= (1 << j);
		}
	}
	
	int ans = 0;
	for(int j=0; j<(1 << m); j++){
		int cur = -(__builtin_popcount(j) * y);
		for(int i=0; i<n; i++){
			int vl = __builtin_popcount(msk[i] & j);
			if(vl > x) cur += vl - x;
		}
		ans = max(ans, cur);
	}
	cout << ans << "\n";
	return 0;
}

