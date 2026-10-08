#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 100005;

int n;
string s;
int p[MAXN];

struct olbat {
    int cnt, siz, lef, rig;
    vector <int> len, link, suf[2], child[2];
    deque <char> dq;

    olbat () {
        cnt = 2; siz = 0;
        lef = rig = 1;
        len = {-1, 0};
        child[0] = child[1] = {0, 0};
        link = suf[0] = suf[1] = {0, 0};
    }

    void add_new_node (int par, char c) {
        len.push_back(len[par] + 2);

        child[c - '0'][par] = cnt;
        child[0].push_back(0); child[1].push_back(0);

        if (par != 0) {
            link.push_back(child[c - '0'][suf[c - '0'][par]]);
        } else {
            link.push_back(1);
        }
        suf[0].push_back(0); suf[1].push_back(0);

        cnt++;
    }

    void add_rig (char c) {
        dq.push_back(c);

        int par;
        if (len[rig] < siz && dq[siz - len[rig] - 1] == c) {
            par = rig;
        } else {
            par = suf[c - '0'][rig];
        }

        if (child[c - '0'][par] == 0) {
            add_new_node(par, c);
            if (dq[siz - len[link[cnt - 1]]] == '0') {
                suf[0][cnt - 1] = link[cnt - 1];
                suf[1][cnt - 1] = suf[1][link[cnt - 1]];
            } else {
                suf[0][cnt - 1] = suf[0][link[cnt - 1]];
                suf[1][cnt - 1] = link[cnt - 1];
            }
        }

        siz++;

        rig = child[c - '0'][par];
        if (len[rig] == siz) lef = rig;
    }

    void add_lef (char c) {
        int par;
        if (len[lef] < siz && dq[len[lef]] == c) {
            par = lef;
        } else {
            par = suf[c - '0'][lef];
        }

        if (child[c - '0'][par] == 0) {
            add_new_node(par, c);
            if (len[link[cnt - 1]] - 1 >= 0 && dq[len[link[cnt - 1]] - 1] == '0' || len[link[cnt - 1]] - 1 < 0 && c == '0') {
                suf[0][cnt - 1] = link[cnt - 1];
                suf[1][cnt - 1] = suf[1][link[cnt - 1]];
            } else {
                suf[0][cnt - 1] = suf[0][link[cnt - 1]];
                suf[1][cnt - 1] = link[cnt - 1];
            }
        }

        dq.push_front(c); siz++;

        lef = child[c - '0'][par];
        if (len[lef] == siz) rig = lef;
    }

    void dfs (int node, string s) {
        cout << node << ": " << s << endl;
        string novi;
        if (node == 0) novi = "0"; else novi = "0" + s + "0";
        if (child[0][node]) dfs(child[0][node], novi);
        if (node == 0) novi = "1"; else novi = "1" + s + "1";
        if (child[1][node]) dfs(child[1][node], novi);
    }

    void ispis () {
        for (auto c : dq) cout << c; cout << endl;
    }

    void popis () {
        dfs(0, "");
        dfs(1, "");
    }
} ol[MAXN];

int nadi (int a) {
    if (a == p[a]) return a;
    return p[a] = nadi(p[a]);
}

int spoji (int a, int b) {
    a = nadi(a); b = nadi(b);
    if (ol[a].siz > ol[b].siz) {
        for (int i = 0; i < ol[b].dq.size(); i++) {
            ol[a].add_rig(ol[b].dq[i]);
        }
        p[b] = a;
    } else {
        for (int i = (int) ol[a].dq.size() - 1; i >= 0; i--) {
            ol[b].add_lef(ol[a].dq[i]);
        }
        p[a] = b;
    }
    return p[a];
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        ol[i].add_rig(s[i - 1]);
        p[i] = i;
    }
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        int node = spoji(a, b);
        cout << ol[node].cnt - 2 << endl;
    }
    /*cin >> n;
    for (int i = 1; i <= n; i++) {
        char c, d;
        cin >> c >> d;
        if (d == 'L') ol[0].add_lef(c); else ol[0].add_rig(c);
    }
    cout << ol[0].cnt - 2;*/
    return 0;
}
