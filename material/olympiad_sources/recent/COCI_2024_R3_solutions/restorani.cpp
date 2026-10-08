#include <cstdio>
#include <vector>
#include <algorithm>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef pair < int, int > pii;
typedef long long ll;

const int N = 6e5 + 500;

int ispod[N];

struct stek{
	int dno, vrh;
	stek() { dno = -1; vrh = -1; }
	void push(int x) {
		if(vrh == -1) dno = x;
		ispod[x] = vrh;
		vrh = x;
	}
	void pop(){
		vrh = ispod[vrh];
		if(vrh == -1) dno = -1;
	}
	void ocisti(){
		dno = -1, vrh = -1;
	}
	void merge(stek &tko) {
		if(tko.vrh == -1) return;
		if(vrh == -1) {
			dno = tko.dno;
			vrh = tko.vrh;
		} else {
			ispod[tko.dno] = vrh;
			vrh = tko.vrh;
		}
		tko.ocisti();
	}
};

vector < int > zivi[N][2], v[N];
int cnt[N][2];
stek A[N], B[N];
int kraj[N], gdje[N], prv[N], nxt[N];

inline void link(int A, int B) {
	nxt[A] = B;
	prv[B] = A;
}

void ubaci_novi(stek &A, stek &B, pii novi) {
	if(A.vrh != -1) {
		int t = A.vrh; A.pop();
		link(novi.Y, t);
		kraj[novi.X] = kraj[t];
		A.push(novi.X);
	} else {
		link(kraj[B.vrh], novi.X);
		kraj[B.vrh] = novi.Y;
	}
}

ll sol;

pii dfs(int x, int lst) {
	for(int t : zivi[x][0]) A[x].push(t);
	for(int t : zivi[x][1]) B[x].push(t);
	pii smece = {-1, -1};
	for(int y : v[x]) {
		if(y == lst) continue;
		pii ret = dfs(y, x);
		if(cnt[y][0] + cnt[y][1]) 
			sol += 2LL * max(1, abs(cnt[y][0] - cnt[y][1]));
		cnt[x][0] += cnt[y][0];
		cnt[x][1] += cnt[y][1];
		if(ret.X != -1) {
			if(smece.X == -1) {
				smece = ret;
			} else {
				link(smece.Y, ret.X);
				smece.Y = ret.Y;
			}
		} else if(A[y].vrh != -1){
			A[x].merge(A[y]);
		} else {
			B[x].merge(B[y]);
		}
	}
	if(A[x].vrh == -1 && B[x].vrh == -1) return smece;
	if(smece.X != -1) {
		ubaci_novi(A[x], B[x], smece);
	}
	while(A[x].vrh != -1 && B[x].vrh != -1) {
		int a = A[x].vrh; A[x].pop();
		int b = B[x].vrh; B[x].pop();
		link(kraj[a], b);
		pii novi = {a, kraj[b]};
		if(A[x].vrh == -1 && B[x].vrh == -1) {
			return novi;
		} else {
			ubaci_novi(A[x], B[x], novi);
		}
	}
	return {-1, -1};
}



int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 0;i < 2 * k;i++) {
		scanf("%d", gdje + i);
		zivi[gdje[i]][i >= k].PB(i); 
		cnt[gdje[i]][i >= k]++;
		kraj[i] = i; 
	}
	for(int i = 1;i < n;i++) {
		int x, y; scanf("%d%d", &x, &y);
		v[x].PB(y), v[y].PB(x);
	}
	
	pii ret = dfs(1, 1);
	
	printf("%lld\n", sol);
	for(int i = 0, poc = ret.X;i < 2 * k;i++, poc = nxt[poc]) {
		if(poc < k) {
			printf("%d ", poc + 1);
		}
		else {
			printf("%d ", poc - k + 1);
		}
	}
	printf("\n");
	return 0;
}
