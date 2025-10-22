struct point{
    double dim[2];
    bool operator != (const point &other){
         return !(dim[0] == other.dim[0] and dim[1] == other.dim[1]);
    }
} pt[MAXN], tmp[MAXN];

struct cmp_point{
    int axis;
    cmp_point(int x = 0): axis(x) {}
    bool operator () (const point &a, const point &b){
         return a.dim[axis] < b.dim[axis];
    }
};
struct kd_tree{
    int axis;
    double value;
    point p;
    kd_tree *left ,*right;
};

typedef kd_tree* node_ptr;
node_ptr node;

double distance_squared(point a, point b){
    double sum = 0;
    for(int i = 0; i < 2; i++){
        sum += (a.dim[i] - b.dim[i]) * (a.dim[i] - b.dim[i]);
    }
    return sqrt(sum);
}
void build(node_ptr &node, int l, int r, int axis){
    if (l > r){
        node = NULL;
        return;
    }

    node = new kd_tree();

    if (l == r){
        node->p = pt[l];
        node->left = node->right = NULL;
        node->axis = axis;
        return;
    }

    int mid = (l + r) >> 1;
    nth_element(pt + l, pt + mid, pt + 1 + r, cmp_point(axis));
    node->value = pt[mid].dim[axis];   node->axis = axis;   node->p = pt[mid];
    build(node->left, l, mid - 1, axis ^ 1);
    build(node->right, mid + 1, r, axis ^ 1);
}

void NearestNeighbour(node_ptr node, point q, double &ans){
    if (node == NULL) return;
    if (q != node->p) minimize(ans, distance_squared(node->p, q));
    if (node->left == NULL and node->right == NULL){
        return;
    }
    int axis = node->axis;
    double value = node->value;
    if (q.dim[axis] <= value){
        NearestNeighbour(node->left, q, ans);
        if (q.dim[axis] + ans >= value + eps) NearestNeighbour(node->right, q, ans);
    }
    else{
        NearestNeighbour(node->right, q, ans);
        if (q.dim[axis] - ans <= value - eps) NearestNeighbour(node->left, q, ans);
    }
}