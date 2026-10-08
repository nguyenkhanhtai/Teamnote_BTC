#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define PB push_back

using namespace std;

typedef long long ll;

const int N = 505;
const int D = 300;
const int MOD = 998244353;

inline int add(int A, int B){
    if(A + B >= MOD) 
        return A + B - MOD;
    return A + B;
}

int n, k, m, dp[N][N][D], A[N][N], g[D][D];
vector < int > d;

ll lgcd(ll A, ll B){
    if(!B) return A;
    return lgcd(B, A % B);
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1;i <= k;i++) {
        if(!(k % i)) d.PB(i);
    }
    m = (int)d.size();
    for(int i = 0;i < m;i++)    
        for(int j = 0;j < m;j++) 
            g[i][j] = lower_bound(d.begin(), d.end(), lgcd((ll)d[i] * d[j], k)) - d.begin();
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            int x; scanf("%d", &x);
            if(x == -1) A[i][j] = -1;
            else A[i][j] = lower_bound(d.begin(), d.end(), lgcd(x, k)) - d.begin();
        }
    }
    dp[0][0][A[0][0]] = 1;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(A[i][j] < 0) continue;
            if(i) for(int k = 0;k < m;k++) 
                dp[i][j][g[k][A[i][j]]] = add(dp[i - 1][j][k], dp[i][j][g[k][A[i][j]]]);
            if(j) for(int k = 0;k < m;k++) 
                dp[i][j][g[k][A[i][j]]] = add(dp[i][j - 1][k], dp[i][j][g[k][A[i][j]]]);
        }
    }
    int sve = 0;
    for(int i = 0;i < m;i++) sve = add(sve, dp[n - 1][n - 1][i]);
    printf("%d\n", dp[n - 1][n - 1][m - 1]);
    return 0;
}
