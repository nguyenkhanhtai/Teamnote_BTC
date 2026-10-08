#include <bits/stdc++.h>

using namespace std;

const int MAXX=10000000;

int nepdj[MAXX+10];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int i=1;i<=MAXX;i+=2) for (int j=i;j<=MAXX;j+=i) ++nepdj[j];
	int t;
	cin>>t;
	while (t--)
	{
		int x,y;
		cin>>x>>y;
		int g=gcd(x,y);
		if (g==0)
		{
			cout<<"0\n";
			continue;
		}
		if ((x/g)%2 && (y/g)%2)
		{
			cout<<"0\n";
			continue;
		}
		cout<<nepdj[g]<<'\n';
	}
}
