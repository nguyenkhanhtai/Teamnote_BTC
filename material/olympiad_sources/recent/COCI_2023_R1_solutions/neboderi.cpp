#include <cstdio>
#include <vector>
#include <algorithm>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef long long ll;
typedef pair < int, int > pii;

const int N = 1e6 + 500;

int n, k;
ll P[N];
vector < pii > r;

int main(){
	ll sol = 0;
	scanf("%d%d", &n, &k);
	for(int i = 0;i < n;i++){
		int x; scanf("%d", &x);
		P[i] = (i ? P[i - 1] : 0LL) + x;
		for(pii &tmp : r)
			tmp.Y = __gcd(tmp.Y, x);
		r.PB({i, x});
		vector < pii > nr;
		for(int i = 0;i < (int)r.size();i++)
			if(!i || r[i - 1].Y != r[i].Y)
				nr.PB(r[i]);
		r = nr;
		for(pii &tmp : r)
			if(i - tmp.X + 1 >= k)
				sol = max(sol, (ll)tmp.Y * (P[i] - (tmp.X ? P[tmp.X - 1] : 0LL)));
	}
	printf("%lld\n", sol);
	return 0;
}
