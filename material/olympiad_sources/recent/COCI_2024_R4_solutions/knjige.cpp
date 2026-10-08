#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 5;

ll pref[MAXN];

int main() {
  int n, t, a, b;
  scanf("%d%d%d%d", &n, &t, &a, &b);
  int l;
  for(int i = 0; i < n; i++) {
    scanf("%d", &l);
    pref[i + 1] = pref[i] + l;
  }
  ll sol=0;
  int y;
  for(int x = 0; x < n; x++) {
    if(x * b > t) {
      break;
    }
    y = (t - x * b) / a;
    sol = max(sol, pref[min(y + x, n)] - pref[x]);
  }
  printf("%lld\n", sol);
  return 0;
}

