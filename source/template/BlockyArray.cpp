
//SQRT Decomposition DS
//Query: O(1)
//Update: O(sqrt(n))


struct BlockyArray{
    vector<int> arr, lazy; //zero based
    BlockyArray(int n = 0){
        arr.resize(n + 9, 0);
        lazy.resize(n + 9, 0);
    }
    void updateUp(int pos, int val){
         pos++;
         while(pos < arr.size() and pos % block != 0) arr[pos++] += val;
         for(int i = pos; i < arr.size(); i += block) lazy[i / block] += val;
    }
    void updateDown(int pos, int val){ //one based
                                   //cap nhat nhung gia tri nho hon pos
         pos--;
         while(pos >= 0 and pos % block != block - 1) arr[pos--] += val;
         for(int i = pos; i >= 0; i -= block) lazy[i / block] += val;
    }
    int get(int pos){
        return arr[pos] + lazy[pos / block];
    }
};

//MO - Hilbert
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) { return 0; }
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += ((seg == 1 || seg == 2) ? add : (subSquareSize - add - 1));
	return ans;
}

struct Query{
    int l, r, id, ord;
    Query(int _l, int _r, int _id){
        l = _l; r = _r; id = _id;
        ord = hilbertOrder(l, r, 17, 0);
    }
    bool operator < (const Query &other) const{ return ord < other.ord;}
};
vector<Query> query;
void pseudo_mo(int lo, int hi, int id){
    while(r < hi){
        sweeplineMO[l - 1].pb(Segment(r + 1, hi, -1, id));
        r = hi;
    }
    while(l > lo){
        sweeplineMO[r].pb(Segment(lo, l - 1, 1, id));
        l = lo;
    }
    while(r > hi){
        sweeplineMO[l - 1].pb(Segment(hi + 1, r, 1, id));
        r = hi;
    }
    while(l < lo){
        sweeplineMO[r].pb(Segment(l, lo - 1, -1, id));
        l = lo;
    }
}
 