// Author : Paweł Parys
// Task   : GCD
// Memory : N
// Time   : <= (R+1)^N * N and <= N^(R+1), but actually smaller; in particular for R=1 it checks in O(N) each step only before finding gcd=1, and there are at most 8 such steps
// Solv   : For consecutive R add precisely R cookies in all possible ways, and checking if the gcd became 1

#include <bits/stdc++.h>
using namespace std;

int N, R;
vector<int> tab;

void check() {
    int d = tab[N-1];
    for(int a = 0; a < N - 1; ++a) {
        d = gcd(tab[a], d);
        if (d==1) {
            printf("%d\n", R);
            exit(0);
        }
    }
}

void start(int pos, int add) {
    if (add==0) {
        check();
        return;
    }
    if (pos==N)
        return;
    tab[pos] += add+1;
    for(int rem = 0; rem <= add; ++rem) {
        --tab[pos];
        start(pos+1, rem);
    }
}

int main() {
    scanf("%d", &N);
    tab.resize(N);
    for(int a = 0; a < N; ++a)
        scanf("%d", &tab[a]);
    for (R = 0; ; R++)
        start(0, R);
}
