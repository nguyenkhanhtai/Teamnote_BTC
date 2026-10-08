#include <cstdio>

typedef long long ll;

const int maxn = 1e5 + 5;

int n, t, s, k;
ll sol[maxn];
int a[maxn];
ll suff[maxn];
int br[maxn];

inline ll dizi_rucno(int h) {
  return (suff[h] - (ll) h * br[h]) * t;
}

int main() {
  scanf("%d%d%d%d", &n, &t, &s, &k);
  int x;
  for(int i = 0; i < n; i++) {
    scanf("%d", &x);
    a[x]++;
  }
  
  for(int i = maxn - 2; i >= 0; i--) {
    suff[i] = suff[i + 1] + a[i] * i;
    br[i] = br[i + 1] + a[i];
  }

  int r = a[0];
  int kol = 0;
  ll paralelno = 0;
  for(int i = maxn - 1; i >= 0; i--) {
    if(paralelno + dizi_rucno(kol + i) > paralelno + s + (ll) k * r + dizi_rucno(kol + i + 1)) {
      paralelno += s + (ll) k * r;
      kol++;
      r += a[kol];
    }
    sol[i] = paralelno + dizi_rucno(kol + i);
  }

  int q;
  scanf("%d", &q);
  for(int i = 0; i < q; i++) {
    scanf("%d", &x);
    printf("%lld ", sol[x]);
  }
  printf("\n");
  return 0;
}

