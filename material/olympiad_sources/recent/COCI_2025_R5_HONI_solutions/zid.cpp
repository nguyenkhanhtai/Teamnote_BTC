#include <cstdio>

using namespace std;

typedef long long ll;

const int N = 505;

int A[N][N], n, m;
int cnt[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < m;j++) {
			char c; scanf(" %c", &c);
			A[i][j] = (c == '#');
		}
	}
	ll sol = 0;
	for(int l = 0;l < m;l++) {
		for(int i = 0;i < n;i++) cnt[i] = 0;
		for(int r = l;r < m;r++) {
			for(int i = 0;i < n;i++) cnt[i] += A[i][r];
			int praz = 0, last = -1;
			for(int i = 0;i < n;i++) {
				if(!cnt[i]) {
					sol += ++praz;
				} else {
					sol += (last + 1) * (praz + 1);
					if(cnt[i] == 1)
						last = praz;
					else
						last = -1;
					praz = 0;
				}
			}
			sol += (last + 1) * (praz + 1);
		}
	}	
	printf("%lld\n", sol);
	return 0;
}
