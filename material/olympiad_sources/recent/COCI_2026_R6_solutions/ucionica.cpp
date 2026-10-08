#include <bits/stdc++.h>
using namespace std;

const int MAXN=2000;

int a[MAXN][MAXN], pom[MAXN][MAXN];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    int h[k];
    for (int i=0; i<k; i++)
        cin >> h[i];
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            cin >> a[i][j];

    sort(h, h+k);
    for (int j=0; j<m; j++)
    {
        int stupacmax=a[0][j], t=0;
        for (int i=0; i<n; i++)
        {
            stupacmax=max(stupacmax, a[i][j]);
            while (t<k && h[t]<=stupacmax)
                t=t+1;
            pom[i][j]=k-t;
        }
    }

    long long suma[n]={0};
    for (int i=0; i<n; i++)
        for (int j=0; j<k; j++)
            suma[i]=suma[i]+a[i][j];

    int total=0;

    for (int j=0; j<=m-k; j++)
    {
        if (j>0)
        {
            for (int i=0; i<n; i++)
                suma[i]=suma[i]-a[i][j-1]+a[i][j+k-1];
        }

        int l=0, r=n-1;
        while (l<=r)
        {
            int i=(l+r)/2;
            int count[k+1]={0};
            for (int t=0; t<k; t++)
                count[pom[i][j+t]]=count[pom[i][j+t]]+1;

            bool ok=true;
            int veci=0;
            for (int t=k; t>=1; t--)
            {
                veci=veci+count[t];
                if (veci==0)
                {
                    ok=false;
                    break;
                }
                veci=veci-1;
            }

            if (ok)
                l=i+1;
            else
                r=i-1;
        }

        if (suma[0]==0)
            total=total+1;
        for (int i=1; i<n; i++)
            if (suma[i]==0 && i-1<=l-1)
                total=total+1;
    }

    cout << total << '\n';

    return 0;
}
