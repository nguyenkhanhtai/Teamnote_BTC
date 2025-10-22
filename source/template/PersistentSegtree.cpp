struct Node{ //Use Long long if MLE.
    int sum;
    //int num;
    int leftChild;
    int rightChild;
 
    Node(int _sum = 0, int _leftChild = 0, int _rightChild = 0){
        sum = _sum;
        leftChild = _leftChild;
        rightChild = _rightChild;
    }
};
 
vector<Node> st;
vector<int> version;
 
void update(int nn, int l, int r, int pos, int val){
    if (l == r){
        st[nn].sum = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid){
        st.push_back(st[st[nn].leftChild]);
        st[nn].leftChild = st.size() - 1;
        update(st[nn].leftChild, l, mid, pos, val);
    }
    else{
        st.push_back(st[st[nn].rightChild]);
 
        st[nn].rightChild = st.size() - 1;
        update(st[nn].rightChild, mid + 1, r, pos, val);
    }
 
    st[nn].sum = st[st[nn].leftChild].sum + st[st[nn].rightChild].sum;
}
 
int get(int nn, int l, int r, int u, int v){
    if (l >= u and r <= v){
        return st[nn].sum;
    }
    if (l > v or r < u) return 0;
    int mid = (l + r) >> 1;
    return get(st[nn].leftChild, l, mid, u, v)
          +get(st[nn].rightChild, mid + 1, r, u, v);
}

ll getKth(int nn, int l, int r, int k){ //Remember to add variable "number" to persistent
    int leftChild = st[nn].leftChild;
    int rightChild = st[nn].rightChild;
    int mid = (l + r) >> 1;
    if (l == r){
        return value[l] * min(st[nn].num, k * 1LL);
    }
    if (st[leftChild].num < k){
        return st[leftChild].sum + getKth(rightChild, mid + 1, r, k - st[leftChild].num);
    }
    else return getKth(leftChild, l, mid, k);
}


//Use:
st.pb(Node(0, 0, 0));
version.pb(0);
update(version[0], 1, n, i, a[i]);

{ //Add a copy version of the kth version
    int k;
    cin >> k;
    k--;
    version.pb(st.size());
    st.pb(st[version[k]]);
}
{ //Modify and get Range
    if (type == 1){ //Update pos
        update(version[k], 1, n, a, b);
    }
    else if (type == 2){ //Get Range
        cout << get(version[k], 1, n, a, b) << endl;
    }
}
