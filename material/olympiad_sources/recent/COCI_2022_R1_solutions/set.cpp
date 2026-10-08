#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 600005;

int n, k;
int cnt[MAXN];

struct Z_adjoin_w {
    llint x, y;

    Z_adjoin_w () {
        x = y = 0;
    }

    Z_adjoin_w (llint _x, llint _y) {
        x = _x; y = _y;
    }
} P[MAXN];

const Z_adjoin_w w = Z_adjoin_w(0, 1);
const Z_adjoin_w w2 = Z_adjoin_w(-1, -1);

Z_adjoin_w add (Z_adjoin_w a, Z_adjoin_w b) {
    return Z_adjoin_w(a.x + b.x, a.y + b.y);
}

Z_adjoin_w div_by_3 (Z_adjoin_w a) {
    return Z_adjoin_w(a.x / 3, a.y / 3);
}

Z_adjoin_w mul (Z_adjoin_w a, Z_adjoin_w b) {
    return Z_adjoin_w(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x - a.y * b.y);
}

void modified_FWHT (bool invert) {
    int siz = 1;
    for (int i = 0; i < k; i++) siz *= 3;

    for (int len = 1; len < siz; len *= 3) {
        for (int i = 0; i < siz; i += 3 * len) {
            for (int j = 0; j < len; j++) {
                Z_adjoin_w a = P[i + j + len * 0];
                Z_adjoin_w b = P[i + j + len * 1];
                Z_adjoin_w c = P[i + j + len * 2];
                if (invert == 0) {
                    P[i + j + len * 0] = add(a, add(b, c));
                    P[i + j + len * 1] = add(a, add(mul(b, w), mul(c, w2)));
                    P[i + j + len * 2] = add(a, add(mul(b, w2), mul(c, w)));
                } else {
                    P[i + j + len * 0] = div_by_3(add(a, add(b, c)));
                    P[i + j + len * 1] = div_by_3(add(a, add(mul(b, w2), mul(c, w))));
                    P[i + j + len * 2] = div_by_3(add(a, add(mul(b, w), mul(c, w2))));
                }
            }
        }
    }
}

void calc () {
    int siz = 1;
    for (int i = 0; i < k; i++) siz *= 3;

    modified_FWHT(0);
    for (int i = 0; i < siz; i++) {
        P[i] = mul(P[i], P[i]);
    }
    modified_FWHT(1);

    llint sol = 0;
    for (int i = 0; i < siz; i++) {
        int val = i, comp = 0, pot = 1;
        for (int j = 0; j < k; j++) {
            comp += (3 - val % 3) % 3 * pot;
            val /= 3;
            pot *= 3;
        }
        sol += cnt[i] * (P[comp].x - 1);
    }
    cout << sol / 6;
}

int main () {
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);
    scanf("%d%d", &n, &k);
    getchar();
    for (int i = 0; i < n; i++) {

        int val = 0;
        for (int j = 0; j < k; j++) {
            char c = getchar();
            val = val * 3 + c - '1';
        }
        getchar();

        P[val] = Z_adjoin_w(1, 0);
        cnt[val]++;
    }
    calc();
    return 0;
}
