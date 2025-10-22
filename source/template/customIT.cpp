struct Node{
    //Necessary information
};


Node mergeNode(Node &a, Node &b){
    //How two nodes can be merged
}

struct segtree{
    vector<Node> st;
    int sz = 0;
    segtree(int _sz = 0){
        sz = _sz;
        st.resize(sz * 4 + 9);
    }

    void init(int arr[]){
        build(arr, 1, 0, sz);
    }
    void build(int arr[], int nn, int l, int r){
        if (l == r){
            st[nn].sum = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(arr, nn << 1, l, mid);
        build(arr, nn << 1 | 1, mid + 1, r);
        st[nn] = mergeNode(st[nn << 1], st[nn << 1 | 1]);
    }

    void fix(int nn, int l, int r){
        //Push down to children
    }
    void updateRange(int nn, int l, int r, int u, int v, int b, int c){
        fix(nn, l, r); 
        if (l >= u and r <= v){
            //lazy update here

            return;
        }
        if (l > v or r < u) return;
        int mid = (l + r) >> 1;
        updateRange(nn << 1, l, mid, u, v, b, c);
        updateRange(nn << 1 | 1, mid + 1, r, u, v, b, c);
        st[nn] = mergeNode(st[nn << 1], st[nn << 1 | 1]);

    }

    void getRange(int nn, int l, int r, int u, int v, Node &res){
        fix(nn, l, r);
        if (l >= u and r <= v){
            res = mergeNode(res, st[nn]);
            return;
        }

        if (l > v or r < u) return;

        int mid = (l + r) >> 1;
        getRange(nn << 1, l, mid, u, v ,res);
        getRange(nn << 1 | 1, mid + 1, r, u, v, res);
    }

    int getRange(int u, int v){
        Node res;
        getRange(1, 0, sz, u, v, res);
        return res.sum;
    }

    void updateRange(int u, int v, int b, int c){
        updateRange(1, 0, sz, u, v, b, c);
    }
};
