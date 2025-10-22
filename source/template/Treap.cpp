int RAND(){
    int res = 0;
    FOR(i, 1, 30){
        res += (1LL << (rand() % 30));
    }
    return res;
}

struct TreapNode{
    TreapNode *leftChild, *rightChild;
    int val = 0, sum = 0, weight;
    int lazy = 0, sz = 0;

    TreapNode(int _val = 0){
        val = _val;
        sum = val;
        weight = RAND();
        lazy = 0;
        sz = 1;
        leftChild = rightChild = nullptr;
    }
};

typedef TreapNode* Treap;

int getSum(Treap root){
    if (root == nullptr) return 0;
    return root->sum;
}

int getSize(Treap root){
    if (root == NULL) return 0;
    return root->sz;
}

void update(Treap &root){
    if (root == NULL) return;
    root->sum = root->val + getSum(root->leftChild) + getSum(root->rightChild);
    root->sz = 1 + getSize(root->leftChild) + getSize(root->rightChild);
}

void fix(Treap root){
    if (root == NULL) return;

    if (root->lazy){
        swap(root->leftChild, root->rightChild);
        if (root->leftChild != NULL) root->leftChild->lazy ^= 1;
        if (root->rightChild != NULL) root->rightChild->lazy ^= 1;
    }
    root->lazy = 0;
}
void split(Treap rt, Treap &l, Treap &r, int key, int add){

    if (rt == NULL) {
        l = r = NULL;
        return;
    }
    fix(rt);

    int imkey = add + getSize(rt->leftChild);
    if (imkey <= key){
        l = rt;
        split(rt->rightChild, l->rightChild, r, key, imkey + 1);
        update(rt);
    }
    else{
        r = rt;
        split(rt->leftChild, l, r->leftChild, key, add);
        update(rt);
    }
}

void merge(Treap &rt, Treap l, Treap r){
    fix(l);
    fix(r);
    if (!l or !r){
        rt = ((!l) ? r : l);
        return;
    }

    if (l->weight < r->weight){
        rt = r;
        merge(rt->leftChild, l, r->leftChild);
        update(rt);
    }
    else{
        rt =l;
        merge(rt->rightChild, l->rightChild, r);
        update(rt);
    }
}

void go(Treap rt){
    if (rt == NULL) return;

    go(rt->leftChild);
    cout << rt->val << ' ';

    go(rt->rightChild);

}
Treap rt;