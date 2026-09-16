// Iterative SegTree (0-indexed [l, r], Point update, Range max query, Tree Walk, Dual)
const int N = 2e5 + 5;
int n, sz, tree[4 * N];

void init(int _n) {
    n = _n; sz = 1;
    while (sz < n) sz <<= 1;
    fill(tree, tree + 2 * sz, 0);
}
void build(int a[]) {
    init(n);
    for (int i = 0; i < n; i++) tree[sz + i] = a[i];
    for (int i = sz - 1; i > 0; i--) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
}
void update(int p, int val) { // a[p] = val
    for (tree[p += sz] = val; p > 1; p >>= 1) tree[p >> 1] = max(tree[p], tree[p ^ 1]);
}
int query(int l, int r) { // max [l, r]
    int res = 0;
    for (l += sz, r += sz + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, tree[l++]);
        if (r & 1) res = max(res, tree[--r]);
    }
    return res;
}
// Tree Walk O(log N): First index i >= l with tree[i] >= val (or n if none)
int max_right(int l, int val) {
    int cur = 0;
    for (l += sz; ; l >>= 1) {
        if (l & 1) {
            if (max(cur, tree[l]) >= val) {
                while (l < sz) {
                    l <<= 1;
                    if (max(cur, tree[l]) < val) cur = max(cur, tree[l++]);
                }
                return min(n, l - sz);
            }
            cur = max(cur, tree[l++]);
        }
        if ((l & (l - 1)) == 0) break;
    }
    return n;
}
// Tree Walk O(log N): Last index i <= r with tree[i] >= val (or -1 if none)
int min_left(int r, int val) {
    int cur = 0;
    for (r += sz + 1; ; r >>= 1) {
        if (r & 1) {
            --r;
            if (max(tree[r], cur) >= val) {
                while (r < sz) {
                    r = r << 1 | 1;
                    if (max(tree[r], cur) < val) cur = max(tree[r--], cur);
                }
                return r - sz;
            }
            cur = max(tree[r], cur);
        }
        if ((r & (r + 1)) == 0) break;
    }
    return -1;
}
// Dual SegTree: Range update [l, r] += val, Point query at p
void update_range(int l, int r, int val) {
    for (l += sz, r += sz + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) tree[l++] += val;
        if (r & 1) tree[--r] += val;
    }
}
int query_point(int p) {
    int res = 0;
    for (p += sz; p > 0; p >>= 1) res += tree[p];
    return res;
}
