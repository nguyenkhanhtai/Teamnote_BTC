#include <bits/stdc++.h>

using namespace std;

int l, q;

void alojzije() {
  int a;
  scanf("%d", &a);

  vector<int> ret;
  int curr = 0;
  for (int i = 18; i >= 0; --i) {
    if (a & (1 << i)) {
      curr |= 1 << i;
      ret.emplace_back(curr);
    }
  }

  printf("%d", (int)ret.size());
  for (int x : ret) printf(" %d", x);
  printf("\n");
}

void benjamin() {
  int b;
  scanf("%d", &b);

  vector<int> ret;
  int curr = 0;
  for (int i = 18; i >= 0; --i) {
    if (b & (1 << i))
      curr |= 1 << i;
    else
      ret.emplace_back(curr | (1 << i));
  }

  printf("%d", (int)ret.size());
  for (int x : ret) printf(" %d", x);
  printf("\n");
}

void cecilija() {
  int l, x;
  scanf("%d", &l);
  for (int i = 0; i < l; ++i)
    scanf("%d", &x);
  if (x != 1)
    printf("A\n");
  else
    printf("B\n");
}

int main(void) {
  scanf("%d%d", &l, &q);
  while (q--) {
    char t[10];
    scanf("%s", t);
    if (t[0] == 'a') alojzije();
    if (t[0] == 'b') benjamin();
    if (t[0] == 'c') cecilija();
  }
  return 0;
}
