#include <bits/stdc++.h>
#define x first
#define y second
#define pii pair<int,int>
#define pb push_back
#define vi vector<int>
#define vl vector<ll>
#define all(a) begin(a),end(a)

using namespace std;

bool prime(int x)
{
	if (x==1) return 0;
	for (int i=2;i*i<=x;++i) if (x%i==0) return 0;
	return 1;
}

using ll=long long;
const int N=600010,PRI=6;
int t,n,m,a[N],b[N],c[N];
ll dis1[N],dis2[N];
bool bio[N];
vector<pii> c1[N],c2[N];
vi ch1[N],ch2[N],rch1[N],rch2[N];
int cn11[PRI+2][N],cn21[PRI+2][N],cn1n[PRI+2][N],cn2n[PRI+2][N];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	mt19937 rng(29834729);
	uniform_int_distribution<int> dis(1e8,1e9);
	vi primes;
	for (int i=0;i<PRI;++i)
	{
		int x=dis(rng);
		while (!prime(x)) x=dis(rng);
		primes.pb(x);
	}
	cin>>t;
	while (t--)
	{
		cin>>n>>m;
		for (int i=0;i<2*n;++i)
		{
			c1[i].clear();
			c2[i].clear();
			ch1[i].clear();
			ch2[i].clear();
			rch1[i].clear();
			rch2[i].clear();
			bio[i]=0;
			for (int j=0;j<PRI;++j) cn11[j][i]=0,cn21[j][i]=0,cn1n[j][i]=0,cn2n[j][i]=0;
		}
		for (int i=0;i<m;++i)
		{
			cin>>a[i]>>b[i]>>c[i];
			--a[i];
			--b[i];
			c1[a[i]].pb({b[i],c[i]});
			c1[b[i]].pb({a[i],c[i]});
			c2[a[i]*2].pb({b[i]*2+c[i]%2,c[i]});
			c2[a[i]*2+1].pb({b[i]*2+1-c[i]%2,c[i]});
			c2[b[i]*2].pb({a[i]*2+c[i]%2,c[i]});
			c2[b[i]*2+1].pb({a[i]*2+1-c[i]%2,c[i]});
		}
		priority_queue<pair<ll,int>> pq;
		pq.push({0,0});
		while (pq.size())
		{
			ll di=pq.top().x;
			int i=pq.top().y;
			pq.pop();
			if (bio[i]) continue;
			dis1[i]=-di;
			bio[i]=1;
			for (auto x: c1[i]) pq.push({di-x.y,x.x});
		}
		for (int i=0;i<2*n;++i) bio[i]=0;
		pq.push({0,0});
		while (pq.size())
		{
			ll di=pq.top().x;
			int i=pq.top().y;
			pq.pop();
			if (bio[i]) continue;
			dis2[i]=-di;
			bio[i]=1;
			for (auto x: c2[i]) pq.push({di-x.y,x.x});
		}
		vector<pair<ll,int>> or1,or2;
		for (int i=0;i<n;++i)
		{
			or1.pb({dis1[i],i});
			for (auto x: c1[i]) if (dis1[x.x]==dis1[i]+x.y)
			{
				ch1[i].pb(x.x);
				rch1[x.x].pb(i);
			}
		}
		for (int i=0;i<2*n;++i)
		{
			or2.pb({dis2[i],i});
			for (auto x: c2[i]) if (dis2[x.x]==dis2[i]+x.y)
			{
				ch2[i].pb(x.x);
				rch2[x.x].pb(i);
			}
		}
		sort(all(or1));
		sort(all(or2));
		vi o1,o2;
		for (auto x: or1) o1.pb(x.y);
		for (auto x: or2) o2.pb(x.y);
		for (int j=0;j<PRI;++j) cn11[j][0]=1;
		for (auto i: o1)
		{
			for (int j=0;j<PRI;++j) for (auto x: ch1[i])
			{
				cn11[j][x]+=cn11[j][i];
				if (cn11[j][x]>=primes[j]) cn11[j][x]-=primes[j];
			}
		}
		reverse(all(o1));
		for (int j=0;j<PRI;++j) cn1n[j][n-1]=1;
		for (auto i: o1)
		{
			for (int j=0;j<PRI;++j) for (auto x: rch1[i])
			{
				cn1n[j][x]+=cn1n[j][i];
				if (cn1n[j][x]>=primes[j]) cn1n[j][x]-=primes[j];
			}
		}
		reverse(all(o1));
		
		for (int j=0;j<PRI;++j) cn21[j][0]=1;
		for (auto i: o2)
		{
			for (int j=0;j<PRI;++j) for (auto x: ch2[i])
			{
				cn21[j][x]+=cn21[j][i];
				if (cn21[j][x]>=primes[j]) cn21[j][x]-=primes[j];
			}
		}
		reverse(all(o2));
		for (int j=0;j<PRI;++j) cn2n[j][2*n-1-dis1[n-1]%2]=1;
		for (auto i: o2)
		{
			for (int j=0;j<PRI;++j) for (auto x: rch2[i])
			{
				cn2n[j][x]+=cn2n[j][i];
				if (cn2n[j][x]>=primes[j]) cn2n[j][x]-=primes[j];
			}
		}
		reverse(all(o2));
		
		vector<int> rjes;
		for (int i=0;i<m;++i)
		{
			bool ok=1;
			int x=a[i],y=b[i];
			if (dis1[x]>dis1[y]) swap(x,y);
			bool ex=(dis1[y]==dis1[x]+c[i]);
			for (int j=0;j<PRI;++j) if ((cn11[j][x]*1ll*cn1n[j][y]*ex-cn1n[j][0])%primes[j]) ok=0;
			int a1=a[i]*2,b1=b[i]*2+c[i]%2,a2=a[i]*2+1,b2=b[i]*2+1-c[i]%2;
			if (dis2[a1]>dis2[b1]) swap(a1,b1);
			if (dis2[a2]>dis2[b2]) swap(a2,b2);
			bool eq=1;
			bool ex1=(dis2[b1]==dis2[a1]+c[i]),ex2=(dis2[b2]==dis2[a2]+c[i]);
			for (int j=0;j<PRI;++j) if ((cn21[j][a1]*1ll*cn2n[j][b1]*ex1+cn21[j][a2]*1ll*cn2n[j][b2]*ex2-cn2n[j][0])%primes[j]) eq=0;
			if (dis2[2*n-1-dis1[n-1]%2]!=dis1[n-1]+1) ok=0;
			if (ok && !eq) rjes.pb(i+1);
		}
		cout<<rjes.size()<<'\n';
		for (auto x: rjes) cout<<x<<' ';
		cout<<'\n';
	}
}




