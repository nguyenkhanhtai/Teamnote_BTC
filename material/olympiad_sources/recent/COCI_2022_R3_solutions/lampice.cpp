#include <iostream>
#include <cstdio>

using namespace std;

const int N=55;

int n, k;
int p[N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i=0; i<n; ++i) scanf("%d", &p[i]);

    for (int l=0; l<n; ++l) {
        for (int r=l; r<n; ++r) {
            int ok=1, d=r-l+1;
            for (int i=1; i<k && ok; ++i) {
                for (int j=l; j<=r; ++j) {
                    if (j+i*d>=n || p[j+i*d]!=p[j]) {
                        ok=0;
                        break;
                    }
                }
            }
            if (ok) {
                printf("%d\n", r-l+1);
                for (int i=l; i<=r; ++i) printf("%d ", p[i]);
                return 0;
            }
        }
    }
    printf("-1");
    return 0;
}
