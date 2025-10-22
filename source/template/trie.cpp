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