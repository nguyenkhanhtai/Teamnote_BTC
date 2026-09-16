struct Node {
int x;
Node *l = 0;
Node *r = 0;
Node *p = 0;
bool rev = false;
Node() = default;
Node(int v) { x = v; }
void push() {
if (rev) {
    rev = false;
    swap(l, r);
    if (l) l->rev ^= true;
    if (r) r->rev ^= true;
}
}
bool is_root() { return p == 0 || (p->l != this && this != p->r); }
};
struct LCT {
vector<Node> a;
LCT(int n) {
a.resize(n + 1);
for (int i = 1; i <= n; ++i) a[i].x = i;
}
void rot(Node *c) {
auto p = c->p;
auto g = p->p;
if (!p->is_root()) (g->r == p ? g->r : g->l) = c;
p->push();
c->push();
if (p->l == c) {  // rtr
    p->l = c->r;
    c->r = p;
    if (p->l) p->l->p = p;
} else {  // rtl
    p->r = c->l;
    c->l = p;
    if (p->r) p->r->p = p;
}
p->p = c;
c->p = g;
}
void splay(Node *c) {
while (!c->is_root()) {
    auto p = c->p;
    auto g = p->p;
    if (!p->is_root()) rot((g->r == p) == (p->r == c) ? p : c);
    rot(c);
}
c->push();
}
Node *access(int v) {
Node *last = 0;
Node *c = &a[v];
for (Node *p = c; p; p = p->p) {
    splay(p);
    p->r = last;
    last = p;
}
splay(c);
return last;
}
void make_root(int v) {
access(v);
auto *c = &a[v];
if (c->l) c->l->rev ^= true, c->l = 0;
}
void link(int u, int v){
make_root(u);
Node *c = &a[u];
c->p = &a[v];
}
void cut(int u){
access(u);
assert(a[u].l);
a[u].l->p = 0;
a[u].l = 0;
}
int lca(int u, int v){
if (u == v) return u;
access(u); access(v);
if (a[u].p == 0) return -1;
splay(&a[u]);
return (a[u].p ? a[u].p->x : a[u].x);
}
};