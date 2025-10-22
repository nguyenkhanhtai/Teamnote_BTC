struct Node{
    int nxt[26];
    int len;
    int sufflink;
    int num;
};
int len;
char s[MAXN];
Node tree[MAXN];
int suff,num,ans;
bool addLetter(int pos){
    int cur = suff;
    int c = s[pos] - 'a';
    int curlen = 0;
    while(true){
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]){
            break;
        }
        cur = tree[cur].sufflink;
    }
    if (tree[cur].nxt[c]){
        suff = tree[cur].nxt[c];
        return false;
    }

    num++;
    suff = num;
    tree[num].len = tree[cur].len + 2;
    tree[cur].nxt[c] = num;
    if (tree[num].len==1){
        tree[num].sufflink = 2;
        tree[num].num = 1;
        return true;
    }
    while(true){
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos-1-curlen] == s[pos]){
            tree[num].sufflink = tree[cur].nxt[c];
            break;
        }
    }
    tree[num].num = 1 + tree[tree[num].sufflink].num;
    return true;
}
void init(){
    num = 2, suff = 2;
    tree[1].len = -1;
    tree[2].len = 0;
    tree[1].sufflink = 1;
    tree[2].sufflink = 1;
}

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 1, sigma = 26;
int len[maxn], link[maxn], to[maxn][sigma];
int slink[maxn], diff[maxn], series_ans[maxn];
int sz, last, n;
char s[maxn];

void init()
{
    s[n++] = -1;
    link[0] = 1;
    len[1] = -1;
    sz = 2;
}

int get_link(int v)
{
    while(s[n - len[v] - 2] != s[n - 1]) v = link[v];
    return v;
}

void add_letter(char c)
{
    s[n++] = c -= 'a';
    last = get_link(last);
    if(!to[last][c])
    {
        len[sz] = len[last] + 2;
        link[sz] = to[get_link(link[last])][c];
        diff[sz] = len[sz] - len[link[sz]];
        if(diff[sz] == diff[link[sz]])
            slink[sz] = slink[link[sz]];
        else
            slink[sz] = link[sz];
        to[last][c] = sz++;
    }
    last = to[last][c];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    string s;
    cin >> s;
    int n = s.size();
    int ans[n + 1];
    memset(ans, 63, sizeof(ans));
    ans[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        add_letter(s[i - 1]);
        for(int v = last; len[v] > 0; v = slink[v])
        {
            series_ans[v] = ans[i - (len[slink[v]] + diff[v])];
            if(diff[v] == diff[link[v]])
                series_ans[v] = min(series_ans[v], series_ans[link[v]]);
            ans[i] = min(ans[i], series_ans[v] + 1);
        }
        cout << ans[i] << "\n";
    }
    return 0;
}
