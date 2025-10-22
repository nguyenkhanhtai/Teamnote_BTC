struct state {
    int len, link; map<char, int> next;
};

const int MAXLEN = 500000 * 2 + 100;
state st[MAXLEN];
int sz, last, dp[MAXLEN];
void sa_init() {st[0].len = 0; st[0].link = -1; sz++; last = 0;}

void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

//Sample Usage: 
sa_init();
FOR(i, 0, n - 1) sa_extend(str[i]);
int ans = 0;
FOR(i, 0, sz - 1){
    ans += st[i].len - st[st[i].link].len;
}
cout << ans << endl;