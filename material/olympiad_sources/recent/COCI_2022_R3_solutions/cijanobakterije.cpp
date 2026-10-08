#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n,m;
int sol=0;
vector<int> graph[MAXN];
bool visited[MAXN];

pair<int, int> find_furthest(int node, int parent=-1){
    visited[node] = true;
    pair<int,int> ret(node, 1);
    for(auto i:graph[node]){
        if(i != parent){
            auto csol = find_furthest(i, node);
            csol.second++;
            if(csol.second > ret.second){
                ret = csol;
            }
        }
    }
    return ret;
}

int radius(int node){
    auto s1 = find_furthest(node);
    return find_furthest(s1.first).second;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i=0;i<m;i++){
        int a, b;
        scanf("%d%d", &a, &b);
        a--;b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i=0;i<n;i++){
        if(!visited[i]){
            sol += radius(i);
        }
    }
    printf("%d\n", sol);
}
