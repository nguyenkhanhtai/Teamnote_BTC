//Vector Implementation
struct TrieNode{
    int child[2];
    int sz = 0;
    TrieNode(){
        memset(child, -1, sizeof(child));
        sz = 0;
    }
};

const int B = 30;
struct Trie{
    vector<TrieNode> T = {TrieNode()};

    void addNum(int num, int s){
        int p = 0;
        for(int i = B; i >= 0; i--){
            int b = (num >> i)&1;
            if (T[p].child[b] == -1){
                T[p].child[b] = T.size();
                T.pb(TrieNode());
            }
            T[p].sz += s;
            p = T[p].child[b];
        }
        T[p].sz += s;
    }

    bool exist(int num){
        int p = 0;
        for(int i = B; i >= 0; i--){
            int b = (num >> i)&1;
            if (T[p].child[b] == -1) return false;
            p = T[p].child[b];
        }
        return T[p].sz;
    }

    int getMinXor(int num){
        int res = 0;
        int p = 0;
        for(int i = B; i >= 0; i--){
            int b = (num >> i)&1;
            int c1 = T[p].child[b];
            int c2 = T[p].child[!b];

            if (c1 != -1 and T[c1].sz > 0) p = c1;
            else if (c2 != -1 and T[c2].sz > 0) {
                p = c2;
                res += (1LL << i);
            }
        }
        return res;
    }
};

//-----------------------------
//Pointer Implementation
struct Trie
{
    struct Node
    {
        Node *child[26];
        int cnt, is_end;
        Node()
        {
            for (int i = 0; i < 26; i++) child[i] = 0;
            cnt = is_end = 0;
        }
    };
    Node *root, *cur;
    Trie()
    {
        root = new Node();
    }

    void add(string s)
    {
        cur = root;
        for (char i : s)
        {
            if (cur->child[i - 'a'] == NULL) cur->child[i - 'a'] = new Node();
            cur = cur->child[i - 'a'];
            cur->cnt++;
        }
        cur->is_end++;
    }

    bool check(string s)
    {
        cur = root;
        for (char i : s)
        {
            if (cur->child[i - 'a'] == NULL) return(0);
            cur = cur->child[i - 'a'];
        }
        return(cur->is_end);
    }

    int cnt(string s)
    {
        cur = root;
        for (char i : s)
        {
            if (cur->child[i - 'a'] == NULL) return(0);
            cur = cur->child[i - 'a'];
        }
        return(cur->cnt);
    }

    void del(string s)
    {
        stack <Node*> st;
        cur = root;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            st.push(cur);
            cur = cur->child[s[i] - 'a'];
            cur->cnt--;
        }
        st.push(cur);
        for (int i = 0; i < s.size(); i++)
        {
            if (st.top()->cnt == 0)
            {
                delete(st.top());
                st.pop();
                st.top()->child[s[i] - 'a'] = NULL;
            }
        }
    }
};