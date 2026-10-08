#include <bits/stdc++.h>
using namespace std;

bool rima(string a, string b, int k)
{
    while (k>0)
    {
        if (a[(int)a.size()-k]!=b[(int)b.size()-k])
            return false;
        k=k-1;
    }

    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // parna (aabb)
    // unakrsna (abab)
    // obgrljena (abba)

    int n, m, k;
    cin >> n >> m >> k;
    string s[n][m];
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            cin >> s[i][j];

    int parna=0, unakrsna=0, obgrljena=0;

    for (int i=0; i<n; i=i+4)
    {
        if ((int)s[i][m-1].size()<k || (int)s[i+1][m-1].size()<k || (int)s[i+2][m-1].size()<k || (int)s[i+3][m-1].size()<k)
            continue;

        if (rima(s[i][m-1], s[i+1][m-1], k) && rima(s[i+2][m-1], s[i+3][m-1], k))
            parna=parna+1;
        if (rima(s[i][m-1], s[i+2][m-1], k) && rima(s[i+1][m-1], s[i+3][m-1], k))
            unakrsna=unakrsna+1;
        if (rima(s[i][m-1], s[i+3][m-1], k) && rima(s[i+1][m-1], s[i+2][m-1], k))
            obgrljena=obgrljena+1;
    }

    cout << parna << ' ' << unakrsna << ' ' << obgrljena << '\n';

    return 0;
}
