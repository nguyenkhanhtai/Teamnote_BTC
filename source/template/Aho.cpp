const alphabet = 2; //26 for character
struct TrieNode{
    int child[alphabet], suffixLink, depth, parent;
    int automata[alphabet];
    //another choice is map if memory is important
    TrieNode(){
        suffixLink = 0;
        parent = 0;
        depth = 0;
        memset(child, 0, sizeof(child));
        memset(automata, 0, sizeof(automata));
    }
};

struct Trie{
    vector<TrieNode> T = {TrieNode()};
    void addStr(string str){
        int p = 0;
        for(int i = 0; i < (int) str.length(); i++){
            //int c = str[i] - '0'; //for number
            //int c = str[i] - 'a'; //for character
            if (T[p].child[c] == 0){
                T[p].child[c] = T.size(); 
                T.pb(TrieNode());
            }
            T[T[p].child[c]].depth = T[p].depth + 1;
            T[T[p].child[c]].parent = p;
            p = T[p].child[c];
        }
    }

    void constructAC(){
        queue<ii> q;
        q.push({0, -1});

        while(!q.empty()){
            int u = q.front().fi;
            int c = q.front().se;
            q.pop();

            if (T[u].depth <= 1) {
                T[u].suffixLink = 0;
            }
            else{
                int prv = T[T[u].parent].suffixLink;
                while(prv > 0 and T[prv].child[c] == 0){
                    prv = T[prv].suffixLink;
                }
                if (T[prv].child[c] != 0) T[u].suffixLink = T[prv].child[c];
            }
            for(int i = 0; i < alphabet; i++){
                T[u].automata[i] = ((T[u].child[i] > 0) ? (T[u].child[i]) : (T[T[u].suffixLink].automata[i]));
            }
            for(int i = 0; i < alphabet; i++){
                if (T[u].child[i] > 0) q.push({T[u].child[i], i});
            }
        }
    }
};