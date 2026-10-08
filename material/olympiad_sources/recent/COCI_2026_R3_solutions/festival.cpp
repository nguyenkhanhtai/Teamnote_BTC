#include <bits/stdc++.h>
using namespace std;

const int MOD=1e9+7, MAXN=5000;

int memo[MAXN+1][MAXN+1];

int dp(int n, int k)
{
    if (memo[n][k]!=-1)
        return memo[n][k];
    if (n==0 && k==0)
        return memo[n][k]=1;
    if (n==0 || k==0)
        return memo[n][k]=0;

    return memo[n][k]=(dp(n-1, k-1)+(long long)(n-1)*dp(n-1, k)%MOD)%MOD;
}

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i=0; i<=n; i++)
        for (int j=0; j<=n; j++)
            memo[i][j]=-1;
    cout << dp(n, k) << '\n';

    return 0;
}
