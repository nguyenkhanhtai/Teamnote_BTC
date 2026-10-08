#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using vi=vector<int>;
using vl=vector<ll>;
#define pb push_back
#define all(a) begin(a),end(a)

const int N=400010,MOD=1e9+7;
const char en='\n';
const ll LLINF=1ll<<60;
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

int n,m,k,q,x[N],y[N],cc[N][4],po[N][4],cs[N],ccc;
char ti[N];
vector<pii> ch[N][4],imx[N],imy[N];
bool bio[N][4];

int nex(int x,int y,int dir)
{
	if (dir==0)
	{
		auto it=lower_bound(all(imx[x]),pii(y,MOD));
		if (it==imx[x].end()) it=imx[x].begin();
		if (it==imx[x].end()) return -1;
		return it->y;
	}
	if (dir==1)
	{
		auto it=lower_bound(all(imy[y]),pii(x,MOD));
		if (it==imy[y].end()) it=imy[y].begin();
		if (it==imy[y].end()) return -1;
		return it->y;
	}
	if (dir==2)
	{
		auto it=lower_bound(all(imx[x]),pii(y,0));
		if (it==imx[x].begin()) it=imx[x].end();
		if (it==imx[x].begin()) return -1;
		--it;
		return it->y;
	}
	if (dir==3)
	{
		auto it=lower_bound(all(imy[y]),pii(x,0));
		if (it==imy[y].begin()) it=imy[y].end();
		if (it==imy[y].begin()) return -1;
		--it;
		return it->y;
	}
	assert(0);
}

void dfs(int i,int j)
{
	bio[i][j]=1;
	cc[i][j]=ccc;
	++cs[ccc];
	for (auto x: ch[i][j]) if (!bio[x.x][x.y])
	{
		po[x.x][x.y]=po[i][j]+1;
		dfs(x.x,x.y);
	}
}

int dis(pii a,pii b)
{
	int ca=cc[a.x][a.y],cb=cc[b.x][b.y];
	if (ca!=cb) return MOD;
	return (po[b.x][b.y]-po[a.x][a.y]+cs[ca])%cs[ca];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>k;
	for (int i=0;i<k;++i)
	{
		cin>>x[i]>>y[i]>>ti[i];
		imx[x[i]].pb({y[i],i});
		imy[y[i]].pb({x[i],i});
	}
	for (int i=1;i<=n;++i) sort(all(imx[i]));
	for (int i=1;i<=m;++i) sort(all(imy[i]));
	for (int i=0;i<k;++i) for (int dir=0;dir<4;++dir)
	{
		int nexdir=dir;
		if (ti[i]=='L') nexdir=(nexdir+3)%4;
		else nexdir=(nexdir+1)%4;
		ch[i][dir].pb({nex(x[i],y[i],nexdir),nexdir});
	}
	for (int i=0;i<k;++i) for (int dir=0;dir<4;++dir) if (!bio[i][dir])
	{
		dfs(i,dir);
		++ccc;
	}
	cin>>q;
	while (q--)
	{
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		vector<pii> p1(4),p2(4);
		for (int dir=0;dir<4;++dir)
		{
			p1[dir]={nex(x1,y1,dir),dir};
			p2[dir]={nex(x2-dx[dir],y2-dy[dir],dir),dir};
		}
		int mi=MOD;
		for (auto x: p1) for (auto y: p2) if (x.x!=-1 && y.x!=-1) mi=min(mi,dis(x,y));
		if ((x1==x2 && imx[x1].empty()) || (y1==y2 && imy[y1].empty())) mi=0;
		if (mi<MOD) cout<<mi<<en;
		else cout<<-1<<en;
	}
}
