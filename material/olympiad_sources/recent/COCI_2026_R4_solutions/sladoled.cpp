#include <bits/stdc++.h>
using namespace std;

const int MV = 5e4 + 1;
const int N = 102;

bitset<MV> b[N];
bool jedan[N];

void solve(){
	int n, q;
	cin >> n >> q;
	for(int i=1; i<=n; i++) b[i] = 1;
	
	while(q--){
		int a, c;
		cin >> a >> c;
		
		if(c == 1) jedan[a] = 1;
		else {
			int tr = c;	
			while(!b[a][tr] and tr < MV){
				b[a] |= (b[a] << tr);
				tr *= 2;
			}
		}
		
		if(jedan[a]) cout << MV - 1 << "\n";
		else cout << b[a].count() - 1 << "\n";
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}

