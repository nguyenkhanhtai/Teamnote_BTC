#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using vl=vector<ll>;
mt19937 rng(3289472394);

const int N=3010;
int m,n,k;
ll pr[N][N];

int brpar(vl v)
{
	sort(v.begin(),v.end());
	int cn=1,an=0;
	for (int i=1;i<(int)v.size();++i)
	{
		if (v[i]!=v[i-1]) cn=0;
		an+=cn;
		++cn;
	}
	return an;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	uniform_int_distribution<ll> dis(0,(1ll<<60)-1);
	cin>>n>>m>>k;
	++n;
	++m;
	for (int i=0;i<k;++i)
	{
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		++x1;
		++y1;
		++x2;
		++y2;
		ll u=dis(rng);
		pr[x1][y1]^=u;
		pr[x2][y2]^=u;
	}
	for (int i=0;i<n;++i) for (int j=0;j<m;++j) pr[i+1][j+1]^=pr[i][j]^pr[i+1][j]^pr[i][j+1];
	ll an=0;
	for (int l=0;l<n;++l) for (int r=l+2;r<=n;++r)
	{
		vl v(m+1);
		for (int i=0;i<=m;++i) v[i]=pr[l][i]^pr[r][i];
		an+=brpar(v);
		for (int i=0;i<m;++i) an-=(v[i]^v[i+1])==0;
	}
	cout<<an<<endl;
}




