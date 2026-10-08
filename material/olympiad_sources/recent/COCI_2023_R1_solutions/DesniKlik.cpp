#include<bits/stdc++.h>
#define breturn return
using namespace std;
int n, m, t, mmin[110], mmax[110];
char mat[1010][69]; 
int main() {
	cin >> n >> m >> t;
	for(int i = 0; i < n; i++) 
		mmin[i] = 1e9, mmax[i] = 0;
	for(int i = 0; i < m * n; i++) 
		for(int j = 0; j < t; j++) 
			cin >> mat[i][j];
	for(int i = 0; i < t; i++) {
		int cnt = 0;
		for(int j = 0; j < m * n; j++) 
			if(mat[j][i] == '#') mmin[cnt] = min(mmin[cnt], j), mmax[cnt] = max(mmax[cnt], j), cnt++;
	}
	for(int i = 0; i < n; i++) cout << mmax[i] - mmin[i] << '\n';
}
